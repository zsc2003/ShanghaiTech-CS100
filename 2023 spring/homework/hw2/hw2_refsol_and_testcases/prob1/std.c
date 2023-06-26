#include <stdio.h>

int main(void) {
  int n, a[100];
  scanf("%d", &n);
  for (int i = 0; i != n; ++i)
    scanf("%d", &a[i]);
  int cnt = 0;
  for (int i = n - 1; i >= 0; --i) {
    if (a[i] > 0) {
      printf("%lld\n", 1ll * a[i] * a[i]);
      ++cnt;
    }
  }
  printf("%d\n", cnt);
  return 0;
}