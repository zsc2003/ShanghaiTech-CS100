#include <assert.h>
#include <math.h>
#include <stdio.h>

void no_solution(void) {
  puts("No solution.");
}

void infinite_solutions(void) {
  puts("x\\in\\mathbb{R}");
}

void solve_linear(int b, int c) {
  if (b == 0) {
    if (c == 0)
      infinite_solutions();
    else
      no_solution();
  } else
    printf("x = %.3lf\n", -1.0 * c / b);
}

void solve_quadratic(int a, int b, int c) {
  assert(a != 0);
  int delta = b * b - 4 * a * c;
  if (delta < 0)
    no_solution();
  else if (delta > 0) {
    double x1 = (-b - sqrt(delta)) / (2.0 * a);
    double x2 = (-b + sqrt(delta)) / (2.0 * a);
    if (x1 > x2) {
      double tmp = x1;
      x1 = x2;
      x2 = tmp;
    }
    printf("x1 = %.3lf, x2 = %.3lf", x1, x2);
  } else {
    // delta == 0
    double x = -b / (2.0 * a);
    printf("x1 = x2 = %.3lf\n", x);
  }
}

int main(void) {
  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  if (a == 0)
    solve_linear(b, c);
  else
    solve_quadratic(a, b, c);
  return 0;
}