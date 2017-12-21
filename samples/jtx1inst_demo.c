#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>

#include "jtx1inst.h"

int main(int argc, char *argv[])
{
    unsigned int val;
    unsigned long rate;
    float convFromMilli;
    char *wunit, *aunit, *vunit;
    int convert;

    bool printModuleInfo;
    bool printBoardInfo;
    int opt;

    printModuleInfo = false;
    printBoardInfo = false;

    if (argc < 2) {
      printf("Usage: %s [-bm]\n", argv[0]);
      exit(EXIT_FAILURE);
    }
    
    while ((opt = getopt(argc, argv, "bm")) != -1) {
	switch (opt) {
	case 'b':
	  printBoardInfo = true;
	  break;
	case 'm':
	  printModuleInfo = true;
	  break;
	default:
	  printf("Usage: %s [-bm]\n", argv[0]);
	  exit(EXIT_FAILURE);
	}
    }

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

    if (printModuleInfo) {
      jtx1_get_ina3221(VDD_IN, POWER, &val);
      printf("[POWER] module power input: %.3f%s\n", convFromMilli * val, wunit);
      jtx1_get_ina3221(VDD_CPU, POWER, &val);
      printf("[POWER] GPU power rail: %.3f%s\n", convFromMilli * val, wunit);
      jtx1_get_ina3221(VDD_CPU, POWER, &val);
      printf("[POWER] CPU power rail: %.3f%s\n", convFromMilli * val, wunit);
    }
    if (printBoardInfo) {
      jtx1_get_ina3221(VDD_MUX, POWER, &val);
      printf("[POWER] main carrier board power input: %.3f%s\n", convFromMilli * val, wunit);
      jtx1_get_ina3221(VDD_5V_IO_SYS, POWER, &val);
      printf("[POWER] main carrier board 5V supply: %.3f%s\n", convFromMilli * val, wunit);
      jtx1_get_ina3221(VDD_3V3_SYS, POWER, &val);
      printf("[POWER] main carrier board 3.3V supply: %.3f%s\n", convFromMilli * val, wunit);
      jtx1_get_ina3221(VDD_3V3_IO, POWER, &val);
      printf("[POWER] carrier board 3.3V Sleep supply: %.3f%s\n", convFromMilli * val, wunit);
      jtx1_get_ina3221(VDD_1V8_IO, POWER, &val);
      printf("[POWER] main carrier board 1.8V supply: %.3f%s\n", convFromMilli * val, wunit);
      jtx1_get_ina3221(VDD_M2_IN, POWER, &val);
      printf("[POWER] 3.3V supply for M.2 Key E connector: %.3f%s\n", convFromMilli * val, wunit);
    }
    printf("\n");

    if (printModuleInfo) {
      jtx1_get_ina3221(VDD_IN, CURRENT, &val);
      printf("[CURRENT] module power input: %.3f%s\n", convFromMilli * val, aunit);
      jtx1_get_ina3221(VDD_CPU, CURRENT, &val);
      printf("[CURRENT] GPU power rail: %.3f%s\n", convFromMilli * val, aunit);
      jtx1_get_ina3221(VDD_CPU, CURRENT, &val);
      printf("[CURRENT] CPU power rail: %.3f%s\n", convFromMilli * val, aunit);
    }
    if (printBoardInfo) {
      jtx1_get_ina3221(VDD_MUX, CURRENT, &val);
      printf("[CURRENT] main carrier board power input: %.3f%s\n", convFromMilli * val, aunit);
      jtx1_get_ina3221(VDD_5V_IO_SYS, CURRENT, &val);
      printf("[CURRENT] main carrier board 5V supply: %.3f%s\n", convFromMilli * val, aunit);
      jtx1_get_ina3221(VDD_3V3_SYS, CURRENT, &val);
      printf("[CURRENT] main carrier board 3.3V supply: %.3f%s\n", convFromMilli * val, aunit);
      jtx1_get_ina3221(VDD_3V3_IO, CURRENT, &val);
      printf("[CURRENT] carrier board 3.3V Sleep supply: %.3f%s\n", convFromMilli * val, aunit);
      jtx1_get_ina3221(VDD_1V8_IO, CURRENT, &val);
      printf("[CURRENT] main carrier board 1.8V supply: %.3f%s\n", convFromMilli * val, aunit);
      jtx1_get_ina3221(VDD_M2_IN, CURRENT, &val);
      printf("[CURRENT] 3.3V supply for M.2 Key E connector: %.3f%s\n", convFromMilli * val, aunit);
    }
    printf("\n");

    if (printModuleInfo) {
      jtx1_get_ina3221(VDD_IN, VOLTAGE, &val);
      printf("[VOLTAGE] module power input: %.3f%s\n", convFromMilli * val, vunit);
      jtx1_get_ina3221(VDD_CPU, VOLTAGE, &val);
      printf("[VOLTAGE] GPU power rail: %.3f%s\n", convFromMilli * val, vunit);
      jtx1_get_ina3221(VDD_CPU, VOLTAGE, &val);
      printf("[VOLTAGE] CPU power rail: %.3f%s\n", convFromMilli * val, vunit);
    }
    if (printBoardInfo) {
      jtx1_get_ina3221(VDD_MUX, VOLTAGE, &val);
      printf("[VOLTAGE] main carrier board power input: %.3f%s\n", convFromMilli * val, vunit);
      jtx1_get_ina3221(VDD_5V_IO_SYS, VOLTAGE, &val);
      printf("[VOLTAGE] main carrier board 5V supply: %.3f%s\n", convFromMilli * val, vunit);
      jtx1_get_ina3221(VDD_3V3_SYS, VOLTAGE, &val);
      printf("[VOLTAGE] main carrier board 3.3V supply: %.3f%s\n", convFromMilli * val, vunit);
      jtx1_get_ina3221(VDD_3V3_IO, VOLTAGE, &val);
      printf("[VOLTAGE] carrier board 3.3V Sleep supply: %.3f%s\n", convFromMilli * val, vunit);
      jtx1_get_ina3221(VDD_1V8_IO, VOLTAGE, &val);
      printf("[VOLTAGE] main carrier board 1.8V supply: %.3f%s\n", convFromMilli * val, vunit);
      jtx1_get_ina3221(VDD_M2_IN, VOLTAGE, &val);
      printf("[VOLTAGE] 3.3V supply for M.2 Key E connector: %.3f%s\n", convFromMilli * val, vunit);
    }
    printf("\n");

    if (printModuleInfo) {
      jtx1_get_temp(A0, &val);
      printf("[TEMPERATURE] A0: %dmC\n", val);
      jtx1_get_temp(CPU, &val);
      printf("[TEMPERATURE] CPU: %dmC\n", val);
      jtx1_get_temp(GPU, &val);
      printf("[TEMPERATURE] GPU: %dmC\n", val);
      jtx1_get_temp(PLL, &val);
      printf("[TEMPERATURE] PLL: %dmC\n", val);
    }
    if (printBoardInfo) {
      jtx1_get_temp(PMIC, &val);
      printf("[TEMPERATURE] PMIC: %dmC\n", val);
      jtx1_get_temp(TDIODE, &val);
      printf("[TEMPERATURE] TDIODE: %dmC\n", val);
      jtx1_get_temp(TBOARD, &val);
      printf("[TEMPERATURE] TBOARD: %dmC\n", val);
      jtx1_get_temp(FAN, &val);
      printf("[TEMPERATURE] FAN: %dmC\n", val);
    }
    printf("\n");

    if (printModuleInfo) {
      jtx1_get_rate(EMC_RATE, &rate);
      printf("[FREQ] EMC: %luHz\n", rate);
      jtx1_get_rate(GPU_RATE, &rate);
      printf("[FREQ] GPU: %luHz\n", rate);
      jtx1_get_rate(CPU0_RATE, &rate);
      printf("[FREQ] CPU0: %luHz\n", rate);
      jtx1_get_rate(CPU1_RATE, &rate);
      printf("[FREQ] CPU1: %luHz\n", rate);
      jtx1_get_rate(CPU2_RATE, &rate);
      printf("[FREQ] CPU2: %luHz\n", rate);
      jtx1_get_rate(CPU3_RATE, &rate);
    }
    
    return 0;

}
