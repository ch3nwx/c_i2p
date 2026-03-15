#include <stdio.h>

int main() {
  int N, Q;
  scanf("%d", &N);
  int sum[N + 1];
  sum[0] = 0;
  for (int i = 0; i < N; i++) {
    int n;
    scanf("%d", &n);
    sum[i] = i > 0 ? sum[i - 1] + n : n;
  }
  scanf("%d", &Q);
  for (int i = 0; i < Q; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", sum[b] - (a > 0 ? sum[a - 1] : 0));
  }
}
