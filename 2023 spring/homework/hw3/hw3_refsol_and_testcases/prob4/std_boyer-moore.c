#include <assert.h>
#include <stdio.h>

int main(void) {
  int n;
  scanf("%d", &n);

  // Boyer-Moore Algorithm
  int type = -1;
  int total_cost = 0;
  while (n--) {
    int curr_type, curr_cost;
    scanf("%*[^,],%d,%d", &curr_cost, &curr_type);
    if (type == -1 || type == curr_type) {
      type = curr_type;
      total_cost += curr_cost;
    } else {
      total_cost -= curr_cost;
      if (total_cost < 0) {
        type = curr_type;
        total_cost = -total_cost;
      }
    }
  }
  assert(total_cost > 0);
  printf("%d\n", type);
  return 0;
}