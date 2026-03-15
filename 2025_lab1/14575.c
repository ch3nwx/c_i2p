#include "14575.h"
#include <stdio.h>
#include <stdlib.h>

Node *createListNode(int x) {
  Node *node = (Node *)malloc(sizeof(Node));
  *(int *)&node->v = x;
  node->next = NULL;
  return node;
}
int print(Node *head, int chk2) {
  Node *cur = head->next;
  while (cur != NULL) {
    chk2 ^= ((int)cur + cur->v);
    printf("%d ", cur->v);
    cur = cur->next;
  }
  return chk2;
}
void freeList(Node *head) {
  Node *cur = head;
  Node *tmp = NULL;
  while (cur != NULL) {
    tmp = cur;
    cur = cur->next;
    free(tmp);
  }
}

int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  Node *head = createListNode(0);
  int chk = (int)head;
  Node *cur = head;
  for (int i = 0; i < n; i++) {
    int tmp;
    scanf("%d", &tmp);
    cur->next = createListNode(tmp);
    cur = cur->next;
    chk ^= ((int)cur + cur->v);
  }
  solve(head, k);
  if (chk != print(head, (int)head))
    printf("WA\n");
  freeList(head);
  return 0;
}
