#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isPalindrome(const char *str, int length) {
  for (int i = 0, j = length - 1; i < j; ++i, --j)
    if (str[i] != str[j])
      return false;
  return true;
}

int main(void) {
  int n;
  scanf("%d", &n);
  while (n--) {
    int length;
    scanf("%d", &length);
    char *str = malloc(length + 1);
    scanf("%s", str);
    if (isPalindrome(str, length))
      puts("Yes");
    else
      puts("No");
    free(str);
  }
  return 0;
}