/**
 * @file numeric.h
 * @author cs
 * @brief This header file contains the numerical functions.
 */
#ifndef NUMERIC_H
#define NUMERIC_H

#include <stdlib.h>

/**
 * @brief Compute average value of array
 *
 * @param result Output's reference
 * @param v Input array
 * @param sz Length of input array
 */
void average(double *result, const unsigned long *v, const size_t sz);

#endif
