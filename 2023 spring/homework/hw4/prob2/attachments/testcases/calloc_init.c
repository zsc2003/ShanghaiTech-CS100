#include <stdlib.h>
#include <stdio.h>

#include "../memcheck.h"

int main(void) {
  int n = 100;
  for (int i = 0; i != n; ++i) {
    int *ptr = calloc(1000, sizeof(int));
    for (int i = 0; i != 1000; ++i)
      printf("%d ", ptr[i]);
    puts("");
    if (i % 3 != 2)
      free(ptr);
  }
  return 0;
}