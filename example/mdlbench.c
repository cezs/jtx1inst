#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#include "tx1inst.h"
#include "bench.h"
#include "tx1.h" /* jtx1_gpu_freqs, jtx1_emc_freqs */

int main(void)
{
  int gpu_rate_sz = 2;
  int emc_rate_sz = 2;
  struct table_v1 results[gpu_rate_sz*emc_rate_sz];
  comp_table_v1(results, 1, jtx1_gpu_freqs, jtx1_emc_freqs, gpu_rate_sz, emc_rate_sz);
  find_table_v1_optimum(results, gpu_rate_sz, emc_rate_sz);
  return 0;
}
