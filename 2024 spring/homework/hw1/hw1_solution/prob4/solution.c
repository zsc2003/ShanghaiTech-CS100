#include <limits.h>
#include <stdio.h>

int main(void) {
  int n;
  scanf("%d", &n);

  int max1 = INT_MIN, max2 = INT_MIN;
  int min1 = INT_MAX, min2 = INT_MAX;

  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);

    // Update max1, max2, min1, and min2
    if (x > max1) {
      max2 = max1;
      max1 = x;
    } else if (x > max2 && x != max1) {
      max2 = x;
    }

    if (x < min1) {
      min2 = min1;
      min1 = x;
    } else if (x < min2 && x != min1) {
      min2 = x;
    }
  }

  // Print the second maximum and second minimum
  printf("%d %d\n", max2, min2);

  return 0;
}