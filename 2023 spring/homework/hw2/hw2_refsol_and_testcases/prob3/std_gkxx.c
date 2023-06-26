#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#define LEN 50

int a[LEN], b[LEN], result[LEN];

int char_to_val(int c) {
  assert(isxdigit(c) && !isupper(c));
  if (isdigit(c))
    return c - '0';
  else
    return 10 + c - 'a';
}

char val_to_char(int val) {
  assert(val < 16 && val >= 0);
  if (val <= 9)
    return val + '0';
  else
    return val - 10 + 'a';
}

int read_hex_number(int *storage) {
  int c = getchar();
  while (isspace(c))
    c = getchar();
  int cnt = 0;
  while (!isspace(c)) {
    *storage++ = char_to_val(c);
    ++cnt;
    c = getchar();
  }
  return cnt;
}

void print_hex_number(int *number, int length) {
  while (length--)
    putchar(val_to_char(*number++));
}

void padding(int n) {
  printf("%*s", n, "");
}

void reverse(int *arr, int len) {
  for (int i = 0, j = len - 1; i < j; ++i, --j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
  }
}

int add(int *longer, int len_long, int *shorter, int len_short) {
  assert(longer == a || longer == b);
  assert(shorter == a || shorter == b);
  assert(longer != shorter);
  assert(len_long >= len_short);
  
  reverse(longer, len_long);
  reverse(shorter, len_short);
  for (int i = 0; i != len_short; ++i)
    result[i] = longer[i] + shorter[i];
  for (int i = len_short; i != len_long; ++i)
    result[i] = longer[i];
  for (int i = 0; i < len_long - 1; ++i) {
    if (result[i] >= 16) {
      ++result[i + 1];
      result[i] -= 16;
      assert(result[i] < 16);
    }
  }
  assert(result[len_long - 1] < 16);
  reverse(result, len_long);
  return len_long;
}

int subtract(int len_a, int len_b) {
  assert(len_a >= len_b);
  
  reverse(a, len_a);
  reverse(b, len_b);
  for (int i = 0; i != len_b; ++i)
    result[i] = a[i] - b[i];
  for (int i = len_b; i != len_a; ++i)
    result[i] = a[i];
  for (int i = 0; i < len_a - 1; ++i) {
    if (result[i] < 0) {
      result[i] += 16;
      assert(result[i] >= 0);
      --result[i + 1];
    }
  }
  assert(result[len_a - 1] >= 0);
  while (len_a >= 1 && result[len_a - 1] == 0)
    --len_a;
  if (len_a == 0)
    len_a = 1;
  reverse(result, len_a);
  return len_a;
}

int main(void) {
  char op;
  scanf("%c", &op);
  int len_a = read_hex_number(a);
  int len_b = read_hex_number(b);
  int max_len = len_a > len_b ? len_a : len_b;
  padding(max_len + 1 - len_a);
  print_hex_number(a, len_a);
  puts("");
  putchar(op);
  padding(max_len - len_b);
  print_hex_number(b, len_b);
  puts("");
  for (int i = 0; i < max_len + 1; ++i)
    putchar('-');
  puts("");
  int len_result = 0;
  if (op == '+') {
    if (len_a < len_b)
      len_result = add(b, len_b, a, len_a);
    else
      len_result = add(a, len_a, b, len_b);
  } else {
    len_result = subtract(len_a, len_b);
  }
  padding(max_len + 1 - len_result);
  print_hex_number(result, len_result);
  puts("");
  return 0;
}