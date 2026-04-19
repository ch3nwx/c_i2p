#include "function.h"
#include <stdio.h>
#include <stdlib.h>

Node *createList(int n) {
  Node *list = (Node *)malloc(sizeof(Node) * n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &list[i].tolerance);
    list[i].id = i + 1;
    if (i == n - 1)
      list[i].next = &list[0];
    else
      list[i].next = &list[i + 1];
    if (i == 0)
      list[i].prev = &list[n - 1];
    else
      list[i].prev = &list[i - 1];
  }
  return list;
}

Node *Relink(Node *cur, int k) {
  cur->prev->next = cur->next;
  cur->next->prev = cur->prev;
  if (k > 0)
    return cur->next;
  else
    return cur->prev;
}
void Move(Node **cur, int k) {
  while (k != 0) {
    if (k > 0) {
      *cur = (*cur)->next;
      k--;
    } else {
      *cur = (*cur)->prev;
      k++;
    }
  }
}

void solve(Node *head, int N, int K) {
  Node *cur = head;
  int k = K;
  int n = N;
  while (cur != cur->next) {
    int r = k % n;
    k = (r == 0) ? (k > 0 ? n : -n) : r;
    Move(&cur, (k > 0) ? k - 1 : k + 1);
    int tmp = cur->tolerance;
    printf("%d ", cur->id);
    cur = Relink(cur, k);
    k = tmp;
    n--;
  }
  printf("\n%d\n", cur->id);
}
