#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#define MAX_LEN 50

char a[MAX_LEN + 1], b[MAX_LEN + 1];
int result[MAX_LEN];

int to_int(char hexchar) {
  assert(isxdigit(hexchar) && !isupper(hexchar));
  if (isdigit(hexchar))
    return hexchar - '0';
  else
    return hexchar - 'a' + 10;
}

char to_hexchar(int val) {
  assert(val >= 0 && val < 16);
  if (val <= 9)
    return val + '0';
  else
    return val - 10 + 'a';
}

void padding(int num) {
  assert(num >= 0);
  for (int i = 0; i != num; ++i)
    putchar(' ');
}

void reverse(char *str, int len) {
  for (int i = 0, j = len - 1; i < j; ++i, --j) {
    char tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
  }
}

void add(char *longer, int len_longer, char *shorter, int len_shorter) {
  assert(len_longer >= len_shorter);
  assert(strlen(longer) == (size_t)len_longer);
  assert(strlen(shorter) == (size_t)len_shorter);

  for (int i = 0; i != len_shorter; ++i)
    result[i] = to_int(longer[i]) + to_int(shorter[i]);

  for (int i = len_shorter; i != len_longer; ++i)
    result[i] = to_int(longer[i]);

  for (int i = 0; i < len_longer - 1; ++i) {
    if (result[i] >= 16) {
      result[i] -= 16;
      ++result[i + 1];
      assert(result[i] >= 0 && result[i] < 16);
    }
  }

  assert(result[len_longer - 1] >= 0 && result[len_longer - 1] < 16);
}

int subtract(int len_a, int len_b) {
  assert(len_a >= len_b);

  for (int i = 0; i != len_b; ++i)
    result[i] = to_int(a[i]) - to_int(b[i]);

  for (int i = len_b; i != len_a; ++i)
    result[i] = to_int(a[i]);

  for (int i = 0; i < len_a - 1; ++i) {
    if (result[i] < 0) {
      result[i] += 16;
      --result[i + 1];
      assert(result[i] >= 0);
    }
  }

  assert(result[len_a - 1] >= 0);

  int end = len_a;
  while (end >= 1 && result[end - 1] == 0)
    --end;
  if (end == 0)
    end = 1;
  return end;
}

int main(void) {
  char op;
  scanf("%c%s%s", &op, a, b);
  int len_a = strlen(a), len_b = strlen(b);
  int len_max = len_a < len_b ? len_b : len_a;
  padding(len_max - len_a + 1);
  puts(a);
  putchar(op);
  padding(len_max - len_b);
  puts(b);
  for (int i = 0; i != len_max + 1; ++i)
    putchar('-');
  puts("");

  reverse(a, len_a);
  reverse(b, len_b);

  int len_result;
  if (op == '+') {
    if (len_a < len_b)
      add(b, len_b, a, len_a);
    else
      add(a, len_a, b, len_b);
    len_result = len_max;
  } else
    len_result = subtract(len_a, len_b);

  assert(len_result >= 0);

  padding(len_max - len_result + 1);
  for (int i = len_result - 1; i >= 0; --i)
    putchar(to_hexchar(result[i]));
  puts("");
  return 0;
}
