#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>    
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <linux/i2c-dev.h>
#include <byteswap.h>

#include "jtx1pow.h"

// resistors' values [milli-ohms]
static int rshunt[] = {20, 10, 10};

// TX1's specific registers
static __u8 vshuntReg[] = {0x01, 0x03, 0x05};
static __u8 vbusReg[] = {0x02, 0x04, 0x06};

// read shunt voltage value
static int convShuntVol(int file, int reg){
  uint16_t v = __bswap_16(i2c_smbus_read_word_data(file, reg));
  return (int)((v >> 3) * 40);
}

// read bus voltage value
static int convBusVol(int file, int reg){
  uint16_t v = __bswap_16(i2c_smbus_read_word_data(file, reg));
  return (int)((v >> 3) * 8);
}

// calculate current using voltage and resistor values
static int calcCurr(int v, int r) {
  return (int)(v/(float)r);
}

// calculate power using voltage and current values
static int calcPow(int v, int i) {
  return (int)(v*i/1000);
}

// read INA3221's values from 0x42 and 0x43 addresse using sysfs files
static void jtx1_get_ina3221_sysf(jtx1_rail rail,
				  jtx1_rail_type measure,
				  unsigned int *val)
{
  FILE *fp;
  int addr;
  int ans;
  char buff[MAX_BUFF];
  char *mea = "voltage";
    
  if (rail >= 0 && rail <= 2) {
    addr = 0;
  } else if (rail >= 3 && rail <= 5) {
    addr = 2;
  } else if (rail >= 6 && rail <= 8) {
    addr = 3;
  } else {
    addr = 2;
  }

  switch (measure) {
  case 0: {
    mea = "voltage";
    break;
  }
  case 1: {
    mea = "power";
    break;
  }
  case 2: {
    mea = "current";
    break;
  }
  default:
    break;
  }

  snprintf(buff, sizeof(buff),
	   SYSFS_INA3321_PATH "/1-004%d/iio_device/in_%s" "%d" "_input",
	   addr, mea, rail % 2);

  fp = fopen(buff, "r");

  if (fp == NULL) {
    fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  } else if (!fscanf(fp, "%d", &ans)) {
    fprintf(stderr, "Error scanning the file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  } else {
    fclose(fp);
  }

  *val = ans;

}

// read INA3221's values from 0x40 using userspace i2c communication
static int jtx1_get_ina3221_userspace_i2c(int rail, unsigned int *val)
{
  int file;
  int adapter_nr = 1;
  char filename[20];

  int addr = 0x40; /* The I2C address */

  int vshunt;
  int vbus;
  int curr;
  int power;

  snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
  file = open(filename, O_RDWR);
  if (file < 0) {
    fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  
  if (ioctl(file, I2C_SLAVE, addr) < 0) {
    fprintf(stderr, "IOCTL error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  /* sleep(1); */
  vshunt = convShuntVol(file, vshuntReg[rail]);
  vbus = convBusVol(file, vbusReg[rail]);
  curr = calcCurr(vshunt, rshunt[rail]);
  power = calcPow(vbus, curr);

  *val = power;

  close(file);

  return 0;
}

// read INA3221's values from 0x40, 0x42 and 0x43 addresses
void jtx1_get_ina3221(jtx1_rail rail,
		      jtx1_rail_type measure,
		      unsigned int *val)
{

  if (rail >= 0 && rail <= 2) {
    jtx1_get_ina3221_userspace_i2c(rail, val);
  } else if (rail >= 3 && rail <= 8) {
    jtx1_get_ina3221_sysf(rail, measure, val);
  } else {
  }

  
}
