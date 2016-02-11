#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bench.h"
#include "numeric.h"
#include "debug.h"
#include "cuda.h"
#include "tx1rate.h"
#include "tx1pow.h"
#include "tx1temp.h"

void comp_table_v1(struct table_v1 *table,
                   const size_t samples,
                   const unsigned long *gpu_rate,
                   const unsigned long *emc_rate,
                   const size_t gpu_rate_sz,
                   const size_t emc_rate_sz)
{
    size_t i, j, k;
    size_t index;

    float convFromMilli = 0.001;
    unsigned int gpu_pow;
    unsigned long gpu_temp;
    unsigned long gpu_pow_store[samples];
    unsigned long gpu_temp_store[samples];
    double gpu_pow_avg, gpu_temp_avg;
    double dgemm_time, dgemm_gflops;
    
    struct table_v1 results[gpu_rate_sz*emc_rate_sz];

    inf("Starting benchmark...");
    inf("GPU_RATE [Hz], EMC_RATE [Hz], GPU_POW [W], GPU_THERM [C], GFLOPS, GFLOPS/GPU_POW");

    for (i = 0; i < gpu_rate_sz; i++) {

        set_gpu_rate(gpu_rate[i]);
    
        for (j = 0; j < emc_rate_sz; j++) {

            set_emc_rate(emc_rate[j]);

            for (k = 0; k < samples; k++) {
                sleep(1);
                // find FLOPS
                dgemm(&dgemm_time, &dgemm_gflops);
                // get gpu's power consumption
                tx1pow_get_val(VDD_GPU, POWER, &gpu_pow);
                // get gpu's temperature 
                tx1temp_get_val(GPU, &gpu_temp);
                // store power consumption sample
                gpu_pow_store[k] = gpu_pow;
                // store gpu's temperature sample
                gpu_temp_store[k] = gpu_temp;
            }

            average(&gpu_pow_avg, gpu_pow_store, samples);
            average(&gpu_temp_avg, gpu_temp_store, samples);

            index = i*emc_rate_sz + j;
            results[index].gpu_rate = gpu_rate[i];
            results[index].emc_rate = emc_rate[j];
            results[index].gpu_pow = gpu_pow_avg * convFromMilli;
            results[index].gpu_therm = gpu_temp_avg * 0.001;
            results[index].gflops = dgemm_gflops;

            printf(GRN "[%lu] " RESET "%lu, %lu, %.3f, %.3f, %.3f, %.3f\n",
                   index,
                   results[index].gpu_rate,
                   results[index].emc_rate,
                   results[index].gpu_pow,
                   results[index].gpu_therm,
                   results[index].gflops,
                   results[index].gflops/results[index].gpu_pow);
        }
    
    }

    // return to defaults
    set_gpu_rate(gpu_rate[0]);
    // return to defaults
    set_emc_rate(emc_rate[0]);
    // store results
    memcpy(table, results, sizeof(results));

};

void find_table_v1_optimum(const struct table_v1 *results,
                           const size_t gpu_rate_sz,
                           const size_t emc_rate_sz)
{
    double perf_per_mW_best;
    double perf_per_mW;
    size_t best_index;
    size_t i;

    if (results == NULL) {

        fprintf(stderr, "Error structure is empty.\n");
        exit(EXIT_FAILURE);

    } else {

        perf_per_mW_best = results[0].gflops / results[0].gpu_pow;
        best_index = 0;

        for (i = 0; i < gpu_rate_sz*emc_rate_sz; i++) {
            perf_per_mW = results[i].gflops / results[i].gpu_pow;
            if (perf_per_mW_best < perf_per_mW) {
                perf_per_mW_best = perf_per_mW;
                best_index = i;
            }
        }

        inf("Found solution...");

        printf(RED "[%lu] " RESET "%lu, %lu, %f, %f, %f, %f\n",
               best_index,
               results[best_index].gpu_rate,
               results[best_index].emc_rate,
               results[best_index].gpu_pow,
               results[best_index].gpu_therm,
               results[best_index].gflops,
               perf_per_mW);
        
    }
    
}

void print_table_v1(const struct table_v1 *table,
                    const size_t gpu_rate_sz,
                    const size_t emc_rate_sz)
{
    size_t i;
    for (i = 0; i < gpu_rate_sz*emc_rate_sz; i++) {
        printf(GRN "[%lu] " RESET "%lu, %lu, %f, %f, %f, %f\n",
               i,
               table[i].gpu_rate,
               table[i].emc_rate,
               table[i].gpu_pow,
               table[i].gpu_therm,
               table[i].gflops,
               table[i].gflops/table[i].gpu_pow);
    }
}
