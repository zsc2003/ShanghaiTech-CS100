#include <ctype.h>
#include <stdio.h>
#include <string.h>

int positive_mod(int i, int mod) {
  return (i % mod + mod) % mod;
}

int decode_char(int curr_char, int base_char, int key, int mod) {
  return base_char + positive_mod(curr_char - base_char - key, mod);
}

int main(void) {
  int key;
  scanf("%d", &key);
  getchar();
  int curr_char;
  while ((curr_char = getchar()) != EOF && curr_char != '\n') {
    if (isupper(curr_char)) {
      putchar(decode_char(curr_char, 'A', key, 26));
    } else if (islower(curr_char)) {
      putchar(decode_char(curr_char, 'a', key, 26));
    } else if (isdigit(curr_char)) {
      putchar(decode_char(curr_char, '0', key, 10));
    } else {
      putchar(curr_char);
    }
  }
  putchar('\n');
  return 0;
}
