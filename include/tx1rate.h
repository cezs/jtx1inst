/**
 * @file tx1rate.h
 * @author cs
 * @brief This header file contains the functions for setting and reading
 * Jetson TX1's GPU and EMC frequncies.
 */
#ifndef TX1RATE_H
#define TX1RATE_H

/**
 * @brief Set GPU operation frequency
 * @param gpu_rate Choice of frequency
 */
void set_gpu_rate(const unsigned long gpu_rate);

/**
 * @brief Read GPU operation frequency
 * @param gpu_rate Output's reference
 */
void get_gpu_rate(unsigned long *gpu_rate);

/**
 * @brief Set EMC operation frequency
 * @param emc_rate Choice of frequency
 */
void set_emc_rate(const unsigned long emc_rate);

/**
 * @brief Read EMC operation frequency
 * @param emc_rate Output's reference
 */
void get_emc_rate(unsigned long *gpu_rate);

#endif
