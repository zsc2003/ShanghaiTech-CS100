#include <stdio.h>

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int min_element(int *a, int l, int r) {
  int pos = l;
  while (l != r) {
    if (a[l] < a[pos])
      pos = l;
    ++l;
  }
  return pos;
}

void sort(int *a, int n) {
  for (int i = 0; i < n - 1; ++i)
    swap(&a[i], &a[min_element(a, i, n)]);
}

int main(void) {
  int n;
  scanf("%d", &n);
  while (n--) {
    int x;
    scanf("%d", &x);
    if (x > 9999) {
      printf("%d contains more than 4 digits.\n", x);
      continue;
    }
    if (x % 1111 == 0) {
      printf("%d is a repdigit.\n", x);
      continue;
    }
    while (x != 6174) {
      int digits[4] = {x / 1000, x / 100 % 10, x / 10 % 10, x % 10};
      sort(digits, 4);
      int large =
          digits[3] * 1000 + digits[2] * 100 + digits[1] * 10 + digits[0];
      int small =
          digits[0] * 1000 + digits[1] * 100 + digits[2] * 10 + digits[3];
      x = large - small;
      printf("%d - %d = %d\n", large, small, x);
    }
  }
  return 0;
}