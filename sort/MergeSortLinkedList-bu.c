
// Bottom-up
#include <stdio.h>
#include <stdlib.h>
struct Node {
  int data;
  struct Node *next;
};
void createNode(struct Node **headRef, int value) { // FIFO
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  if (newNode == NULL)
    return;
  newNode->data = value;
  newNode->next = NULL;

  if (*headRef == NULL) {
    *headRef = newNode;
    return;
  }
  struct Node *last = *headRef;
  while (last->next != NULL) {
    last = last->next;
  }
  last->next = newNode;
}
void printList(struct Node *head) {

  struct Node *current = head;
  while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}
struct Node *merge(struct Node *left, struct Node *right) {
  if (left == NULL)
    return right;
  if (right == NULL)
    return left;

  struct Node *result = NULL;

  if (left->data <= right->data) {
    result = left;
    result->next = merge(left->next, right);
  } else {
    result = right;
    result->next = merge(left, right->next);
  }
  return result;
}

struct Node *mergeSort(struct Node *head) {
  if (head == NULL || head->next == NULL)
    return head;

  int listSize = 0;
  struct Node *current = head;

  while (current != NULL) {
    listSize++;
    current = current->next;
  }
  struct Node *dummy = (struct Node *)malloc(sizeof(struct Node));
  dummy->next = head;

  for (int blockSize = 1; blockSize < listSize; blockSize *= 2) {
    struct Node *prev = dummy;
    current = dummy->next;
    while (current != NULL) {
      struct Node *left = current;
      struct Node *right;
      for (int i = 1; i < blockSize && current->next != NULL; i++)
        current = current->next;
      right = current->next;
      current->next = NULL;
      current = right;

      for (int i = 0; i < blockSize && current != NULL && current->next != NULL;
           i++)
        current = current->next;
      if (current != NULL) {
        struct Node *tmp = current->next;
        current->next = NULL;
        current = tmp;
      }

      prev->next = merge(left, right);
      while (prev->next != NULL)
        prev = prev->next;
    }
  }
  head = dummy->next;
  free(dummy);
  return head;
}

int main(void) {
  struct Node *head = NULL;
  for (int i = 0; i < 100; i++)
    createNode(&head, rand() % 100);

  printf("Original list: ");
  printList(head);

  mergeSort(head);
  printf("Sorted list: ");
  printList(head);
}
