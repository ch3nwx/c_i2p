#include <stdio.h>

// Euclidaen Algorithm
//
int main() {
  int T;
  scanf("%d", &T);
  for (int t = 0; t < T; t++) {
    int a, b;

    scanf("%d%d", &a, &b);
    while (b) {
      a %= b;
      int tmp = b;
      b = a;
      a = tmp;
    }

    printf("%d\n", a);
  }
}
