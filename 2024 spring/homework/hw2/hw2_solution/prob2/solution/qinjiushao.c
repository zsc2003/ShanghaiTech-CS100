#include <stdio.h>

int main(void) {
  int degree;
  scanf("%d", &degree);
  static double coeffs[31];
  for (int i = 0; i <= degree; ++i)
    scanf("%lf", coeffs + i);
  int query;
  scanf("%d", &query);
  while (query--) {
    double x;
    scanf("%lf", &x);
    double result = 0;
    for (int i = degree; i >= 0; --i)
      result = result * x + coeffs[i];
    printf("%.3lf\n", result);
  }
  return 0;
}