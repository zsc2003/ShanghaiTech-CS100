#include <stdio.h>

int main(void) {
  int n;
  scanf("%d", &n);

  // local static array elements are initialized to zero
  static long long price_sum_of_type[1000001];
  long long price_sum = 0;

  int max_type = 0;
  while (n--) {
    int price, type;
    // Use %* to skip things
    scanf("%*[^,],%d,%d)", &price, &type);
    price_sum_of_type[type] += price;
    price_sum += price;
    if (type >= max_type)
      max_type = type;
  }

  for (int type = 1; type <= max_type; ++type)
		if (price_sum_of_type[type] * 2 >= price_sum) {
      printf("%d\n", type);
      break;
    }

  return 0;
}