#include "memcheck.h"

// Use __attribute__((__unused__)) to suppress warning on unused variable 'p'.
void happy(void *p __attribute__((__unused__))) {}

int main(void) {
  double *p = malloc(sizeof(double) * 100);
  free(p + 10);
  free(p);
  free(p);
  char *q = calloc(10, 1);
  float *r = malloc(0);
  happy(q);
  happy(r);
  return 0;
}