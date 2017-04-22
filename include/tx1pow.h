#ifndef TX1POW_H_
#define TX1POW_H_

#define SYSFS_INA3321_PATH "/sys/class/i2c-dev/i2c-1/device"

typedef unsigned int tx1pow_ina3321_input;
enum tx1pow_ina3321_inputs {
    /* main module power input */
    VDD_IN = 1,
    /* GPU Power rail */
    VDD_GPU,
    /* CPU Power rail */
    VDD_CPU,
    /* main carrier board power input */
    VDD_MUX,
    /* main carrier board 5V supply */
    VDD_5V_IO_SYS,
    /* main carrier board 3.3V supply */
    VDD_3V3_SYS,
    /* carrier board 3.3V Sleep supply */
    VDD_3V3_IO,
    /* main carrier board 1.8V supply */
    VDD_1V8_IO,
    /* 3.3V supply for M.2 Key E connector */
    VDD_M2_IN
};

typedef unsigned int tx1pow_ina3321_measure;
enum tx1pow_meas_ch {
    VOLTAGE = 0, // mA
    POWER, // mV
    CURRENT // mW
};

void tx1pow_get_val(tx1pow_ina3321_input in,
                      tx1pow_ina3321_measure measure,
                      unsigned int *val);
#endif // TX1POW_H_
