#include <stdio.h>
typedef struct {
  int r, c;
} Point;

int main(void) {
  int n, m;
  scanf("%d %d", &n, &m);

  int array[n][m];
  int visited[n][m];
  int head, tail;
  Point q[n * m];

  int dr[] = {-1, 1, 0, 0};
  int dc[] = {0, 0, -1, 1};

  for (int i = 0; i < n; i++) {
    for (int j = 0; i < m; j++) {
      scanf("%d", &array[i][j]);
    }
  }

  head = tail = 0;
  q[tail++] = (Point){0, 0};
  visited[0][0] = 1;
  int count = 0;

  while (head < tail) {
    Point cur = q[head++];
    count++;

    for (int d = 0; d < 4; d++) {
      int nr = cur.r + dr[d];
      int nc = cur.r + dc[d];
      // in grid
      //  not visited
      //  less height
      if (nr >= 0 && nr < n && nc >= 0 && nc < n && !visited[nr][nc] &&
          array[nr][nc] <= array[cur.r][cur.c]) {
        visited[nr][nc] = 1;
        q[tail++] = (Point){nr, nc};
      }
    }
  }

  printf("%d", count);
  return 0;
}
