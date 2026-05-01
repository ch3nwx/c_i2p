#include "question.h"
#include <iostream>
using namespace std;

// ============================ stack (10998) ============================
// Doubly-linked list used as a LIFO stack. head = top of stack.

// Constructor: empty stack, both pointers null.
List_stack::List_stack() : head(NULL), tail(NULL) {}

// Destructor: walk from head to tail, delete every node so no leaks.
List_stack::~List_stack() {
  while (head) {
    ListNode *t = head;   // remember current node
    head = head->nextPtr; // advance before deleting
    delete t;             // free old node
  }
  tail = NULL;
}

// push: insert new node at front (top of stack).
void List_stack::push(const int &v) {
  ListNode *n = new ListNode(v);
  if (!head) {
    head = tail = n; // first element: head and tail both point here
  } else {
    n->nextPtr = head; // new node points to old head
    head->prevPtr = n; // old head's prev points back to new node
    head = n;          // new node becomes the head
  }
}

// pop: remove top (head). No-op if empty.
void List_stack::pop() {
  if (!head)
    return;
  ListNode *t = head;   // node to delete
  head = head->nextPtr; // advance head
  if (head)
    head->prevPtr = NULL; // new head has no previous
  else
    tail = NULL; // list became empty
  delete t;
}

// print: traverse head -> tail, print data separated by single spaces.
// No trailing space, no newline (main.cpp prints endl after).
void List_stack::print() {
  for (ListNode *c = head; c; c = c->nextPtr) {
    cout << c->data;
    if (c->nextPtr)
      cout << " ";
  }
}

// ============================ matrix (14605) ============================
// All operations mutate *this in place.

// Element-wise A += B.
void Matrix::add(const Matrix &rhs) {
  for (long long i = 0; i < n; i++)
    for (long long j = 0; j < n; j++)
      data[i][j] += rhs.data[i][j];
}

// Element-wise A -= B.
void Matrix::subtract(const Matrix &rhs) {
  for (long long i = 0; i < n; i++)
    for (long long j = 0; j < n; j++)
      data[i][j] -= rhs.data[i][j];
}

// A = A * B. Standard O(n^3) with i,k,j loop order (cache-friendly:
// data[i][k] is constant across the inner j loop).
void Matrix::multiply(const Matrix &rhs) {
  long long **r = new long long *[n]; // allocate result matrix
  for (long long i = 0; i < n; i++) {
    r[i] = new long long[n](); // zero-initialised row
    for (long long k = 0; k < n; k++) {
      long long a = data[i][k];
      if (!a)
        continue; // skip zero -> small speedup
      for (long long j = 0; j < n; j++)
        r[i][j] += a * rhs.data[k][j];
    }
  }
  // free old data, swap in result
  for (long long i = 0; i < n; i++)
    delete[] data[i];
  delete[] data;
  data = r;
}

// In-place transpose: swap data[i][j] with data[j][i] for j>i only
// (swapping both halves would undo the swap).
void Matrix::transpose() {
  for (long long i = 0; i < n; i++)
    for (long long j = i + 1; j < n; j++) {
      long long t = data[i][j];
      data[i][j] = data[j][i];
      data[j][i] = t;
    }
}

// Fast exponentiation: A^x in O(n^3 log x).
// Idea: result = I; while x > 0, if bit is 1 multiply result by base, then
// square base.
void Matrix::power(long long x) {
  Matrix base(n, data); // copy of current matrix
  // reset *this to identity (the multiplicative "1")
  for (long long i = 0; i < n; i++)
    for (long long j = 0; j < n; j++)
      data[i][j] = (i == j) ? 1 : 0;
  while (x > 0) {
    if (x & 1)
      this->multiply(base); // accumulate when current bit is 1
    x >>= 1;
    if (x)
      base.multiply(
          base); // square base for next bit (skip last unnecessary squaring)
  }
}

// ============================ vending (14927) ============================
// Min-heap on a dynamic array (no STL allowed).
// Parent of i = (i-1)/2, children = 2i+1, 2i+2.

// Initial capacity 16, all counters zero.
VendingMachine::VendingMachine() {
  capacity = 16;
  data = new int[capacity];
  size = 0;
  totalRevenue = 0;
  totalSold = 0;
}

// Free backing array.
VendingMachine::~VendingMachine() { delete[] data; }

// store: append + sift-up to restore min-heap property.
void VendingMachine::store(int price) {
  if (size == capacity) {
    // grow: allocate doubled array, copy, free old
    int nc = capacity * 2;
    int *nd = new int[nc];
    for (int i = 0; i < size; i++)
      nd[i] = data[i];
    delete[] data;
    data = nd;
    capacity = nc;
  }
  int i = size++; // place at next free slot
  data[i] = price;
  // sift-up: while parent is larger, swap with parent
  while (i > 0) {
    int p = (i - 1) / 2;
    if (data[p] > data[i]) {
      int t = data[p];
      data[p] = data[i];
      data[i] = t;
      i = p;
    } else
      break; // heap property restored
  }
}

// sell: pop minimum (root), record sale, sift-down.
void VendingMachine::sell() {
  if (size == 0)
    return; // ignore on empty machine
  totalSold++;
  totalRevenue += data[0]; // root is the minimum
  size--;
  if (size == 0)
    return;             // heap is now empty
  data[0] = data[size]; // move last element to the root
  int i = 0;
  // sift-down: swap with smaller child until heap property holds
  while (true) {
    int l = 2 * i + 1, r = 2 * i + 2, s = i;
    if (l < size && data[l] < data[s])
      s = l; // left child is smaller
    if (r < size && data[r] < data[s])
      s = r; // right child is even smaller
    if (s == i)
      break; // current is smallest -> done
    int t = data[s];
    data[s] = data[i];
    data[i] = t;
    i = s;
  }
}

// Output total items sold and total revenue.
void VendingMachine::printResult() {
  cout << totalSold << " " << totalRevenue << "\n";
}

// ============================ kura (14931) ============================
// Reorder 1->2->3->4->5 into 1->5->2->4->3 by:
//   1) find midpoint via slow/fast pointers
//   2) split list and reverse the second half
//   3) interleave first half with reversed second half
// Wrapped in namespace kura so its ListNode doesn't clash with the stack's.
namespace kura {

ListNode *solve(ListNode *head) {
  // length 0/1/2 needs no reordering
  if (!head || !head->next || !head->next->next)
    return head;

  // (1) tortoise-and-hare to find the midpoint
  // when fast reaches end, slow is at the middle (first half gets the extra for
  // even length)
  ListNode *slow = head, *fast = head;
  while (fast->next && fast->next->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  // (2) split: cut list after slow, then reverse second half
  ListNode *sec = slow->next;
  slow->next = nullptr; // terminate first half

  ListNode *prev = nullptr; // builds reversed list
  while (sec) {
    ListNode *nxt = sec->next; // remember next BEFORE rewriting
    sec->next = prev;          // flip pointer
    prev = sec;                // advance prev
    sec = nxt;                 // advance sec
  }
  // prev now heads the reversed second half

  // (3) interleave: a, b, a->next, b->next, ...
  // capture an/bn before overwriting pointers (otherwise we'd lose the chains)
  ListNode *a = head, *b = prev;
  while (b) {
    ListNode *an = a->next;
    ListNode *bn = b->next;
    a->next = b;  // a points to the back-half element
    b->next = an; // b points to the next front-half element (or nullptr at end)
    a = an;
    b = bn;
  }

  return head;
}

} // namespace kura
