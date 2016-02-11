#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_BUFF 128

void set_gpu_rate(const unsigned long gpu_rate)
{
    int val = 1;
    FILE *fp[2];
  
    fp[0] = fopen("/sys/kernel/debug/clock/override.gbus/rate", "w");
    
    if (fp[0] == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else if (!fprintf(fp[0], "%lu", gpu_rate)) {
        fprintf(stderr, "Error writing to file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else {
        fclose(fp[0]);
    }

    fp[1] = fopen("/sys/kernel/debug/clock/override.gbus/state", "w");

    if (fp[1] == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else if (!fprintf(fp[1], "%u", val)) {
        fprintf(stderr, "Error writing to file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else {
        fclose(fp[1]);
    }
    
}

void get_gpu_rate(unsigned long *gpu_rate)
{
    FILE *fp;
    unsigned long rate;

    fp = fopen("/sys/kernel/debug/clock/gbus/rate", "r");

    if (fp == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else if (!fscanf(fp, "%lu", &rate)) {
        fprintf(stderr, "Error scaning file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else {
        fclose(fp);
    }

    *gpu_rate = rate;

}


void set_emc_rate(const unsigned long emc_rate)
{
    int val = 1;
    FILE *fp[2];
  
    fp[0] = fopen("/sys/kernel/debug/clock/override.emc/rate", "w");

    if (fp[0] == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else {
        fprintf(fp[0], "%lu", emc_rate);
        fclose(fp[0]);
    }

    fp[1] = fopen("/sys/kernel/debug/clock/override.emc/state", "w");

    if (fp[1] == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else {
        fprintf(fp[1], "%u", val);
        fclose(fp[1]);
    }

}


void get_emc_rate(unsigned long *gpu_rate)
{
    FILE *fp;
    unsigned long rate;

    fp = fopen("/sys/kernel/debug/clock/emc/rate", "r");

    if (fp == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else if (!fscanf(fp, "%lu", &rate)) {
        fprintf(stderr, "Error scaning file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else {
        fclose(fp);
    }

    *gpu_rate = rate;

}


/* void tx1pow_get_val(tx1pow_ina3321_input in, */
/*                     tx1pow_ina3321_measure measure, */
/*                     unsigned int *val) */
/* { */
/*     FILE *fp; */
/*     int addr; */
/*     int ans; */
/*     char buff[MAX_BUFF]; */
/*     char *meas = "voltage"; */
    
/*     if (in >= 0 && in <= 3) { */
/*         addr = 0; */
/*     } else if (in >= 4 && in <= 6) { */
/*         addr = 2; */
/*     } else if (in >= 7 && in <= 9) { */
/*         addr = 3; */
/*     } else { */
/*         addr = 2; */
/*     } */

/*     switch (measure) { */
/*     case 0: { */
/*         meas = "voltage"; */
/*         break; */
/*     } */
/*     case 1: { */
/*         meas = "power"; */
/*         break; */
/*     } */
/*     case 2: { */
/*         meas = "current"; */
/*         break; */
/*     } */
/*     default: */
/*         break; */
/*     } */

/*     snprintf(buff, sizeof(buff), */
/*              SYSFS_INA3321_PATH "/1-004%d/iio_device/in_%s" "%d" "_input", */
/*              addr, meas, in % 2); */

/*     fp = fopen(buff, "r"); */

/*     if (fp == NULL) { */
/*         fprintf(stderr, "Error opening file: %s\n", strerror(errno)); */
/*         exit(EXIT_FAILURE); */
/*     } else if (!fscanf(fp, "%d", &ans)) { */
/*         fprintf(stderr, "Error scanning the file: %s\n", strerror(errno)); */
/*         exit(EXIT_FAILURE); */
/*     } else { */
/*         fclose(fp); */
/*     } */

/*     *val = ans; */
/* } */
