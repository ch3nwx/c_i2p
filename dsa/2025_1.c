#include <stdio.h>

int main(void) {
  int n, k;
  scanf("%d %d", &n, &k);
  int V[101], W[101];
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &V[i], &W[i]);
  }

  int dp[1001] = {0};
  for (int i = 1; i <= n; i++) {
    // start at max weight
    for (int w = k; w >= W[i]; w--) {
      if (dp[w - W[i]] + V[i] >
          dp[w]) { // dp[w] = max(dp[w] , dp[w - W[i]] + V[i])
        dp[w] = dp[w - W[i]] + V[i];
      }
    }
  }

  printf("%d\n", dp[k]);
}
