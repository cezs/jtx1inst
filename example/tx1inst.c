#include <stdio.h>

#include "tx1inst.h"

int main(void)
{
    unsigned int val;
    float convFromMilli = 0.001;

    tx1pow_get_val(VDD_MUX, POWER, &val);
    printf("main carrier board power input: %.3fW\n", convFromMilli * val);
    tx1pow_get_val(VDD_5V_IO_SYS, POWER, &val);
    printf("main carrier board 5V supply: %.3fW\n", convFromMilli * val);
    tx1pow_get_val(VDD_3V3_SYS, POWER, &val);
    printf("main carrier board 3.3V supply: %.3fW\n", convFromMilli * val);
    tx1pow_get_val(VDD_3V3_IO, POWER, &val);
    printf("carrier board 3.3V Sleep supply: %.3fW\n", convFromMilli * val);
    tx1pow_get_val(VDD_1V8_IO, POWER, &val);
    printf("main carrier board 1.8V supply: %.3fW\n", convFromMilli * val);
    tx1pow_get_val(VDD_M2_IN, POWER, &val);
    printf("3.3V supply for M.2 Key E connector: %.3fW\n", convFromMilli * val);
    printf("\n");

    tx1pow_get_val(VDD_MUX, VOLTAGE, &val);
    printf("main carrier board power input: %.3fV\n", convFromMilli * val);
    tx1pow_get_val(VDD_5V_IO_SYS, VOLTAGE, &val);
    printf("main carrier board 5V supply: %.3fV\n", convFromMilli * val);
    tx1pow_get_val(VDD_3V3_SYS, VOLTAGE, &val);
    printf("main carrier board 3.3V supply: %.3fV\n", convFromMilli * val);
    tx1pow_get_val(VDD_3V3_IO, VOLTAGE, &val);
    printf("carrier board 3.3V Sleep supply: %.3fV\n", convFromMilli * val);
    tx1pow_get_val(VDD_1V8_IO, VOLTAGE, &val);
    printf("main carrier board 1.8V supply: %.3fV\n", convFromMilli * val);
    tx1pow_get_val(VDD_M2_IN, VOLTAGE, &val);
    printf("3.3V supply for M.2 Key E connector: %.3fV\n", convFromMilli * val);
    printf("\n");

    tx1pow_get_val(VDD_MUX, CURRENT, &val);
    printf("main carrier board power input: %.3fA\n", convFromMilli * val);
    tx1pow_get_val(VDD_5V_IO_SYS, CURRENT, &val);
    printf("main carrier board 5V supply: %.3fA\n", convFromMilli * val);
    tx1pow_get_val(VDD_3V3_SYS, CURRENT, &val);
    printf("main carrier board 3.3V supply: %.3fA\n", convFromMilli * val);
    tx1pow_get_val(VDD_3V3_IO, CURRENT, &val);
    printf("carrier board 3.3V Sleep supply: %.3fA\n", convFromMilli * val);
    tx1pow_get_val(VDD_1V8_IO, CURRENT, &val);
    printf("main carrier board 1.8V supply: %.3fA\n", convFromMilli * val);
    tx1pow_get_val(VDD_M2_IN, CURRENT, &val);
    printf("3.3V supply for M.2 Key E connector: %.3fA\n", convFromMilli * val);

    return 0;
}
