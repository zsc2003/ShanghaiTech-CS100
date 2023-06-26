#include <stdbool.h>
#include <stdio.h>

bool check(int x, int days_of_month[], int n, int *last) {
  int month = (x % 10) * 10 + ((x / 10) % 10); // get month
  int day = x / 100;
  day = (day + (day % 10) * 100) / 10; // get inverse
  *last = month * 100 + day;           // store
  return month <= n && month >= 1 && day >= 1 && day <= days_of_month[month];
}

int main(void) {
  int n;
  scanf("%d", &n);
  int days_of_month[100];
  for (int i = 1; i <= n; i++) {
    scanf("%d", days_of_month + i);
  }
  int st, ed;
  scanf("%d%d", &st, &ed);
  int ans = 0;
  int last = 0;
  for (int i = (st / 10000) + 1, end = ed / 10000; i < end; i++) {
    ans += check(i, days_of_month, n, &last) ? 1 : 0;
  }
  if (check(st / 10000, days_of_month, n, &last)) {
    int org = st / 10000;
    if (org * 10000 + last >= st) {
      ans++;
    }
  }
  if (check(ed / 10000, days_of_month, n, &last)) {
    int org = ed / 10000;
    if (org * 10000 + last <= ed) {
      ans++;
    }
  }
  printf("%d\n", ans);
  return 0;
}