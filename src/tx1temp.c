#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "tx1inst.h"

void tx1temp_get_val(tx1temp_zone zone, unsigned int *val)
{
    FILE *fp;
    char buff[MAX_BUFF];
    int ans;
    
    snprintf(buff, sizeof(buff), SYSFS_TEMP_PATH "/thermal_zone%d/temp", zone);

    fp = fopen(buff, "r");
    fscanf(fp, "%d", &ans);
    fclose(fp);

    *val = ans;
}
