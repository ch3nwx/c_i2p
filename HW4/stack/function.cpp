#include "10998.h"
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
    if (!head) return;
    ListNode *t = head;
    head = head->nextPtr;
    if (head) head->prevPtr = NULL;
    else tail = NULL;
    delete t;
}

void List_stack::print() {
    for (ListNode *c = head; c; c = c->nextPtr) {
        cout << c->data;
        if (c->nextPtr) cout << " ";
    }
}
