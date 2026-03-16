#include <stdio.h>

int main() {
  int T;
  scanf("%d", &T);

  for (int t; t < T; t++) {
    int R, C;
    scanf("%d %d", &R, &C);
    char matrix[R][C];

    for (int r; r < R; r++) {
      for (int c; c < C; c++) {
        scanf("%c", &matrix[r][c]);
      }
    }
  }
}
