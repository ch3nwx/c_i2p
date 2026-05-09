#ifndef FUNCTION_H
#define FUNCTION_H

struct Node {
    Node *prev;
    Node *next;
    int val;
    int tag;
};

class KuoYangPresent {
public:
    KuoYangPresent(int k);
    void Push(int x);
    void Pop();
    void Reverse();
    void ProgrammingTanoshi();
    void KuoYangTeTe();
    void PrintList();

private:
    Node *head, *mid, *tail;
    int sz, k;
    int now;
    bool reverse;
};

#endif
