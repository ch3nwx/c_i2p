#include "function.h"
#include <stdlib.h>

int **create_walkway(int n, const int *len) {
  int **arr = (int **)malloc(sizeof(int *) * n);
  if (!arr)
    return NULL;

  for (int i = 0; i < n; i++) {
    int *tiles = (int *)malloc(sizeof(int) * len(i));
  }
}
