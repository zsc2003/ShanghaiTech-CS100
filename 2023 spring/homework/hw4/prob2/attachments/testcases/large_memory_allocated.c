#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../memcheck.h"

int *ptr[1010];

int main(void) {
  int AL = 1024 * 1024 * 1024;
  int *huge = &AL, times = 0, allocated = 0;
  for (int i = 1; i < 999; ++i) {
    ptr[i] = malloc(AL * sizeof(int));
    ++times;
    if (ptr[i] == NULL)
      break;
    ++allocated;
  }

  for (int i = times; i < 999; ++i) {
    huge = calloc(AL, sizeof(int));
    free(huge);
    free(NULL);
  }

  for (int i = 1; i <= allocated; ++i)
    free(ptr[i]);

  for (int i = 1; i <= 1000000; ++i)
    free(NULL);

  return 0;
}