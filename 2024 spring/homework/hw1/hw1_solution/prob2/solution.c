#include <stdio.h>
#include <limits.h>

int main(void) {
  int sum = 0;
  int max = INT_MIN;

  while (1) {
    int number;
    scanf("%d", &number);
    if (number == 0)
      break;
    sum += number;
    if (number > max)
      max = number;
  }

  printf("sum: %d\nmaximum: %d\n", sum, max);

  return 0;
}