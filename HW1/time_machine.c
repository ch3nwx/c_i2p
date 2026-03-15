#include <stdio.h>
int to_second(int h, int m, int s) { return (h * 3600) + (m * 60) + s; }

int main(void) {
  int H1, H2, M1, M2, S1, S2;
  scanf("%d %d %d", &H1, &M1, &S1);
  scanf("%d %d %d", &H2, &M2, &S2);
  int T1 = to_second(H1, M1, S1);
  int T2 = to_second(H2, M2, S2);
  if (T1 < T2)
    T1 += 86400;

  int AnsSec = T1 - T2;
  int Hour = AnsSec / 3600;
  AnsSec %= 3600;
  int Minute = AnsSec / 60;
  AnsSec %= 60;

  printf("%02d %02d %02d", Hour, Minute, AnsSec);
}
