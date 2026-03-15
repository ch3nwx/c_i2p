#include <stdio.h>
int main(void) {
  long money = 10000;
  int A, B;
  long P;

  int is_backrupt = 0;

  while (scanf("%d %d %ld", &A, &B, &P) == 3) {
    if (A > B) { // won
      money += P;
    } else if (A < B) {
      money -= P;
    }

    if (money <= 0) {
      if (!is_backrupt) {
        printf("0\n");
        is_backrupt = 1;
      } else {
        printf("No balance\n");
      }
    }
  }

  if (money > 0 && !is_backrupt) {
    printf("%ld\n", money);
  }
}
