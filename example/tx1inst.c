#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#include "tx1inst.h"

int main(void)
{
    unsigned int val;
    float convFromMilli;
    char *wunit, *aunit, *vunit;
    int convert;

    convert = 0;

    if (convert) {
      convFromMilli = 0.001;
      wunit = "W";
      aunit = "A";
      vunit = "V";
    } else {
      convFromMilli = 1;
      wunit = "mW";
      aunit = "mA";
      vunit = "mV";
    }

    tx1pow_get_val(VDD_MUX, POWER, &val);
    printf("[POWER] main carrier board power input: %.3f%s\n", convFromMilli * val, wunit);
    tx1pow_get_val(VDD_5V_IO_SYS, POWER, &val);
    printf("[POWER] main carrier board 5V supply: %.3f%s\n", convFromMilli * val, wunit);
    tx1pow_get_val(VDD_3V3_SYS, POWER, &val);
    printf("[POWER] main carrier board 3.3V supply: %.3f%s\n", convFromMilli * val, wunit);
    tx1pow_get_val(VDD_3V3_IO, POWER, &val);
    printf("[POWER] carrier board 3.3V Sleep supply: %.3f%s\n", convFromMilli * val, wunit);
    tx1pow_get_val(VDD_1V8_IO, POWER, &val);
    printf("[POWER] main carrier board 1.8V supply: %.3f%s\n", convFromMilli * val, wunit);
    tx1pow_get_val(VDD_M2_IN, POWER, &val);
    printf("[POWER] 3.3V supply for M.2 Key E connector: %.3f%s\n", convFromMilli * val, wunit);
    printf("\n");

    tx1pow_get_val(VDD_MUX, CURRENT, &val);
    printf("[CURRENT] main carrier board power input: %.3f%s\n", convFromMilli * val, aunit);
    tx1pow_get_val(VDD_5V_IO_SYS, CURRENT, &val);
    printf("[CURRENT] main carrier board 5V supply: %.3f%s\n", convFromMilli * val, aunit);
    tx1pow_get_val(VDD_3V3_SYS, CURRENT, &val);
    printf("[CURRENT] main carrier board 3.3V supply: %.3f%s\n", convFromMilli * val, aunit);
    tx1pow_get_val(VDD_3V3_IO, CURRENT, &val);
    printf("[CURRENT] carrier board 3.3V Sleep supply: %.3f%s\n", convFromMilli * val, aunit);
    tx1pow_get_val(VDD_1V8_IO, CURRENT, &val);
    printf("[CURRENT] main carrier board 1.8V supply: %.3f%s\n", convFromMilli * val, aunit);
    tx1pow_get_val(VDD_M2_IN, CURRENT, &val);
    printf("[CURRENT] 3.3V supply for M.2 Key E connector: %.3f%s\n", convFromMilli * val, aunit);
    printf("\n");

    tx1pow_get_val(VDD_MUX, VOLTAGE, &val);
    printf("[VOLTAGE] main carrier board power input: %.3f%s\n", convFromMilli * val, vunit);
    tx1pow_get_val(VDD_5V_IO_SYS, VOLTAGE, &val);
    printf("[VOLTAGE] main carrier board 5V supply: %.3f%s\n", convFromMilli * val, vunit);
    tx1pow_get_val(VDD_3V3_SYS, VOLTAGE, &val);
    printf("[VOLTAGE] main carrier board 3.3V supply: %.3f%s\n", convFromMilli * val, vunit);
    tx1pow_get_val(VDD_3V3_IO, VOLTAGE, &val);
    printf("[VOLTAGE] carrier board 3.3V Sleep supply: %.3f%s\n", convFromMilli * val, vunit);
    tx1pow_get_val(VDD_1V8_IO, VOLTAGE, &val);
    printf("[VOLTAGE] main carrier board 1.8V supply: %.3f%s\n", convFromMilli * val, vunit);
    tx1pow_get_val(VDD_M2_IN, VOLTAGE, &val);
    printf("[VOLTAGE] 3.3V supply for M.2 Key E connector: %.3f%s\n", convFromMilli * val, vunit);

    return 0;

}
