# HW4 Line-by-Line Notes

---

## question.h — class definitions

### Header guard
```cpp
#ifndef HW4_QUESTION_H
#define HW4_QUESTION_H
```
"If this file hasn't been included before, define it now."
Prevents the compiler from reading the same header twice.

---

## 10998 — Stack (doubly-linked list)

### ListNode class
```cpp
class ListNode {
    friend class List_stack;
```
ListNode is a private data container. `friend class List_stack` means only List_stack is
allowed to touch its private members (data, nextPtr, prevPtr). Nobody else can.

```cpp
    public:
        ListNode(const int &info)
            : data(info), nextPtr(NULL), prevPtr(NULL) {}
```
Constructor. Takes a number by reference (no copy made). The `: data(info), ...` part is the
initializer list — sets all three members before the body runs. Body is empty `{}` because
the initializer list did everything. Every new node starts with no neighbors.

```cpp
    private:
        int data;           // the number stored in this node
        ListNode *nextPtr;  // pointer to the node in front (toward tail)
        ListNode *prevPtr;  // pointer to the node behind (toward head)
```

### List_stack class
```cpp
    private:
        ListNode *head;   // top of stack — where push and pop happen
        ListNode *tail;   // bottom of stack — only needed for cleanup
```
The stack is a doubly-linked list. head = top. Push/pop only touch head.
tail is kept only so the destructor can verify the list is fully emptied.

---

## function.cpp — stack implementation

### Constructor
```cpp
List_stack::List_stack() : head(NULL), tail(NULL) {}
```
Empty stack: both head and tail are null. Nothing in the list yet.

### Destructor
```cpp
List_stack::~List_stack() {
  while (head) {
    ListNode *t = head;    // save pointer to current node
    head = head->nextPtr;  // move head forward BEFORE deleting
    delete t;              // now safe to free the old node
  }
  tail = NULL;
}
```
Walk the list from head to tail. Each iteration: remember where you are, step forward,
then delete where you were. If you deleted first you'd lose the next pointer.
After the loop set tail to NULL for cleanliness (head is already NULL from the loop).

### push
```cpp
void List_stack::push(const int &v) {
  ListNode *n = new ListNode(v);   // allocate a new node on the heap
  if (!head) {
    head = tail = n;               // list was empty: new node is both head and tail
  } else {
    n->nextPtr = head;             // new node's "next" points to old top
    head->prevPtr = n;             // old top's "prev" points back to new node
    head = n;                      // new node is now the top
  }
}
```
Push always inserts at the front (head side). Think of it as prepending.
The two pointer assignments wire the new node into the chain before updating head.

### pop
```cpp
void List_stack::pop() {
  if (!head) return;               // empty stack: do nothing
  ListNode *t = head;              // remember the node we're about to remove
  head = head->nextPtr;            // move head to the next node
  if (head)
    head->prevPtr = NULL;          // new head has no predecessor
  else
    tail = NULL;                   // list just became empty, clear tail too
  delete t;                        // free the removed node
}
```
Pop removes the top (head). Save it, step head forward, fix the new head's prevPtr,
then delete the saved node. The `if (head)` check handles the case where we just
popped the last node.

### print
```cpp
void List_stack::print() {
  for (ListNode *c = head; c; c = c->nextPtr) {
    cout << c->data;
    if (c->nextPtr) cout << " ";   // space between items, NOT after the last one
  }
}
```
Walk from head to tail printing each value. The trick: only print a space when there
IS a next node, so there's no trailing space.

---

## 14605 — Matrix

### Constructor: identity matrix `Matrix(N)`
```cpp
Matrix(long long N) {
    this->n = N;
    this->data = new long long *[N];      // allocate N row-pointers
    for (long long i = 0; i < N; i++) {
        this->data[i] = new long long[N]; // allocate each row of N values
        for (long long j = 0; j < N; j++) {
            this->data[i][j] = (i == j) ? 1 : 0;  // 1 on diagonal, 0 elsewhere
        }
    }
}
```
Builds an N×N identity matrix (ones on the diagonal, zeros everywhere else).
`data` is a pointer-to-pointer: `data[i]` is a row, `data[i][j]` is one cell.

### Constructor: from existing data `Matrix(N, Data)`
```cpp
Matrix(long long N, long long **Data) {
    this->n = N;
    this->data = new long long *[N];
    for (long long i = 0; i < N; i++) {
        this->data[i] = new long long[N];
        for (long long j = 0; j < N; j++) {
            this->data[i][j] = Data[i][j];  // copy each cell from Data
        }
    }
}
```
Makes a deep copy of an existing 2D array. Allocates fresh memory and copies
every cell — doesn't just point at the same memory as Data.

### Destructor
```cpp
~Matrix() {
    for (long long i = 0; i < this->n; i++) delete[] this->data[i]; // free each row
    delete[] this->data;                                              // free row-pointer array
}
```
Two-step cleanup matching the two-step allocation. Must free rows first, then the
array of row-pointers. Reversing the order would be a bug (you'd lose the row addresses).

### add
```cpp
void Matrix::add(const Matrix &rhs) {
  for (long long i = 0; i < n; i++)
    for (long long j = 0; j < n; j++)
      data[i][j] += rhs.data[i][j];   // this[i][j] = this[i][j] + rhs[i][j]
}
```
Element-wise addition. Every cell in `this` gets the corresponding cell of `rhs` added to it.

### subtract
```cpp
void Matrix::subtract(const Matrix &rhs) {
  for (long long i = 0; i < n; i++)
    for (long long j = 0; j < n; j++)
      data[i][j] -= rhs.data[i][j];   // same idea, minus instead of plus
}
```

### multiply
```cpp
void Matrix::multiply(const Matrix &rhs) {
  long long **r = new long long *[n];  // fresh result matrix, all zeros
  for (long long i = 0; i < n; i++) {
    r[i] = new long long[n]();         // () means zero-initialised
    for (long long k = 0; k < n; k++) {
      long long a = data[i][k];
      if (!a) continue;                // skip: multiplying by 0 adds nothing
      for (long long j = 0; j < n; j++)
        r[i][j] += a * rhs.data[k][j];
    }
  }
  for (long long i = 0; i < n; i++) delete[] data[i];  // free old rows
  delete[] data;                                         // free old row-pointers
  data = r;                                              // point at new result
}
```
Standard matrix multiply: result[i][j] = sum over k of (this[i][k] * rhs[k][j]).
Loop order is i,k,j instead of i,j,k — this keeps `data[i][k]` constant in the
innermost loop which is better for CPU cache.
Can't write directly into `data` because we're also reading from it, so we allocate
a separate result `r`, compute into it, then replace `data` with `r`.

### transpose
```cpp
void Matrix::transpose() {
  for (long long i = 0; i < n; i++)
    for (long long j = i + 1; j < n; j++) {   // only upper triangle: j starts at i+1
      long long t = data[i][j];
      data[i][j] = data[j][i];
      data[j][i] = t;
    }
}
```
Swap every cell above the diagonal with its mirror below.
`j` starts at `i+1` not 0 — if you went through the whole row you'd swap everything
twice and end up back where you started.

### power
```cpp
void Matrix::power(long long x) {
  Matrix base(n, data);                         // copy of current matrix
  for (long long i = 0; i < n; i++)
    for (long long j = 0; j < n; j++)
      data[i][j] = (i == j) ? 1 : 0;           // reset this to identity (= "1")
  while (x > 0) {
    if (x & 1) this->multiply(base);            // if current bit is 1, multiply in base
    x >>= 1;                                    // shift to next bit
    if (x) base.multiply(base);                 // square base for next round
  }
}
```
Binary exponentiation: instead of multiplying n times, use the binary bits of x.
- `result` starts as identity (the matrix equivalent of the number 1)
- `base` starts as the original matrix
- For each bit of x: if bit is 1, fold base into result. Then square base.
- Example: x=6 (binary 110) → skip bit0, multiply at bit1, multiply at bit2
- Cost: O(n³ log x) instead of O(n³ × x)

---

## 14927 — VendingMachine (min-heap)

### The heap layout (mental model)
```
index:  0    1    2    3    4    5    6
             
        root
       /    \
    left    right       children of i: left=2i+1, right=2i+2
   /    \                parent of i: (i-1)/2
```
Smallest item is always at index 0 (the root). Every parent ≤ its children.

### Constructor
```cpp
VendingMachine::VendingMachine() {
  capacity = 16;             // initial array size
  data = new int[capacity];  // allocate the backing array
  size = 0;                  // no items yet
  totalRevenue = 0;
  totalSold = 0;
}
```

### store (push + sift-up)
```cpp
void VendingMachine::store(int price) {
  if (size == capacity) {           // array is full — grow it
    int nc = capacity * 2;
    int *nd = new int[nc];
    for (int i = 0; i < size; i++) nd[i] = data[i];  // copy old data
    delete[] data;
    data = nd;
    capacity = nc;
  }
  int i = size++;                   // place new item at the end, increment size
  data[i] = price;
  while (i > 0) {                   // sift-up: bubble new item toward root
    int p = (i - 1) / 2;           // parent index
    if (data[p] > data[i]) {       // parent is bigger than child — swap them
      int t = data[p]; data[p] = data[i]; data[i] = t;
      i = p;                        // move up to where parent was
    } else break;                   // parent is smaller — heap property holds, stop
  }
}
```
Add to the end (cheap), then bubble up until the new item finds its correct level.

### sell (pop-min + sift-down)
```cpp
void VendingMachine::sell() {
  if (size == 0) return;            // nothing to sell
  totalSold++;
  totalRevenue += data[0];          // data[0] is always the minimum
  size--;
  if (size == 0) return;            // heap is now empty, done
  data[0] = data[size];             // move the last item to the root to plug the hole
  int i = 0;
  while (true) {                    // sift-down: push root item to its correct level
    int l = 2*i+1, r = 2*i+2, s = i;  // s = index of smallest among {i, left, right}
    if (l < size && data[l] < data[s]) s = l;   // left child smaller?
    if (r < size && data[r] < data[s]) s = r;   // right child even smaller?
    if (s == i) break;              // already smallest among children — done
    int t = data[s]; data[s] = data[i]; data[i] = t;  // swap down
    i = s;                          // follow the swapped item down
  }
}
```
Remove root (the minimum). Can't leave a hole, so grab the last item and put it at
the root. It's probably too big to be root, so sift it down: repeatedly swap it with
whichever child is smaller until it's smaller than both children.

### printResult
```cpp
void VendingMachine::printResult() {
  cout << totalSold << " " << totalRevenue << "\n";
}
```

---

## 14931 — Kura (linked list reorder)

Goal: `1→2→3→4→5` becomes `1→5→2→4→3`
(interleave front of list with reversed back half)

### solve — step 1: find midpoint
```cpp
if (!head || !head->next || !head->next->next)
    return head;
```
If list has 0, 1, or 2 nodes there's nothing to reorder — return as-is.

```cpp
ListNode *slow = head, *fast = head;
while (fast->next && fast->next->next) {
    slow = slow->next;        // slow moves 1 step
    fast = fast->next->next;  // fast moves 2 steps
}
```
Tortoise-and-hare. When fast hits the end, slow is at the midpoint.
For 5 nodes: slow ends at node 3 (index 2). For 4 nodes: slow ends at node 2 (index 1).
First half always gets the extra node for odd lengths.

### solve — step 2: split and reverse second half
```cpp
ListNode *sec = slow->next;   // second half starts here
slow->next = nullptr;          // cut the list: terminate first half
```
Now we have two separate lists: `head...slow` and `sec...end`.

```cpp
ListNode *prev = nullptr;
while (sec) {
    ListNode *nxt = sec->next;  // save next BEFORE overwriting
    sec->next = prev;           // flip: this node now points backward
    prev = sec;                 // prev advances to current node
    sec = nxt;                  // sec advances to saved next
}
// prev is now the head of the reversed second half
```
Standard list reversal. Each iteration flips one arrow. Must save `nxt` first or
you lose the rest of the list when you overwrite `sec->next`.

### solve — step 3: interleave
```cpp
ListNode *a = head, *b = prev;  // a = front half, b = reversed back half
while (b) {
    ListNode *an = a->next;   // save a's next before overwriting
    ListNode *bn = b->next;   // save b's next before overwriting
    a->next = b;              // a points to b (insert b after a)
    b->next = an;             // b points to a's old next (rejoin front half)
    a = an;                   // advance a
    b = bn;                   // advance b
}
return head;
```
Weave the two halves together one node at a time.
Always save both `an` and `bn` before touching any pointers — overwriting one
pointer makes you lose the chain beyond it.

---

## question.cpp — main entry points

### stack_main
```cpp
List_stack L_stack;
char command[10];
int n;
while (cin >> command) {          // read one word at a time until EOF
    if (strcmp(command, "pop") == 0)       L_stack.pop();
    else if (strcmp(command, "push") == 0) { cin >> n; L_stack.push(n); }
    else if (strcmp(command, "print") == 0){ L_stack.print(); cout << endl; }
}
```
`strcmp` returns 0 when strings are equal. `cin >> command` returns false at EOF,
ending the loop.

### matrix_main
```cpp
cin >> n >> t;                    // n = matrix size, t = number of operations
long long **tmp = new long long *[n];
for (...) tmp[i] = new long long[n];   // allocate scratch 2D array for reading input
for (...) cin >> tmp[i][j];            // read initial matrix
Matrix res(n, tmp);                    // construct result matrix from it
while (t--) {                          // process t operations
    int o; cin >> o;
    if      (o == 1) { read tmp; Matrix mat(n,tmp); res.add(mat); }
    else if (o == 2) { read tmp; Matrix mat(n,tmp); res.subtract(mat); }
    else if (o == 3) { read tmp; Matrix mat(n,tmp); res.multiply(mat); }
    else if (o == 4) { res.transpose(); }
    else if (o == 5) { cin >> x; res.power(x); }
}
res.print();
```
`tmp` is reused as a scratch buffer for reading each operation's matrix from stdin.
`t--` decrements t after checking it, so the loop runs exactly t times.

### vending_main
```cpp
VendingMachine vm;
string cmd;
while (cin >> cmd) {
    if (cmd == "store") { cin >> price; vm.store(price); }
    else if (cmd == "sell") { vm.sell(); }
}
vm.printResult();
```
Read commands until EOF. `std::string` comparison with `==` works unlike C-strings.

### kura_main
```cpp
ios_base::sync_with_stdio(false);  // faster I/O: decouple C and C++ streams
cin.tie(NULL);                      // don't flush cout before every cin read
```
Standard competitive programming I/O speedup — safe when you only use cin/cout.

```cpp
int value, chk = 0;
for (int i = 0; i < N; ++i) {
    cin >> value;
    kura::ListNode *node = kura_newNode(value);
    chk ^= (reinterpret_cast<intptr_t>(node) + node->value);  // fingerprint each node
    // append node to list...
}
```
`chk` is a checksum: XOR of (memory address + value) for every node. Since XOR is
its own inverse, if solve reuses the exact same node objects, scanning the output
list will produce the same checksum. If solve secretly allocates new nodes, the
addresses change and `chk != chk2` catches it.

```cpp
kura::ListNode *result = kura::solve(head);
int chk2 = 0;
// print result, compute chk2 simultaneously
if (chk != chk2) cout << "Wrong Answer\n";
```
Print and verify in one pass. If checksums differ, solve created new nodes instead
of reusing existing ones — that's a bug the grader wants to catch.

```cpp
curr = result;
while (curr != nullptr) {
    kura::ListNode *tmp = curr;
    curr = curr->next;
    delete tmp;
}
```
Same pattern as the stack destructor: save current, advance, then delete saved.

### dispatcher (main)
```cpp
int main(int argc, char **argv) {
    if (argc < 2) { cerr << "usage: ..."; return 1; }
    string p = argv[1];
    if (p == "stack")   return stack_main();
    if (p == "matrix")  return matrix_main();
    if (p == "vending") return vending_main();
    if (p == "kura")    return kura_main();
    cerr << "unknown problem: " << p << "\n";
    return 1;
}
```
`argc` = number of command-line arguments (program name counts as 1, so `argc < 2`
means no argument was given). `argv[1]` is the first real argument.
The return value of each `*_main()` propagates back as the process exit code.
