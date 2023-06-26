#include "memcheck.h"

int main(void) {
  int **matrix = malloc(sizeof(int *) * 10);
  for (int i = 0; i != 10; ++i)
    matrix[i] = malloc(sizeof(int) * 5);
  // do some calculations
  for (int i = 0; i != 10; ++i)
    free(matrix[i]);
  free(matrix);
  matrix = NULL;
  free(matrix); // free(NULL) should do nothing
  return 0;
}