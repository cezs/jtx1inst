#ifndef BENCH_H
#define BENCH_H

#include <stdlib.h>

struct table_v1 {
    unsigned long gpu_rate;
    unsigned long emc_rate;
    double gpu_pow;
    double gpu_therm;
    double gflops;
};

void comp_table_v1(struct table_v1 *table,
                   const size_t samples,
                   const unsigned long *gpu_rate,
                   const unsigned long *emc_rate,
                   const size_t gpu_rate_sz,
                   const size_t emc_rate_sz);
void find_table_v1_optimum(const struct table_v1 *results,
                           const size_t gpu_rate_sz,
                           const size_t emc_rate_sz);
void print_table_v1(const struct table_v1 *table,
                    const size_t gpu_rate_sz,
                    const size_t emc_rate_sz);

#endif
