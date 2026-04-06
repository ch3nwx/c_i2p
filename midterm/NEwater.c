#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005
#define INITCAP 128

static char *strs[MAXN];
static int lens[MAXN], caps[MAXN];
static int N;

static void ensure(int i, int add) {
  while (lens[i] + add > caps[i])
    caps[i] *= 2;
  char *tmp = (char *)realloc(strs[i], caps[i]);
  if (tmp)
    strs[i] = tmp;
}

int main() {
  int Q;
  scanf("%d %d", &N, &Q);
  for (int i = 0; i < N; i++) {
    caps[i] = INITCAP;
    strs[i] = (char *)malloc(INITCAP);
    lens[i] = 0;
  }
  while (Q--) {
    int type;
    scanf("%d", &type);
    if (type == 0) {
      /* Append a single character */
      int i;
      char c;
      scanf("%d %c", &i, &c);
      ensure(i, 1);
      strs[i][lens[i]++] = c;
    } else if (type == 1) {
      /* Append a string */
      int i;
      char buf[100010];
      scanf("%d %s", &i, buf);
      int sl = (int)strlen(buf);
      ensure(i, sl);
      memcpy(strs[i] + lens[i], buf, sl);
      lens[i] += sl;
    } else {
      /* Print all non-empty strings */
      for (int i = 0; i < N; i++) {
        if (lens[i] > 0) {
          strs[i][lens[i]] = '\0';
          printf("%s\n", strs[i]);
        }
      }
    }
  }
}
