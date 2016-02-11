#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "tx1temp.h"

void tx1temp_get_val(tx1temp_zone zone, unsigned long *val)
{
    FILE *fp;
    char buff[MAX_BUFF];
    unsigned long ans;
    
    snprintf(buff, sizeof(buff), SYSFS_TEMP_PATH "/thermal_zone%d/temp", zone);

    fp = fopen(buff, "r");

    if (fp == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else if (!fscanf(fp, "%lu", &ans)) {
        fprintf(stderr, "Error scanning the file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else {
        fclose(fp);
    }
    
    *val = ans;
}
