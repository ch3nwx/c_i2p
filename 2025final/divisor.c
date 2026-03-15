#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 0x3f3f3f3f

int main() {
  int N;
  scanf("%d", &N);

  // if there only one return imme;
  if (N == 1) {
    printf("0\n");
    return 0;
  }

  int dist[N];
  // set the each distance to maximum (INF) == not reach
  //  queue = n+1 buffer so dist = n + 1 + 1
  memset(dist, 0x3f, (N + 2) * sizeof(int));
  int *q = malloc((N + 1) * sizeof(int));

  dist[N] = 0;
  int qhead = 0, qtail = 0;
  q[qtail++] = N;

  // i = i+d -> v = u+d revert u = v-d;
  while (qhead < qtail) {
    int u = q[qhead++];
    int cur_dist = dist[u] + 1;
    // half of divisor
    for (int d = 1; (long long)d * d <= u; d++) {
      if (u % d == 0) {
        // ds for pairs
        int ds[2];
        if (cache[u] == INF)
          ds = {d, u / d};
        else
          ds = cache[];
        int pair = (d == u / d) ? 1 : 2;
        for (int i = 0; i < pair; i++) {
          int dv = ds[i];
          if (u + dv <= N && dist[u + dv] == INF) {
            dist[u + dv] = cur_dist;
            cache[qtail] = dv;
            q[qtail++] = u + dv;
          }
          if (u - dv >= 1 && dist[u - dv] == INF) {
            dist[u - dv] = cur_dist;
            cache[qtail] = dv;
            q[qtail++] = u - dv;
          }
        }
      }
    }
  }

  for (int i = 1; i <= N; i++) {
    printf("%d ", dist[i]);
  }
}
