#include <stdio.h>
#include <string.h>

int main(void) {
  short T;
  scanf("%hd", &T);
  for (int t = 0; t < T; ++t) {
    char A[1000], B[1000];
    scanf("%s %s", A, B);

    int lenA = strlen(A);
    int lenB = strlen(B);
    int max = (lenA < lenB) ? lenA : lenB;
    int count = 0;

    for (int i = 0; i < max; ++i) {
      int match = 1;

      for (int j = 0; j <= i; ++j) {
        if (A[lenA - 1 - i + j] != B[j]) {
          match = 0;
          break;
        }
      }
      if (match) {
        count = i + 1;
      }
    }

    A[lenA - count] = '\0';

    printf("%s%s\n", A, B);
  }
}
