#include <stdio.h>
typedef struct {
  int r, c;
} Point;

int main() {
  int n, m;
  scanf("%d %d", &n, &m);

  int array[n][m];
  int visited[n][m];
  Point q[n * m];

  Point d[] = {-1, 0, 1, 0, 0, -1, 0, 1};

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      scanf("%d", &array[i][j]);
      visited[i][j] = 0; // not forgot this !!!!!!!  or it undefined behavior
    }

  int head, tail;
  head = tail = 0;
  q[tail++] = (Point){0, 0};
  visited[0][0] = 1;
  int count = 0;

  while (head < tail) {
    Point cur = q[head++];
    count++;

    for (int i = 0; i < 4; i++) {
      Point now = {cur.r + d[i].r, cur.c + d[i].c};

      if (now.r >= 0 && now.r < n && now.c >= 0 && now.c < m &&
          !visited[now.r][now.c] &&
          array[now.r][now.c] <= array[cur.r][cur.c]) {
        visited[now.r][now.c] = 1;
        q[tail++] = (Point){now.r, now.c};
      }
    }
  }
  printf("%d\n", count);
  return 0;
}
