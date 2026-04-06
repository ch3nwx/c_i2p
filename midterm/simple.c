#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXS 20010

static char S[MAXS];
static int slen;

/* Convert "d1|d2|...|dm" -> uppercase hex string. */
static void mystery_to_hex(const char *inp, char *out, int *outlen) {
  *outlen = 0;
  const char *p = inp;
  while (*p) {
    char *end;
    long long val = strtoll(p, &end, 10);
    int n = sprintf(out + *outlen, "%llX", val);
    *outlen += n;
    if (*end == '|')
      p = end + 1;
    else
      break;
  }
  out[*outlen] = '\0';
}

int main() {
  char initStr[5010];
  scanf("%s", initStr);
  mystery_to_hex(initStr, S, &slen);
  int q;
  scanf(" %d", &q);
  getchar(); /* consume newline */

  while (q--) {
    char line[10010];
    fgets(line, sizeof(line), stdin);
    if (line[0] == 'I') {
      int idx;
      char str[5010];
      sscanf(line + 7, "%d %s", &idx, str);

      char hexIn[MAXS];
      int hexLen;
      mystery_to_hex(str, hexIn, &hexLen);

      memmove(S + idx + hexLen, S + idx, slen - idx + 1);
      memcpy(S + idx, hexIn, hexLen);
      slen += hexLen;
    } else {
      int idx, len;
      sscanf(line + 7, "%d %d", &idx, &len);
      memmove(S + idx, S + idx + len, slen - idx - len + 1);
      slen -= len;
    }
  }
}
