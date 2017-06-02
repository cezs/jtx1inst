/**
 * @file tx1pow.h
 * @author cs
 * @brief This header file contains the function for accessing
 * on-board and on-module INA3221's values.
 */
#ifndef TX1POW_H_
#define TX1POW_H_

#define MAX_BUFF 128
#define SYSFS_INA3321_PATH "/sys/class/i2c-dev/i2c-1/device"

/**
 * @brief Enumeration indexing each INA3221's input.
 */
typedef unsigned int tx1pow_ina3321_input;
enum tx1pow_ina3321_inputs {
    VDD_IN = 0, ///< main module power input
    VDD_GPU, ///< GPU Power rail
    VDD_CPU, ///< CPU Power rail
    VDD_MUX, ///< main carrier board power input
    VDD_5V_IO_SYS, ///< main carrier board 5V supply
    VDD_3V3_SYS, ///< main carrier board 3.3V supply
    VDD_3V3_IO, ///< carrier board 3.3V Sleep supply
    VDD_1V8_IO, ///< main carrier board 1.8V supply
    VDD_M2_IN ///< 3.3V supply for M.2 Key E connector
};

/**
 * @brief Enumeration indexing each type of measurement.
 */
typedef unsigned int tx1pow_ina3321_measure;
enum tx1pow_meas_ch {
    VOLTAGE = 0, ///< Voltage given in milli-volts or mV
    POWER, ///< Power given in milli-watts or mW
    CURRENT ///< Power given in milli-amps mA
};

/**
 * @brief Read on-board and on-module INA3221's values
 * 
 * Use sysf files to access on-board INA3221 sensor 
 * and userspace I2C to access on-module INA3221 sensor
 * and read power, current, and voltage information.
 *
 * @param in Indexed by ::tx1pow_ina3321_input
 * @param measure Either VOLTAGE, POWER or CURRENT. See ::tx1pow_ina3321_measure
 * @param *val Output's reference
 */
void tx1pow_get_val(tx1pow_ina3321_input in,
                      tx1pow_ina3321_measure measure,
                      unsigned int *val);

#endif // TX1POW_H_
