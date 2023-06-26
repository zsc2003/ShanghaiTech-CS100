#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../memcheck.h"

int *ptr[1010];

int main(void) {
  for (int i = 1; i < 1000; ++i) {
    if (i & 1)
      ptr[i] = malloc((i / 20) * sizeof(int));
    else
      ptr[i] = calloc(i / 20, sizeof(int));
  }

  for (int i = 20; i < 1000; ++i)
    if (ptr[i] != NULL)
      ptr[i][0] = i;

  for (int i = 1; i <= 1000000; ++i)
    free(NULL);

  for (int i = 999; i >= 1; --i) {
    free(ptr[i]);
    free(NULL);
  }

  return 0;
}