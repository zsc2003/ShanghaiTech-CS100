#include <stdio.h>

void fun(void) __attribute__((destructor));

void fun(void) {
  printf("Goodbye world!\n");
}

int main(void) {}