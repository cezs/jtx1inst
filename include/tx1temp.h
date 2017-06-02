/**
 * @file tx1temp.h
 * @author cs
 * @brief This header file contains the functions for reading
 * Jetson TX1's values of thermal zones.
 */
#ifndef TX1TEMP_H_
#define TX1TEMP_H_

#define MAX_BUFF 128
#define SYSFS_TEMP_PATH "/sys/class/thermal"

/**
 * @brief Thermal zones index
 */
typedef unsigned int tx1temp_zone;
enum tx1temp_zones {
    A0 = 0, ///< on-chip thermal zone (mC)
    CPU, ///< on-chip thermal zone (mC)
    GPU, ///< on-chip thermal zone (mC)
    PLL, ///< on-chip thermal zone (mC)
    PMIC, ///< on-chip thermal zone (mC)
    TDIODE, ///< on-module thermal zone (mC)
    TBOARD, ///< on-module thermal zone (mC)
    FAN ///< on-chip thermal zone (mC)
};


/**
 * @brief Read on-chip and on-module temperatures.
 *
 * @param zone Indexed by ::tx1temp_zone
 * @param *val Output's reference
 */
void tx1temp_get_val(tx1temp_zone zone, unsigned long *val);

#endif // TX1TEMP_H_
