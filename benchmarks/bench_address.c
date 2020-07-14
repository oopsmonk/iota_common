#include <stdio.h>
#include <sys/time.h>

#include "model/address.h"
#include "model/transaction.h"

#include "KeccakP-1600-SnP.h"
#ifdef KERL_SIMD_TIMES2
#include "SIMD128-config.h"
#elif KERL_SIMD_TIMES4
#include "SIMD256-config.h"
#endif

#ifdef KERL_TIMES2
#include "KeccakP-1600-times2-SnP.h"
#elif KERL_TIMES4
#include "KeccakP-1600-times4-SnP.h"
#elif KERL_TIMES8
#include "KeccakP-1600-times8-SnP.h"
#endif

#define NUM_OF_TIMES 20

static tryte_t *test_seed =
    (tryte_t *)"ABCDEFGHIJKLMNOPQRSTUVWXYZ9ABCDEFGHIJKLMNOPQRSTUVWXYZ9ABCDEFGHIJKLMNOPQRSTUVWXYZ9";

long diff_in_microsec(struct timeval start, struct timeval end) {
  long seconds = (end.tv_sec - start.tv_sec);
  return ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
}

void bench_gen_address(addr_security_t security) {
  struct timeval start, end;
  long run_time = 0;
  long min = 0, max = 0, sum = 0;
  tryte_t addr[NUM_TRYTES_ADDRESS];

  for (int i = 0; i < NUM_OF_TIMES; i++) {
    gettimeofday(&start, NULL);
    generate_address_trytes(test_seed, i, security, addr);
    gettimeofday(&end, NULL);
    run_time = diff_in_microsec(start, end);
    max = (i == 0 || run_time > max) ? run_time : max;
    min = (i == 0 || run_time < min) ? run_time : min;
    sum += run_time;
  }
  printf("security %d:\t%.3f\t%.3f\t%.3f\t%.3f\n", security, (min / 1000.0), (max / 1000.0),
         (sum / NUM_OF_TIMES) / 1000.0, sum / 1000.0);
}

int main() {
  printf("Kerl: %s \n", KeccakP1600_implementation);
#if KERL_SIMD_TIMES2
  printf(", %s\n", KeccakP1600times2_implementation_config);
#elif KERL_SIMD_TIMES4
  printf(", %s\n", KeccakP1600times4_implementation_config);
#elif KERL_TIMES2
  printf(", %s\n", KeccakP1600times2_implementation);
#elif KERL_TIMES4
  printf(", %s\n", KeccakP1600times4_implementation);
#elif KERL_TIMES8
  printf(", %s\n", KeccakP1600times8_implementation);
#else
  printf("\n");
#endif

  printf("Bench address generation: %d times\n\t\tmin(ms)\tmax(ms)\tavg(ms)\ttotal(ms)\n", NUM_OF_TIMES);
  bench_gen_address(ADDR_SECURITY_LOW);
  bench_gen_address(ADDR_SECURITY_MEDIUM);
  bench_gen_address(ADDR_SECURITY_HIGH);
  return 0;
}