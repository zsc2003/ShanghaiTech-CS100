#include <stdio.h>
#include <assert.h>

int calc_bits(long long x) {
  assert(x >= 0);
  if (x == 0)
    return 1;
  int ans = 0;
  while (x > 0) {
    ++ans;
    x >>= 1;
  }
  return ans;
}

int main(void) {
  long long x;
  int m;
  scanf("%lld%d", &x, &m);
  long long q = x >> (m + 1);
  long long p = x - (q << (m + 1));
  long long y = (p << calc_bits(q)) + q;
  int b = 0;
  while ((y & (1ll << b)) == 0)
    ++b;
  printf("%lld %d\n", y, b);
  return 0;
}