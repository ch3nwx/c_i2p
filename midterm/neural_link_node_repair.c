#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// safety checks and neural bridging repairs
//  calculate final checksum signal
//
//  if adjecent = overload -> 0xFFFFFFFF
//  NOT between 2 extream node
//  checksum low byte
bool overload(uint32_t S) {
  uint32_t mask = (1 << 2) - 1;
  for (int i = 0; i < 6; i++) {
    if ((S & mask) == 3)
      return true;
    S >>= 1;
  }
  return false;
}
uint32_t LSB(uint32_t S) {
  uint32_t m_LSB = 1U;
  for (int i = 0; i < 6; i++) {
    if ((S & m_LSB) == 1) {
      return (1U << i);
    }
    S >>= 1;
  }
  return 0;
}
uint32_t MSB(uint32_t S) {
  uint32_t m_MSB = 0x80000000;

  for (int i = 0; i < 6; i++) {
    if ((S & m_MSB) == 0x80000000) {
      return (0x80000000 >> i);
    }
    S <<= 1;
  }
  return 0;
}
uint32_t bridging(uint32_t S) {
  if (MSB(S) == 0 || LSB(S) == 0)
    return S;
  uint32_t m_NOT = (MSB(S) - 1) & ~(LSB(S) - 1);
  S ^= m_NOT;
  return S;
}

uint32_t checksum(uint32_t S) {
  uint32_t mask = (1U << 4) - 1;
  uint32_t c_S = S;
  uint8_t sum = 0;
  for (int i = 0; i < 4; i++) {
    sum ^= (c_S & mask);

    c_S >>= 4;
  }
  return (S & ~mask) | sum;
}
int main() {
  unsigned T;
  scanf("%d", &T);
  for (unsigned t = 0; t < T; t++) {
    uint32_t S;
    scanf("%X", &S);
    if (overload(S)) {
      printf("%X", (uint32_t)(-1));
    } else {
      printf("%X", checksum(bridging(S)));
    }
  }
}
