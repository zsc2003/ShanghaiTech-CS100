#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#define MAX_LEN 51

char a[MAX_LEN], b[MAX_LEN];
int result[MAX_LEN];

void add_leading_zero(char *target, int length, int num_of_zeros) {
  for (int i = length; i >= 0; --i)
    target[i + num_of_zeros] = target[i];
  assert(target[length + num_of_zeros] != '\0');
  for (int i = 0; i != num_of_zeros; ++i)
    target[i] = '0';
  assert((int)strlen(target) == length + num_of_zeros);
}

void print_space(int n) {
  for (int i = 0; i != n; ++i)
    putchar(' ');
}

char int_to_char(int x) {
  assert(x >= 0 && x <= 15);
  if (x <= 9)
    return x + '0';
  else
    return x - 10 + 'a';
}

int char_to_int(char x) {
  assert(isxdigit(x) && !isupper(x));
  if (x <= '9')
    return x - '0';
  else
    return x - 'a' + 10;
}

void add(int length) {
  for (int i = 0; i != length; ++i)
    result[i] = char_to_int(a[i]) + char_to_int(b[i]);
  for (int i = length - 1; i > 0; --i) {
    if (result[i] > 15) {
      result[i - 1]++;
      result[i] -= 16;
    }
  }
  assert(result[0] <= 15);
}

int subtract(int length) {
  for (int i = 0; i != length; ++i)
    result[i] = char_to_int(a[i]) - char_to_int(b[i]);
  for (int i = length - 1; i > 0; --i) {
    if (result[i] < 0) {
      result[i - 1]--;
      result[i] += 16;
      assert(result[i] >= 0);
    }
  }
  assert(result[0] >= 0);
  for (int start = 0; start < length; ++start)
    if (result[start] != 0)
      return start;
  return length - 1;
}

int main(void) {
  char op;
  scanf("%c %s %s", &op, a, b);
  int len_a = strlen(a), len_b = strlen(b);
  int max_len = len_a < len_b ? len_b : len_a;
  print_space(max_len - len_a + 1);
  puts(a);
  putchar(op);
  print_space(max_len - len_b);
  puts(b);
  for (int i = 0; i != max_len + 1; ++i)
    putchar('-');
  puts("");

  if (len_a < len_b)
    add_leading_zero(a, len_a, len_b - len_a);
  else if (len_a > len_b)
    add_leading_zero(b, len_b, len_a - len_b);
  
  if (op == '+') {
    add(max_len);
    putchar(' ');
    for (int i = 0; i != max_len; ++i)
      putchar(int_to_char(result[i]));
    puts("");
  } else {
    int start = subtract(max_len);
    assert(start < max_len);
    print_space(start + 1);
    for (int i = start; i != max_len; ++i)
      putchar(int_to_char(result[i]));
    puts("");
  }
  return 0;
}