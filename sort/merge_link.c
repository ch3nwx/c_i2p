// =================================== Problem Statement
/*
 Task: Sorting Algorithm for Linked List

 Sol: The problem to sort the linked can be done via folowing methods

    Method 1)  One of the brute force solution is to convert the linked list
 into an array, sort the array using a standard sorting algorithm, and then
 rebuild the linked list using the sorted values. This approach may be simpler
 to implement but requires additional memory to store the array. Time Complexity
 - O(n logn) , Space Complexity - O(n)

    Method 2) Quick Sort can be applied to a linked list by selecting a pivot,
 partitioning the list into smaller and greater elements, and recursively
 sorting the partitions. The main challenge lies in rearranging the nodes during
 the partitioning step, as random access is not available. Despite this, Quick
 Sort remains an efficient sorting algorithm for linked lists with an average
 Time complexity of O(n log n) but in worst case O(n^2) and a Space complexity
 of O(log n).

    Method 3) Merge Sort can be applied to a linked list by recursively dividing
 it into smaller sublists, sorting each sublist individually, and then merging
 the sorted sublists back together. The merging process takes advantage of the
 sorted order of the sublists, resulting in a sorted linked list. Merge Sort is
 efficient for linked lists, with a time complexity of O(n log n) and a space
 complexity of O(log n) due to the recursive nature of the algorithm.

    Among the sorting algorithms suitable for linked lists, Merge Sort stands
 out as the most suitable choice. Merge Sort is a popularly known algorithm that
 follows the Divide and Conquer strategy. It can be implemented by recursively
 dividing the linked list, sorting each sublist, and merging them back together.
 However, even within Merge Sort, there are two approaches to consider:

    Approach 1) The recursive approach using top-down merging.

        - Recursively split the original list into two halves. The split
 continues until there is only one node in the linked list (Divide phase). To
 split the list into two halves, we find the middle of the linked list using the
 Fast and Slow pointer approach.

        - Recursively sort each sublist and combine it into a single sorted list
 (Merge Phase).

    Time Complexity: O(n logn) , Space Complexity: O(logn) for recursive stack
 space.

    Approach 2) The iterative approach using bottom-up merging.

        - Start with splitting the list into sublists of size 1.Each adjacent
 pair of sublists of size 1 is merged in sorted order. After the first
 iteration, we get the sorted lists of size 2.

        - A similar process is repeated for a sublist of size 2.In this way, we
 iteratively split the list into sublists of size 1, 2, 4, 8, and so on until we
 reach n.

        - To split the list into two sublists of given size beginning from
 start, we use two pointers: mid and end. Mid and end reference the start and
 end of the second linked list, respectively.

        - Merge the lists in sorted order as discussed in Approach 1.

        - As we iteratively split the list and merge, we have to keep track of
 the previous merged list using pointer tail and the next sublist to be sorted
 using pointer nextSubList.

    Time Complexity: O(n logn) , Space Complexity: O(1) only reference pointer.

    We are going to implemet both Approaches below
*/
// =================================== Code with C

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;
void insertNode(Node **headRef, int value) { // LIFO
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = value;
  newNode->next = *headRef;
  *headRef = newNode;
}

void printList(Node *head) {
  Node *current = head;
  while (current != NULL) {
    printf("%d", current->data);
    current = current->next;
  }
  printf("\n");
}

// function to merge two sorted linked list
Node *merge(Node *left, Node *right) {
  if (left == NULL) {
    return right;
  }
  if (right == NULL) {
    return left;
  }

  Node *result = NULL;

  if (left->data <= right->data) {
    result = left;
    result->next = merge(left->next, right);
  } else {
    result = right;
    result->next = merge(left, right->next);
  }
  return result;
}

// function to split the linked list into two halved
void splitList(Node *head, Node **left, Node **right) {
  Node *slow = head;
  Node *fast = head->next;

  // move 'fast' two nodes ahead and 'slow' one node ahead

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

void mergeSortTopDown(Node **headRef) {
  Node *head = *headRef;
  Node *left;
  Node *right;

  // Base case: if list is empty or contains only one node
  if (head == NULL || head->next == NULL) {
    return;
  }

  // Split the list into two halves
  splitList(head, &left, &right);

  // Recursively sort the two halves
  mergeSortTopDown(&left);
  mergeSortTopDown(&right);

  // Merge the sorted halves
  *headRef = merge(left, right);
}

// bottom-up merge sort on linked list
Node *mergeSortBottomUp(Node *head) {

  // Base case: if list is empty or constains only one node
  if (head == NULL || head->next == NULL) {
    return head;
  }

  int listSize = 0;
  Node *current = head;
  // Count the number of nodes in the list
  while (current != NULL) {
    listSize++;
    current = current->next;
  }

  Node *dummy = (Node *)malloc(sizeof(Node));
  dummy->next = head;

  for (int blockSize = 1; blockSize < listSize; blockSize *= 2) {
    Node *prev = dummy;
    current = dummy->next;
    while (current != NULL) {
      // Split the list into two parts
      Node *left = current;
      Node *right;
      for (int i = 1; i < blockSize && current->next != NULL; i++)
        current = current->next;

      right = current->next;
      current->next = NULL;
      current = right;
      // split the list again to get the next part
      for (int i = 1; i < blockSize && current != NULL && current->next != NULL;
           i++)
        current = current->next;

      if (current != NULL) {
        Node *tmp = current->next;
        current->next = NULL;
        current = tmp;
      }

      // merge the two parts
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
  Node *headTopDown = NULL;
  Node *headBottomUp = NULL;

  // Insert nodes into the linked list
  insertNode(&headTopDown, 5);
  insertNode(&headTopDown, 2);
  insertNode(&headTopDown, 8);
  insertNode(&headTopDown, 1);
  insertNode(&headTopDown, 9);

  insertNode(&headBottomUp, 5);
  insertNode(&headBottomUp, 2);
  insertNode(&headBottomUp, 8);
  insertNode(&headBottomUp, 1);
  insertNode(&headBottomUp, 9);

  printf("Original list;");
  printList(headTopDown);

  mergeSortTopDown(&headTopDown);
  printf("Sorted listed (Top-down): ");
  printList(headTopDown);

  headBottomUp = mergeSortBottomUp(headBottomUp);
  printf("Sorted list (bottom-up): ");
  printList(headBottomUp);
  return 0;
}
