#include <stdio.h>

double quick_pow(double x, int n) {
  double result = 1;
  for (; n; x *= x, n /= 2)
    if (n % 2)
      result *= x;
  return result;
}

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
    for (int i = 0; i <= degree; ++i)
      result += coeffs[i] * quick_pow(x, i);
    printf("%.3lf\n", result);
  }
  return 0;
}