#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* N up to 5e6 - allocate on heap */
#define MAXN 500005
static int32_t H[MAXN];
static int64_t V[MAXN], energy[MAXN];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d %lld", &H[i], &V[i]);
  }

  /*Each spire broadcasts Vi to its immediate neighbour if tha neighbour is
   * strictly taller. O[N]. */
  for (int i = 0; i < n; i++) {
    if (i > 0 && H[i - 1] > H[i])
      energy[i - 1] += V[i];
    if (i < n - 1 && H[i + 1] > H[i])
      energy[i + 1] += V[i];
  }

  /* Find the spire with maximum received energy (smallest index on tie). */
  int best = 0;
  for (int i = 0; i < n; i++)
    if (energy[i] > energy[best])
      best = i;
  printf("%d %lld\n", best, energy[best]);
}
