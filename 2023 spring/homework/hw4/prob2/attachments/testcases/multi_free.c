#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../memcheck.h"

#define M 100

long long seed = 0x88abcdef137584a6, S = 1;

long long RNG(void) {
  long long x = ((S >> 10) & seed) ^ ((S << 13) & seed) ^ (S << 2) ^ (S << 20);
  S = x;
  return S;
}

int *ptr[1010], *void_ptr[M];

int main(void) {
  int AL = 1024, n = 50;
  for (int i = 0; i < n; ++i)
    ptr[i] = malloc(AL * sizeof(int));

  for (int i = 0; i < M; ++i)
    void_ptr[i] = (void *)(ptr + i + 1);

  for (int j = 1; j <= 10; ++j) {
    const int free_times = 100;
    for (int k = 1; k <= free_times; ++k) {
      free(void_ptr[RNG() % M]);
      free(ptr[RNG() % n]);
    }

    for (int i = 0; i < n; ++i)
      ptr[i] = malloc(AL * sizeof(int));
  }

  return 0;
}