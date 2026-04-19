#include "function.h"
#include <stddef.h>

void solve(Node *head, int l, int r) {
  Node *pre = head;
  for (int i = 1; i < l; i++)
    pre = pre->next;

  Node *prev = NULL;
  Node *cur = pre->next;
  Node *tail = cur; // l-th node becomes the tail after reversal

  for (int i = l; i <= r; i++) {
    Node *next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
  }

  pre->next = prev;
  tail->next = cur;
}
