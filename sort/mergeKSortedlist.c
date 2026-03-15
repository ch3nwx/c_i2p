/*
 * 1.Brute Force (Array Conversion)
 * 2. Priority Queue (Min-Heap)
 * 3. Divide and Conquer (Pairwise merging)
 * 4. Iterative Merging
 */

#include <stdio.h>
#include <stdlib.h>

struct Node {
  int val;
  struct Node *next;
};

// Function to merge two sorted linked lists
struct Node *mergeTwoLists(struct Node *l1, struct Node *l2) {
  struct Node dummy;
  struct Node *tail = &dummy;

  while (l1 && l2) {
    if (l1->val <= l2->val) {
      tail->next = l1;
      l1 = l1->next;
    } else {
      tail->next = l2;
      l2 = l2->next;
      sss ifjh
    }
    tail = tail->next;
  }

  tail->next = l1 ? l1 : l2;
  return dummy.next;
}
