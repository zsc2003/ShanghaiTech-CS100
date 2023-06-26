#include <stdio.h>

int main()
{
    double num1 = 0, num2 = 0;
    char operator = ' ';
    int a = scanf("%lf,%c,%lf", &num1, &operator, & num2);
    printf("%d", a);
    switch (operator)
    {
    case '+':
        printf("%lf", num1 + num2);
        break;
    case '-':
        printf("%lf", num1 - num2);
        break;
    case '*':
        printf("%lf", num1 * num2);
        break;
    case '/':
        printf("%lf", num1 / num2);
        break;
    default:
        printf("invalid syntax\n");
        break;
    }
}