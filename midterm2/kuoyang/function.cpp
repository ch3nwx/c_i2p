#include "13472.h"
#include <iostream>
using namespace std;

// Doubly-linked list with lazy modulo and O(1) reverse via flag.
//
// Layout invariants:
//   - head/tail are real endpoints of the linked list.
//   - reverse flag toggles the LOGICAL direction. When reverse=true, the user's
//     "front" is real tail and "back" is real head.
//   - mid points to the LOGICAL median position floor((sz+1)/2) (1-indexed).
//   - now is a counter incremented by ProgrammingTanoshi.
//   - each node carries tag = value of `now` when its val was last reduced %k.
//     If tag < now when we read the value, apply v %= k once and bump tag.
//     This works because (a%k)%k == a%k, so one reduction suffices regardless
//     of how many ProgrammingTanoshi calls happened in between.

KuoYangPresent::KuoYangPresent(int k_) {
    k = k_;
    head = mid = tail = NULL;
    sz = 0;
    now = 0;
    reverse = false;
}

void KuoYangPresent::Push(int x) {
    Node *n = new Node;
    n->val = x;
    n->tag = now;        // brand new value: already "current" w.r.t. mod state
    n->prev = n->next = NULL;

    sz++;
    if (sz == 1) {
        head = tail = mid = n;
        return;
    }

    // append to the LOGICAL tail
    if (reverse) {
        // logical tail = real head -> prepend
        n->next = head;
        head->prev = n;
        head = n;
    } else {
        n->prev = tail;
        tail->next = n;
        tail = n;
    }

    // mid update: only when sz transitions even -> odd does the median shift.
    // Move mid one step in the LOGICAL forward direction.
    if (sz % 2 == 1) {
        mid = reverse ? mid->prev : mid->next;
    }
}

void KuoYangPresent::Pop() {
    // Pop the LOGICAL median. sz is guaranteed odd, so mid is valid.
    Node *to_del = mid;
    Node *new_mid = reverse ? mid->next : mid->prev;

    // detach to_del from the doubly-linked list
    Node *p = to_del->prev, *nx = to_del->next;
    if (p) p->next = nx;
    if (nx) nx->prev = p;
    if (to_del == head) head = nx;
    if (to_del == tail) tail = p;

    delete to_del;
    sz--;
    mid = (sz == 0) ? NULL : new_mid;
}

void KuoYangPresent::Reverse() {
    reverse = !reverse;
    // Even-length lists pick floor((sz+1)/2) = sz/2 as the median; that
    // position MIRRORS to a different node when we flip. Walk mid one step
    // in the OLD logical-forward direction so it lands on the new median.
    if (sz > 0 && sz % 2 == 0) {
        // After the flip, "reverse" already holds the NEW state. New state
        // reverse=true <=> old was false <=> old logical-forward = real next.
        mid = reverse ? mid->next : mid->prev;
    }
}

void KuoYangPresent::ProgrammingTanoshi() {
    // O(1) lazy: just bump the global tag. Actual mod application is deferred
    // until the value is read (PrintList).
    now++;
}

void KuoYangPresent::KuoYangTeTe() {
    // No-op: PrintList resolves any deferred mod on the fly.
}

void KuoYangPresent::PrintList() {
    if (reverse) {
        for (Node *c = tail; c; c = c->prev) {
            if (c->tag < now) { c->val %= k; c->tag = now; }
            cout << c->val << " ";
        }
    } else {
        for (Node *c = head; c; c = c->next) {
            if (c->tag < now) { c->val %= k; c->tag = now; }
            cout << c->val << " ";
        }
    }
    cout << "\n";
}
