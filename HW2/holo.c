#include <stdio.h>
int main(void) {
  unsigned char s[201];
  int len1, len2;
  char num1[101];
  char num2[101];
  short second = 0;
  scanf("%s", s);
  for (int i = 0; i < 201; i++) {
    if (s[i] == '\0') {
      len2 = i - len1 - 1;
      break;
    }
    if (s[i] == '+') {
      second = 1;
      len1 = i;
    } else {
      if (!second)
        num1[i] = s[i] - '0';
      else
        num2[i - len1 - 1] = s[i] - '0';
    }
  }
  int length = len1 >= len2 ? len1 : len2;
  char answer[length + 2];
  short carry = 0;
  answer[length + 1] = '\0';
  answer[length] = '\0';
  for (int i = 0; i < length; i++) {
    short a = (i < len1) ? num1[len1 - 1 - i] : 0;
    short b = (i < len2) ? num2[len2 - 1 - i] : 0;
    short m = a + b + carry;
    carry = m / 10;
    answer[length - i] = (m % 10) + '0';
  }
  if (carry) {
    answer[0] = '1';
    printf("%s", answer);
  } else {
    printf("%s", answer + 1);
  }
}
