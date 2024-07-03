#include <stdio.h>

int main(void) {
  while (1) {
    double x, y;
    char op;
    scanf("%lf %c %lf", &x, &op, &y);
    if (op == '+')
      printf("%lf + %lf == %lf\n", x, y, x + y);
    else if (op == '-')
      printf("%lf - %lf == %lf\n", x, y, x - y);
    else if (op == '*')
      printf("%lf * %lf == %lf\n", x, y, x * y);
    else if (op == '/')
      printf("%lf / %lf == %lf\n", x, y, x / y);
    else
      printf("Unknown operator!\n");
    printf("Do you want to continue? (y/n)\n");
    char yn;
    scanf(" %c", &yn);
    if (yn != 'y')
      break;
  }
  return 0;
}