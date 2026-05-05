#include "question.h"
#include <iostream>
using namespace std;

List_stack::List_stack() : head(NULL), tail(NULL) {}

List_stack::~List_stack() {
  while (head) {
    ListNode *t = head;
    head = head->nextPtr;
    delete t;
  }
  tail = NULL;
}

void List_stack::push(const int &v) {
  ListNode *n = new ListNode(v);
  if (!head) {
    head = tail = n;
  } else {
    n->nextPtr = head;
    head->prevPtr = n;
    head = n;
  }
}

void List_stack::pop() {
  if (!head)
    return;
  ListNode *t = head;
  head = head->nextPtr;
  if (head)
    head->prevPtr = NULL;
  else
    tail = NULL;
  delete t;
}

void List_stack::print() {
  for (ListNode *c = head; c; c = c->nextPtr) {
    cout << c->data;
    if (c->nextPtr)
      cout << " ";
  }
}

void Matrix::add(const Matrix &rhs) {
  for (long long i = 0; i < n; i++)
    for (long long j = 0; j < n; j++)
      data[i][j] += rhs.data[i][j];
}

void Matrix::subtract(const Matrix &rhs) {
  for (long long i = 0; i < n; i++)
    for (long long j = 0; j < n; j++)
      data[i][j] -= rhs.data[i][j];
}

void Matrix::multiply(const Matrix &rhs) {
  long long **r = new long long *[n];
  for (long long i = 0; i < n; i++) {
    r[i] = new long long[n]();
    for (long long k = 0; k < n; k++) {
      long long a = data[i][k];
      if (!a)
        continue;
      for (long long j = 0; j < n; j++) {
        r[i][j] += a * rhs.data[k][j];
      }
    }
  }

  for (long long i = 0; i < n; i++)
    delete[] data[i];
  delete[] data;
  data = r;
}
