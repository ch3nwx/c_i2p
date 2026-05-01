#include "14931.h"

ListNode *solve(ListNode *head) {
  if (!head || !head->next || !head->next->next)
    return head;

  ListNode *slow = head, *fast = head;
  while (fast->next && fast->next->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  ListNode *sec = slow->next;
  slow->next = nullptr;

  ListNode *prev = nullptr;
  while (sec) {
    ListNode *nxt = sec->next;
    sec->next = prev;
    prev = sec;
    sec = nxt;
  }

  ListNode *a = head, *b = prev;
  while (b) {
    ListNode *an = a->next;
    ListNode *bn = b->next;
    a->next = b;
    b->next = an;
    a = an;
    b = bn;
  }

  return head;
}
