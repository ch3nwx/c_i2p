#include <stdio.h>
#include <stdlib.h>

int **alloc_matrix(int n) {
  int **a = (int **)malloc(sizeof(int *) * n);
  for (int i = 0; i < n; ++i) {
    a[i] = (int *)malloc(sizeof(int) * n);
  }
  return a;
}
void free_matrix(int **a, int n) {
  for (int i = 0; i < n; ++i) {
    free(a[i]);
  }
  free(a);
}

void scan_matrix(int **a, int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", &a[i][j]);
    }
  }
}

void flip(int **a, const int n) {
  int temp;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n / 2; ++j) {
      temp = a[i][j];
      a[i][j] = a[i][n - 1 - j];
      a[i][n - 1 - j] = temp;
    }
  }
}

void apply_filter(int **picA, int **filter, int **picB, int n, int m, int x) {
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < x; j++) {
      picB[i][j] = 0;
      for (int q = 0; q < m; q++) {
        for (int r = 0; r < m; r++) {
          picB[i][j] += picA[i + q][j + r] * filter[q][r];
        }
      }
    }
  }
}

int main(void) {
  int T;
  scanf("%d", &T);

  for (int t = 0; t < T; ++t) {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    int **picA = alloc_matrix(n);
    scan_matrix(picA, n);
    int **filter = alloc_matrix(m);
    scan_matrix(filter, m);
    flip(picA, n);
    int x = n - m + 1;
    int **picB = alloc_matrix(x);
    apply_filter(picA, filter, picB, n, m, x);

    int count = 0;
    for (int i = 0; i < x; ++i) {
      for (int j = 0; j < x; ++j) {
        if (picB[i][j] > k) {
          count++;
        }
      }
    }
    printf("%d\n", count);
    free_matrix(picA, n);
    free_matrix(picB, x);
    free_matrix(filter, m);
  }
}
