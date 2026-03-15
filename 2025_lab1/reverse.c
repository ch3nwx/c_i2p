#include "14575.h"
#include <stdio.h>
#include <stdlib.h>

void solve(Node *head, int k) {
  Node *start = head;

  while (start != NULL) {
    Node *curr = start->next;
    Node *prev = start;
    for (int i = 0; i < k - 1; ++i) {
      if (curr == NULL || curr->next == NULL)
        break;
      if (curr->v > curr->next->v) {
        Node *tmp = curr->next;
        curr->next = tmp->next;
        tmp->next = curr;
        prev->next = tmp;
        prev = tmp;
      } else {
        prev = curr;
        curr = curr->next;
      }
    }

    for (int i = 0; i < k; ++i) {
      start = start->next;
    }
  }
}
