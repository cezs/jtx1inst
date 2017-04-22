#ifndef TX1TEMP_H_
#define TX1TEMP_H_

#define SYSFS_TEMP_PATH "/sys/class/thermal"

typedef unsigned int tx1temp_zone;
enum tx1temp_zones {
    A0 = 0,
    CPU,
    GPU,
    PLL,
    PMIC,
    TDIODE,
    TBOARD,
    FAN
};

void tx1temp_get_val(tx1temp_zone zone, unsigned int *val);

#endif // TX1TEMP_H_
