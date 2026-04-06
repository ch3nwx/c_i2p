#include <stdint.h>
#include <stdio.h>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    uint32_t S;
    scanf(" %x", &S); /* %x reads hex; handles optional 0x prefix */

    /* Rule 1: adjacent ls? */
    if (S & (S >> 1)) {
      printf("0xFFFFFFFF\n");
      continue;
    };

    /* Rule 2; find MSB and LSB, fill bits between them */
    int msb = 31;
    while (!((S >> msb) & 1))
      msb--;
    int lsb = 0;
    while (!((S >> lsb) & 1))
      lsb++;

    uint32_t bridge = S;
    if (msb > lsb) {
      uint32_t hi = (msb == 31) ? 0xFFFFFFFFu : (1u << (msb + 1)) - 1u;
      uint32_t lo = (1u << lsb) - 1u;
      uint32_t m_not = hi & ~lo;
      bridge = S ^ m_not;
    }

    /* Rule 3: XOR all 4 bytes, replace lowest byte with checksum */
    uint8_t cs =
        (uint8_t)(bridge >> 24) ^ (bridge >> 16) ^ (bridge >> 8) ^ bridge;
    printf("0x%08X\n", (bridge & 0xFFFFFF00u) | cs);
  }
  return 0;
}
