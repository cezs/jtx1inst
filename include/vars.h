#ifndef VARS_H
#define VARS_H

#include <stdlib.h>

struct platform_vars
{
    unsigned long *gpu_freqs; ///< GPU's operating frequencies (Hz)
    unsigned long *emc_freqs; ///< external memory controller frequencies (Hz)
    unsigned long *cpu_freqs; ///< CPU's operating frequencies (Hz)
    size_t gpu_freqs_sz;
    size_t emc_freqs_sz;
    size_t cpu_freqs_sz;
};


/**
 * @brief Structure holding measurements.
 *
 * The purpose of this structure is to encapsulate measurments
 * performed during evaluation of different parameters combinations.
 * /home/cs/Downloads
 * SoC -- system-on-chip
 * PLL -- phase-locked loop 
 * EMC -- external memory controller 
 */
struct platform_metrics
{
    int ram_sz_util; ///< memory utilisation (% of MB)
    int *cpu_freq_util; ///< all cpu cores utilisation (% of rate)
    int gpu_bw_util; ///< GPU's bandwidth utilisation (% of bandwitdh)
    long gpu_bw; ///< GPU's bandwidth (Hz)

    long gpu_pow; ///< GPU's power consumption (mW)
    long cpu_pow; ///< CPU's power consumption (mW)
    long soc_pow; ///< SoC's power consumption (mW)

    int emc_temp; ///< MEM-therm on-chip thermal zone (C)
    int gpu_temp; ///< GPU-therm on-chip thermal zone (C)
    int cpu_temp; ///< CPU-therm on-chip thermal zone (C)
    int pll_temp; ///< PLL-therm on-chip thermal zone (C)
    int pcb_temp; ///< Tboard_tegra on-module thermal zone (C)
    int pcb2_temp; ///< Tdiode_tegra on-module thermal zone (C)    
};

struct app_metrics
{
    int fps;
    int flops;
};

#endif
