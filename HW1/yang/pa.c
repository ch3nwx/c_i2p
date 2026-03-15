#include <stdio.h>
#include <stdlib.h>

struct Node {
  int n;
  struct Node *next;
  struct Node *prev;
};

struct Node *createNode(int value) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  if (newNode == NULL) {
    exit(1);
  }
  newNode->n = value;
  newNode->next = NULL;
  newNode->prev = NULL;
  return newNode;
}

int main(void) {
  int n, m;
  scanf("%d %d", &n, &m);
  struct Node *head = createNode(1);
  struct Node *current = head;
  struct Node **lookup =
      (struct Node **)malloc(sizeof(struct Node *) * (n + 1));

  lookup[1] = head;
  struct Node *temp = NULL;
  for (int i = 2; i <= n; ++i) {

    temp = current;
    current->next = createNode(i);
    current = current->next;
    current->prev = temp;
    lookup[i] = current;
  }

  for (int i = 0; i < m; ++i) {
    int num;
    scanf("%d", &num);

    current = lookup[num];
    while (current != NULL) {
      if (current->n == num) {
        if (current == head) {
          break;
        }
        if (current->prev != NULL) {
          current->prev->next = current->next;
        }
        if (current->next != NULL) {
          current->next->prev = current->prev;
        }

        current->prev = NULL;
        current->next = head;
        head->prev = current;
        head = current;
        break;
      }
      current = current->next;
    }
  }

  current = head;
  while (current != NULL) {
    printf("%d\n", current->n);
    temp = current;
    current = current->next;
    free(temp);
  }
}
