/**
 * @file bench.h
 * @author cs
 * @brief This header file contains the functions for computing bnechmark, 
 * printing the it's values, and finding optimal entries.
 */
#ifndef BENCH_H
#define BENCH_H

#include <stdlib.h>

/**
 * @brief Structure storing benchmark entries
 */
struct table_v1 {
    unsigned long gpu_rate; ///< GPU rate selection
    unsigned long emc_rate; ///< EMC rate selection
    double gpu_pow; ///< Measured GPU power consumption
    double gpu_therm; ///< Measured GPU temperature
    double gflops;  ///< Measured FLOPS agains a kernel
};

/**
 * @brief Perform benchmarking computation
 * 
 * This function benchmarks a given kernel and saves
 * results in table.
 *
 * @param table See ::table_v1
 * @param samples Number of samples to be taken on each iteration
 * @param gpu_rate GPU's rate entries
 * @param emc_rate EMC's rate entries
 * @param gpu_rate_sz Number of GPU's rate entries
 * @param emc_rate_sz Number of EMC's rate entries
 */
void comp_table_v1(struct table_v1 *table,
                   const size_t samples,
                   const unsigned long *gpu_rate,
                   const unsigned long *emc_rate,
                   const size_t gpu_rate_sz,
                   const size_t emc_rate_sz);

/**
 * @brief Find optimal combination in benchmark
 * 
 * This function basically finds entry in benchmark's table
 * which has highest FLOPS/Watt ratio.
 *
 * @param results See ::table_v1
 * @param gpu_rate_sz Number of GPU's rate entries
 * @param emc_rate_sz Number of EMC's rate entries
 */
void find_table_v1_optimum(const struct table_v1 *results,
                           const size_t gpu_rate_sz,
                           const size_t emc_rate_sz);

/**
 * @brief Print benchmark's values.
 * 
 * This function prints benchmark's values stored in table.
 *
 * @param table See ::table_v1
 * @param gpu_rate_sz Number of GPU's rate entries
 * @param emc_rate_sz Number of EMC's rate entries
 */
void print_table_v1(const struct table_v1 *table,
                    const size_t gpu_rate_sz,
                    const size_t emc_rate_sz);

#endif
