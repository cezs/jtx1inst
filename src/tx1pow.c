#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "tx1inst.h"

void tx1pow_get_val(tx1pow_ina3321_input in,
                      tx1pow_ina3321_measure measure,
                      unsigned int *val)
{
    FILE *fp;
    int addr;
    int ans;
    char buff[MAX_BUFF];
    char *meas = "voltage";
    
    if (in >= 0 && in <= 3) {
        addr = 0;
    } else if (in >= 4 && in <= 6) {
        addr = 2;
    } else if (in >= 7 && in <= 9) {
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
    fscanf(fp, "%d", &ans);
    fclose(fp);

    *val = ans;
}
