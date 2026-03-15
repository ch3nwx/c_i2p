#include "function.h"
#include <stdio.h>
#include <stdlib.h>

unsigned ***new_3d_array(unsigned n, unsigned m, unsigned k) {

  unsigned ***array = (unsigned ***)malloc(sizeof(unsigned **) * n +
                                           sizeof(unsigned *) * (n * m) +
                                           sizeof(unsigned) * (n * m * k));

  unsigned **ptrs = (unsigned **)(array + n);
  unsigned *data = (unsigned *)(ptrs + n * m);

  for (unsigned i = 0; i < n; i++) {
    *(array + i) = (unsigned **)(ptrs + i * m);
    for (unsigned j = 0; j < m; j++) {
      *(*(array + i) + j) = (unsigned *)(data + i * m * k + j * k);
    }
  }
  return array;
}
void delete_3d_array(unsigned ***arr) { free(arr); }
