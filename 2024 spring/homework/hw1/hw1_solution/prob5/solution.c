#include <stdio.h>

int main(void) {
  int passengers, stops = 0;
  scanf("%d", &passengers);
  int in, out;
  while (scanf("%d%d", &out, &in) == 2) {
    ++stops;
    passengers -= out;
    if (passengers < 0) {
      printf("Impossible.\n");
      return 0;
    }
    passengers += in;
  }
  char query;
  scanf(" %c", &query);
  if (query == 'p')
    printf("%d\n", passengers);
  else
    printf("%d\n", stops);
  return 0;
}