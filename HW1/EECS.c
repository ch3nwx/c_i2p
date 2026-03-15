#include <stdio.h>
#include <stdlib.h>

int main(void) {
  short k;
  scanf("%hd", &k);
  char s[6];
  int asc[5];

  scanf("%s", s);
  for (int i = 0; i < 5; ++i) {

    asc[i] = (int)(s[i]) + k;
    if (asc[i] > 122) {
      asc[i] = (asc[i] % 122) + 96;
    }
    asc[i] -= (97 - 65);

    s[i] = (char)(asc[i]);
  }
  printf("%s", s);
}
