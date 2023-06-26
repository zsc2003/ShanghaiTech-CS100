#include <stdio.h>
#include <stdlib.h>

#include "../memcheck.h"

int **magic_square(int n) {
  int **data = malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++)
    data[i] = calloc(n, sizeof(int));
  int row = 0, col = n / 2;
  for (int i = 1; i <= n * n; i++) {
    data[row][col] = i;
    int nextRow = row == 0 ? n - 1 : row - 1;
    int nextCol = col == (n - 1) ? 0 : col + 1;
    if (data[nextRow][nextCol] != 0) {
      nextRow = row == (n - 1) ? 0 : row + 1;
      nextCol = col;
    }
    row = nextRow;
    col = nextCol;
  }
  return data;
}

int main(void) {
  int n = 10;
  int **m = magic_square(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%4d", m[i][j]);
    }
    printf("\n");
  }
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      free(&m[i][j]);
  return 0;
}
