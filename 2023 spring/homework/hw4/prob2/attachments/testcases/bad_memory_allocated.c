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
    ptr[i][0] = i;
  }
  while (times < 999) {
    huge = malloc(AL * sizeof(int));
    ++times;
    if (huge != NULL) {
      huge[0] = times;
      free(huge);
      break;
    }
    AL /= 2;
  }

  for (int i = times; i < 999; ++i) {
    huge = calloc(AL, sizeof(int));
    huge[0] = i;
    free(huge);
    if (i > 800)
      free(huge);
    free(NULL);
  }
  free(huge);

  for (int i = 1; i <= 1000000; ++i)
    free(NULL);

  for (int i = allocated; i >= 2; --i)
    free(ptr[i]);

  return 0;
}