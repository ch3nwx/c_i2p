#include "14219.h"
#include <stdio.h>
#include <stdlib.h>

ListNode *merge(ListNode *left, ListNode *right) {
  if (left == NULL)
    return right;
  if (right == NULL)
    return left;

  ListNode *result = NULL;
  if (left->val <= right->val) {
    result = left;
    result->next = merge(left->next, right);
  } else {
    result = right;
    result->next = merge(left, right->next);
  }
  return result;
}

void split(ListNode *head, ListNode **left, ListNode **right) {
  ListNode *slow = head;
  ListNode *fast = head;

  while (fast != NULL) {
    fast = fast->next;
    if (fast != NULL) {
      slow = slow->next;
      fast = fast->next;
    }
  }

  *left = head;
  *right = slow->next;
  slow->next = NULL;
}

void ms(ListNode **headRef) {
  ListNode *head = *headRef;
  ListNode *left;
  ListNode *right;
  if (head == NULL || head->next == NULL)
    return;

  split(head, &left, &right);

  ms(&left);
  ms(&right);

  *headRef = merge(left, right);
}

ListNode *mergeLists(ListNode **lists, int n) {
  if (n == 0) return NULL;
  if (n == 1) return lists[0];
  int mid = n / 2;
  ListNode *left = mergeLists(lists, mid);
  ListNode *right = mergeLists(lists + mid, n - mid);
  return merge(left, right);
}
