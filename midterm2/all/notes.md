# Midterm2 Line-by-Line Notes

---

## question.h — class & namespace definitions

### Header guard
```cpp
#ifndef MIDTERM2_QUESTION_H
#define MIDTERM2_QUESTION_H
```
Two of these problems define a struct called `Node` (corridor and station) with
DIFFERENT fields. Putting both in the global namespace would be a redefinition
error, so each is wrapped in its own namespace (`corridor::Node`, `station::Node`).
The casino classes don't conflict so they stay in the global scope; the
KuoYangPresent class also lives in `kuoyang::` to keep its private `Node` from
clashing with the others.

---

## 13182 — Casino

### Guest class
```cpp
class Guest {
public:
    Guest();
    Guest(string s, int m, int ski);
    string get_name();
    int get_money();
    int get_skill();
    void Win(int m);
private:
    string name;
    int money;
    int skill;
};
```
Plain data record for one guest. `Win(m)` just adds m to money — it does NOT
check for cheating or bankruptcy; that's the casino's job.

### Casino fields
```cpp
int fee;                 // current day's entrance fee
int guest_num;           // how many guests are in the casino RIGHT NOW
Guest *guest[1009];      // pointers to those guests
int income;              // running total across the whole month
int list_num;            // how many people have been blacklisted
string blacklist[1009];  // names, in the ORDER they got blacklisted
```
Two parallel arrays: `guest[]` is people currently inside (cleared every
EndDay), `blacklist[]` is permanent across days. Income accumulates forever.

### Constructor / destructor
```cpp
Casino::Casino() : fee(0), guest_num(0), income(0), list_num(0) {
    for (int i = 0; i < 1009; i++) guest[i] = NULL;
}
Casino::~Casino() {
    for (int i = 0; i < guest_num; i++) delete guest[i];
}
```
All counters start at zero. Destructor frees any guests still inside (e.g. if
EndDay was never called).

### Enterance
```cpp
void Casino::Enterance(int f) { fee = f; }
```
Just stores the fee for the rest of the day. Money is taken later in
GuestEnter.

### GuestEnter
```cpp
void Casino::GuestEnter(string s, int m, int ski) {
    for (int i = 0; i < list_num; i++)
        if (blacklist[i] == s) return;          // (1) blacklisted -> ignore
    for (int i = 0; i < guest_num; i++)
        if (guest[i]->get_name() == s) return;  // (2) already in -> ignore
    if (m <= fee) {
        income += m;
        blacklist[list_num++] = s;              // (3a) bankrupt at the door
    } else {
        income += fee;
        guest[guest_num++] = new Guest(s, m - fee, ski);   // (3b) enters
    }
}
```
Order of checks matters: blacklist first (ignored people don't pay anything),
then "already inside" (the same name re-entering on the same day is ignored
silently). The bankruptcy rule is `Y <= X` — note the `<=`, so paying EXACTLY
the fee still empties the wallet and gets you blacklisted.

### Win
```cpp
if (m >= 0) {
    g->Win(m);
    income -= m;                          // casino pays out
    if (m > 2 * g->get_skill()) {
        // cheater: kick + blacklist (casino still pays)
        ...
    }
} else {
    int X = -m, Y = g->get_money();
    if (Y <= X) {
        income += Y;                      // pay all, bankrupt
        // blacklist + remove
    } else {
        g->Win(m);                        // m is negative
        income += X;
    }
}
```
Two cases. Positive m: guest is winning, casino loses m, then check the
cheater rule (`>`, not `>=`). Negative m: guest must pay |m|; if their wallet
can't cover it, take whatever they have and blacklist them. The cheater check
ONLY applies to positive wins — losing more than 2*skill is never cheating.

When removing a guest mid-array we shift the tail down by one (`for i = idx ..
guest_num-1: guest[i] = guest[i+1]`), then decrement `guest_num`. Order in
this array doesn't matter — we look up by name, not by index.

### EndDay / Result
```cpp
void Casino::EndDay() {
    for (int i = 0; i < guest_num; i++) delete guest[i];
    guest_num = 0;
}
void Casino::Result() {
    cout << income << "\n";
    for (int i = 0; i < list_num; i++) cout << blacklist[i] << "\n";
}
```
EndDay just empties the guest list — anyone still inside leaves with their
money (no income change). Result prints total income then all blacklisted
names in the order they were added.

---

## 13472 — KuoYangPresent

### The model
- Doubly-linked list of `Node { prev, next, val, tag }`.
- `head`, `tail` are the REAL endpoints; `mid` is the LOGICAL median.
- `reverse` is a flag: when true, the user-visible front is the real tail.
- `now` is a global "modulo generation". Every node carries a `tag`. If
  `tag < now` when we read a value, we apply `val %= k` once and bump tag.
  Works because `(a%k)%k == a%k`, so one reduction is enough no matter how
  many ProgrammingTanoshi calls happened in between.

### Constructor
```cpp
KuoYangPresent::KuoYangPresent(int k_) {
    k = k_;
    head = mid = tail = NULL;
    sz = 0;
    now = 0;
    reverse = false;
}
```

### Push — add to logical tail, maybe move mid
```cpp
void KuoYangPresent::Push(int x) {
    Node *n = new Node;
    n->val = x; n->tag = now;
    n->prev = n->next = NULL;
    sz++;
    if (sz == 1) { head = tail = mid = n; return; }

    if (reverse) { n->next = head; head->prev = n; head = n; }
    else         { n->prev = tail; tail->next = n; tail = n; }

    if (sz % 2 == 1)
        mid = reverse ? mid->prev : mid->next;
}
```
Why `n->tag = now`? A brand-new value is "current" — it doesn't need any
deferred mod applied to it.

The mid-update rule: median position is `floor((sz+1)/2)`. Going from
even -> odd, the median shifts forward by one. Going odd -> even, it stays
put. So we only move mid on the even -> odd transition (i.e. when the new
sz is odd).

"Logical forward" depends on the reverse flag: with `reverse=false`, forward
is `mid->next`; with `reverse=true`, forward is `mid->prev` (because the
logical view runs tail -> head).

### Pop — remove logical median
```cpp
void KuoYangPresent::Pop() {
    Node *to_del = mid;
    Node *new_mid = reverse ? mid->next : mid->prev;
    // detach to_del
    Node *p = to_del->prev, *nx = to_del->next;
    if (p) p->next = nx;
    if (nx) nx->prev = p;
    if (to_del == head) head = nx;
    if (to_del == tail) tail = p;
    delete to_del;
    sz--;
    mid = (sz == 0) ? NULL : new_mid;
}
```
Sz is guaranteed odd, so mid is valid. Remember `new_mid` BEFORE deleting,
because we need to access `mid->prev`/`mid->next` while the node is still
alive. After pop, sz becomes even and the new median position is one step
LOGICAL-BACKWARD from the popped node.

We don't bother applying the lazy mod here because the value is being
deleted — no one will ever read it.

### Reverse — toggle flag, fix mid for even sz
```cpp
void KuoYangPresent::Reverse() {
    reverse = !reverse;
    if (sz > 0 && sz % 2 == 0) {
        mid = reverse ? mid->next : mid->prev;
    }
}
```
At odd sz, the median position is symmetric — it lands on the same node
under either direction, so mid doesn't need to move. At even sz, the
left-biased median (`floor((sz+1)/2) = sz/2`) flips to a different node, so
we step mid one space in the OLD logical-forward direction. After the flip,
"reverse" already holds the NEW state; new state `true` means old state was
`false` and old forward was `next`, hence `mid->next`.

### ProgrammingTanoshi — pure O(1) lazy bump
```cpp
void KuoYangPresent::ProgrammingTanoshi() { now++; }
```
That's the entire operation — just bump the generation counter. No nodes
are touched. The actual `% k` happens inside PrintList when we read a value
whose tag is stale.

### KuoYangTeTe — no-op
```cpp
void KuoYangPresent::KuoYangTeTe() {}
```
PrintList already resolves any deferred mod, so nothing to do here.

### PrintList — direction + lazy resolution
```cpp
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
```
Walk in the logical direction. For each node, resolve the lazy mod the first
time we see it after a ProgrammingTanoshi (`tag < now`). The resolution
update means subsequent prints don't redo the mod.

---

## 14932 — Endless Corridor (Floyd's algorithm, in C)

### Why O(1) memory matters
The hint specifically forbids storing per-node bookkeeping (e.g. a
`visited[]` array) — for the largest subtask N is too big, you'd MLE.
Floyd's tortoise-and-hare uses just two pointers.

### Phase 1 — find a meeting point if a cycle exists
```c
Node *slow = head, *fast = head;
int found = 0;
while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) { found = 1; break; }
}
```
Slow advances 1 step per iter, fast 2 steps. If there's a cycle, the gap
between them shrinks by 1 each iter and they eventually collide INSIDE the
cycle. If there's no cycle, fast falls off the end and we exit with
`found = 0`.

The `slow == fast` check is AFTER the move so we don't trip it on the
initial state where both are at head.

### Phase 2 — locate the cycle entry
```c
slow = head;
while (slow != fast) {
    slow = slow->next;
    fast = fast->next;
}
return slow;
```
Math identity: if the path from head to the cycle entry has length L, the
cycle has length C, and the meeting point is k steps into the cycle, then
moving one pointer back to head and stepping both at speed 1 makes them
collide exactly at the cycle entry.

### No-cycle path
```c
if (!found) {
    Node *c = head;
    while (c->next) c = c->next;
    return c;
}
```
If we got out of phase 1 without finding a meet, the list is acyclic. Walk
from head until `next == NULL`; that's the last room before the exit.

---

## 14934 — Station Marshalling (linked list with hash, in C)

### Why a hash table at all
SPLIT and CHECK both name a car by its ID. Scanning the platform's list to
find the car costs O(len), which is too slow on the big inputs. A hash from
ID to `Node*` makes lookups O(1).

### Hash
```c
#define HASH_SIZE 2000003
typedef struct HashEntry { int key; Node *val; int used; } HashEntry;
static HashEntry hash_table[HASH_SIZE];
```
`2000003` is a prime well above the worst-case car count, so probe chains
stay short. Open addressing with linear probing.

```c
static int hash_lookup(int key) {
    unsigned int h = ((unsigned int)key * 2654435769u) % HASH_SIZE;
    while (hash_table[h].used && hash_table[h].key != key)
        h = (h + 1) % HASH_SIZE;
    return h;
}
```
Knuth multiplicative hash (the constant is ~2^32 / golden_ratio) gives a
decent bit-mixing for arbitrary ints, then linear probe to the slot.

### enter — append to platform tail
```c
void enter(int p, int c) {
    Node *n = malloc(sizeof(Node));
    n->id = c;
    n->prev = tails[p]; n->next = NULL;
    if (tails[p]) tails[p]->next = n;
    else heads[p] = n;
    tails[p] = n;
    hash_set(c, n);
}
```
Standard doubly-linked list append, plus register the car in the hash.

### merge — splice src onto end of dest
```c
void merge(int p_src, int p_dest) {
    if (!heads[p_src]) return;
    if (!heads[p_dest]) {
        heads[p_dest] = heads[p_src];
        tails[p_dest] = tails[p_src];
    } else {
        tails[p_dest]->next = heads[p_src];
        heads[p_src]->prev = tails[p_dest];
        tails[p_dest] = tails[p_src];
    }
    heads[p_src] = NULL; tails[p_src] = NULL;
}
```
O(1) splice. We don't update any per-car platform tracking because the hash
is keyed only by ID — we never need to ask "which platform is this car on",
the input always tells us.

### split — cut just BEFORE car c
```c
void split(int p_src, int c, int p_dest) {
    Node *n = hash_get(c);
    Node *p = n->prev;
    if (p) p->next = NULL;
    n->prev = NULL;
    heads[p_dest] = n;
    tails[p_dest] = tails[p_src];
    if (p) tails[p_src] = p;
    else { heads[p_src] = NULL; tails[p_src] = NULL; }
}
```
Two cases on whether car c was at the head: if it was, p_src becomes empty
after the split. Either way, p_dest takes [c..tail], p_src keeps [head..p].

### reverse — flip every link on the platform
```c
void reverse(int p) {
    Node *c = heads[p];
    while (c) { Node *t = c->next; c->next = c->prev; c->prev = t; c = t; }
    Node *t = heads[p]; heads[p] = tails[p]; tails[p] = t;
}
```
Walk the list and swap `prev`/`next` on each node. Save `c->next` first
(`t = c->next`) because we're about to overwrite it. After the walk, the
real head and tail need swapping too. The problem caps total reverse work
across all calls so this is fine globally.

### check — k steps toward the front
```c
int check(int p, int c, int k) {
    Node *n = hash_get(c);
    while (k > 0 && n->prev) { n = n->prev; k--; }
    return n->id;
}
```
"Toward the front" = follow `prev`. The `n->prev` guard means we stop early
if we hit the head before completing k steps.

The platform argument is unused — the hash already pins the car's location.
The `(void)p` in the implementation silences an unused-parameter warning.

---

## question.cpp — entry points

### casino_main
Reads N days. For each day: a "Casino Q T" line that tells us how many
events Q and the entrance fee T, then Q events of the form "Guest …" or
"Win …", then implicit EndDay. Final Result after all days.

### kuoyang_main
Reads N K Q, builds the initial sequence with N pushes, then dispatches Q
operations. The "programming tanoshi" command is two whitespace-separated
words, so when none of `push`/`pop`/`reverse` matches, we read one extra
token to consume "tanoshi".

### corridor_main / station_main
Both keep their original C-style I/O (scanf/printf) since that's what the
partial judge code used; only the `Node` type is qualified with the
namespace.

### dispatcher
```cpp
int main(int argc, char **argv) {
    if (argc < 2) { ...usage... }
    string p = argv[1];
    if (p == "casino")   return casino_main();
    if (p == "kuoyang")  return kuoyang_main();
    if (p == "corridor") return corridor_main();
    if (p == "station")  return station_main();
    ...
}
```
First command-line argument selects which problem to run. The exit code of
each `*_main()` is the process exit code.
