#include "function.h"

void shift(char *start, char *end) { // l,r inclusive
  char tmp = *start;
  int len = end - start + 1;

  for (int i = 1; i < len; i++) {
    start[i - 1] = start[i];
  }
  *end = tmp;
}
