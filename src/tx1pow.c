#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>    

#include "tx1pow.h"

// User-space I2C reading of INA3221 at 0x40
/* #include <stdio.h> */
/* #include <stdlib.h> */
#include <stdbool.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <byteswap.h>

// resistors' values [milli-ohms]
static int rshunt[] = {20, 10, 10};

// ...
static __u8 vshuntReg[] = {0x01, 0x03, 0x05};
static __u8 vbusReg[] = {0x02, 0x04, 0x06};

static int convShuntVol(int file, int reg){
  uint16_t v = __bswap_16(i2c_smbus_read_word_data(file, reg));
  return (int)((v >> 3) * 40);
}

static int convBusVol(int file, int reg){
  uint16_t v = __bswap_16(i2c_smbus_read_word_data(file, reg));
  return (int)((v >> 3) * 8);
}

static int calcCurr(int v, int r) {
  return (int)(v/(float)r);
}

static int calcPow(int v, int i) {
  return (int)(v*i/1000);
}

static void tx1pow_get_val_sysf(tx1pow_ina3321_input in,
			 tx1pow_ina3321_measure measure,
			 unsigned int *val)
{
  FILE *fp;
  int addr;
  int ans;
  char buff[MAX_BUFF];
  char *meas = "voltage";
    
  if (in >= 0 && in <= 2) {
    addr = 0;
  } else if (in >= 3 && in <= 5) {
    addr = 2;
  } else if (in >= 6 && in <= 8) {
    addr = 3;
  } else {
    addr = 2;
  }

  switch (measure) {
  case 0: {
    meas = "voltage";
    break;
  }
  case 1: {
    meas = "power";
    break;
  }
  case 2: {
    meas = "current";
    break;
  }
  default:
    break;
  }

  snprintf(buff, sizeof(buff),
	   SYSFS_INA3321_PATH "/1-004%d/iio_device/in_%s" "%d" "_input",
	   addr, meas, in % 2);

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

static int tx1pow_get_val_userspace_i2c(int i, unsigned int *val)
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
  vshunt = convShuntVol(file, vshuntReg[i]);
  vbus = convBusVol(file, vbusReg[i]);
  curr = calcCurr(vshunt, rshunt[i]);
  power = calcPow(vbus, curr);

  *val = power;

  /* close(file); */

  return 0;
}

void tx1pow_get_val(tx1pow_ina3321_input in,
                    tx1pow_ina3321_measure measure,
                    unsigned int *val)
{

  if (in >= 0 && in <= 2) {
    tx1pow_get_val_userspace_i2c(in, val);
  } else if (in >= 3 && in <= 8) {
    tx1pow_get_val_sysf(in, measure,val);
  } else {
  }

  
}
