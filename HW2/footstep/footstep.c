#include "function.h"
#include <stdlib.h>

int **create_walkway(int n, const int *len) {
  int **arr = (int **)malloc(sizeof(int *) * n);
  if (!arr)
    return NULL;

  for (int i = 0; i < n; i++) {
    int *tiles = (int *)malloc(sizeof(int) * len[i]);
    if (!tiles) {
      for (int ii = 0; ii < i; ii++) {
        free(arr[ii]);
      }
      free(arr);
      return NULL;
    }
    *(arr + i) = tiles;
  }
  return arr;
}
void activate_walkway(int n, const int *len, int **tile) {
  long long sum = 0;
  for (int i = 0; i < n; i++) {
    int *tmp = (int *)malloc(sizeof(int) * len[i]);
    for (int j = 0; j < len[i]; j++) {
      tmp[j] = tile[i][j];
      if (j - 1 >= 0)
        tmp[j] += tile[i][j - 1];
      if (j + 1 < len[i])
        tmp[j] += tile[i][j + 1];
      sum += tmp[j];
    }
    for (int j = 0; j < len[i]; j++)
      tile[i][j] = tmp[j];
    free(tmp);
  }
}

void delete_walkway(int n, int **tile) {
  for (int i = 0; i < n; i++) {
    free(tile[i]); // tiles
  }
  free(tile); // array
  return;
}
