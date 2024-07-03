#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int randint(int l, int r) { // [l, r)
  return rand() % (r - l) + l;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    puts("Usage: ./data_gen <n> <max_length>");
    return 1;
  }
  int n = strtol(argv[1], NULL, 10);
  int max_length = strtol(argv[2], NULL, 10);
  printf("%d\n", n);
  while (n--) {
    int length = randint(1, max_length + 1);
    char *str = calloc(length + 1, 1);
    if (rand() % 2) {
      for (int i = 0; i < length / 2; ++i)
        str[i] = str[length - 1 - i] = randint(33, 127);
      if (length % 2 == 1)
        str[length / 2] = randint(33, 127);
    } else {
      for (int i = 0; i < length; ++i)
        str[i] = randint(33, 127);
    }
    printf("%d\n%s\n", length, str);
    free(str);
  }
  return 0;
}