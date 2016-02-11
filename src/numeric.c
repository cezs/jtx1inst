#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "numeric.h"

void average(double *result, const unsigned long *v, const size_t sz)
{
    size_t i;
    unsigned long sum = 0;
    double ans = 0.0;
    
    for (i = 0; i < sz; i++) {
        sum += v[i];
    }

    ans = ((double)sum/sz);

    *result = ans;

    if (*result < 0.0) {
        fprintf(stderr, "Error assigning value.\n");
        exit(EXIT_FAILURE);
    }
    
}
