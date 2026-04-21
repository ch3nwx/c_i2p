# HW3 — Logic & Solution Notes

---

## 1. Hot Spring (Josephus Variant)

### Problem
N people stand in a **circular doubly-linked list**, each holding a `tolerance` value.
Starting step is K. Each round:
1. Move `|k|` steps forward (k > 0) or backward (k < 0) from the current position.
2. Eliminate that person and print their id.
3. The **next step becomes the eliminated person's tolerance**.
4. Repeat until one person remains — print the survivor.

### Key Insight
This is a **Josephus-problem variant** where the step size is dynamic.

The tricky part is the modular reduction with a signed step:

```c
int r = k % n;
k = (r == 0) ? (k > 0 ? n : -n) : r;
```

- If `k % n == 0`, a full lap is taken — clamp to `±n` so the person at the current position is chosen.
- Otherwise keep the remainder, preserving the sign (direction).

After the modulo, move `|k| - 1` steps (not `|k|`) because the current node counts as step 0, not step 1:

```c
Move(&cur, (k > 0) ? k - 1 : k + 1);
```

After elimination, `Relink` removes the node and returns the **next** or **previous** node as the new starting position depending on the direction of `k`.

### Trace (N=5, K=2, tolerances=[3,−1,2,−4,1])

| Round | k  | n | Eliminated | Next k |
|-------|----|---|------------|--------|
| 1     | 2  | 5 | 2          | −1     |
| 2     | −1 | 4 | 3          | 2      |
| 3     | 2  | 3 | 4          | −4     |
| 4     | −4 | 2 | 1          | 3      |
| —     | —  | 1 | survivor=5 | —      |

Output: `2 3 4 1` then `5`

### Data Structure
Circular doubly-linked list — O(1) removal, O(k) traversal per round.

---

## 2. Queue Correction (Reverse Linked List [l, r])

### Problem
Given a singly linked list of N nodes (with a dummy head), reverse the nodes from position `l` to `r` (1-based). Only `next` pointers may be changed — node values and addresses must stay the same.

### Key Insight
Classic in-place reversal in three steps:

```
dummy → [1] → ... → [l-1] → [l] → [l+1] → ... → [r] → [r+1] → ...
                      pre     tail                  prev   cur
```

1. Walk to `pre` (the node just before position `l`).
2. Reverse the sublist `[l..r]` — `tail` (the l-th node) ends up as the new tail.
3. Reconnect: `pre->next = prev` (new head of reversed segment), `tail->next = cur` (node after r).

```c
void solve(Node *head, int l, int r) {
    Node *pre = head;
    for (int i = 1; i < l; i++) pre = pre->next;

    Node *prev = NULL, *cur = pre->next, *tail = cur;

    for (int i = l; i <= r; i++) {
        Node *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    pre->next = prev;
    tail->next = cur;
}
```

### Example
List: `4 → 6 → 7 → 8 → 3`, l=2, r=4

- Reverse `[6,7,8]` → `[8,7,6]`
- Result: `4 → 8 → 7 → 6 → 3` ✓

---

## 3. Same Tree (Dual EBNF Parser)

### Problem
Two binary trees are given in **different string formats**. Determine if they represent the same tree.

| Tree | Format (EBNF) |
|------|---------------|
| T    | `(INT/TREE/TREE)` or empty for NIL |
| S    | `INT(TREE)(TREE)` or empty for NIL |

### Key Insight
Write a **recursive descent parser** for each format. Both parsers build the same internal struct, then a simple recursive equality check decides the answer.

**Parser T** — triggered by `(`, NIL when current char is not `(`:
```c
Node* parseT(const char *s, int *pos) {
    if (s[*pos] != '(') return NULL;       // NIL
    (*pos)++;                               // consume '('
    // read integer ...
    (*pos)++;                               // consume '/'
    Node *left  = parseT(s, pos);
    (*pos)++;                               // consume '/'
    Node *right = parseT(s, pos);
    (*pos)++;                               // consume ')'
    ...
}
```

**Parser S** — triggered by a digit, NIL when current char is not a digit:
```c
Node* parseS(const char *s, int *pos) {
    if (!isdigit(s[*pos])) return NULL;    // NIL
    // read integer ...
    (*pos)++;                               // consume '('
    Node *left  = parseS(s, pos);
    (*pos)++;                               // consume ')'
    (*pos)++;                               // consume '('
    Node *right = parseS(s, pos);
    (*pos)++;                               // consume ')'
    ...
}
```

**Equality check** — standard recursive comparison:
```c
int same(Node *a, Node *b) {
    if (!a && !b) return 1;
    if (!a || !b) return 0;
    return a->val == b->val && same(a->left, b->left) && same(a->right, b->right);
}
```

### Example
`(4//(1/(3//(0//))/(2//)))` and `4(3()(0()()))(1()(2()()))` → **NO**  
`(0/(3/(2//(1//))/)/(4//))` and `0(3(2()(1()()))())(4()())` → **YES**

---

## 4. Central — LCA via Euler Tour + Sparse Table (stdin)

### Problem
Given a rooted tree (node 1 = root), answer Q queries: for each pair (u, v) find their **Lowest Common Ancestor (LCA)**.

Input format:
- Line 1: `N Q`
- Line 2: `parent[2] parent[3] ... parent[N]` (N−1 values, node 1 is root)
- Lines 3…: Q queries `u v`

### Key Insight — Euler Tour + RMQ

**Step 1 — Euler Tour**: perform DFS and record every node visit (including re-visits on return). For N nodes the tour has **2N−1** entries. The LCA of u and v is the **shallowest node** between their first appearances in the tour.

```
DFS visits: first[u] ... (subtree of u) ... first[u] ... first[v] ...
                LCA is the min-depth node in this range
```

**Step 2 — Sparse Table (RMQ)**: precompute range-minimum in O(N log N); answer any range query in O(1).

```c
// sparse[k][i] = index of min-depth node in euler[i .. i + 2^k - 1]
sparse[k][i] = (depth[euler[a]] <= depth[euler[b]]) ? a : b;
```

**Step 3 — LCA query**:
```c
int lca(int u, int v) {
    int l = first[u], r = first[v];
    if (l > r) swap(l, r);          // ensure l <= r
    return euler[rmq(l, r)];
}
```

### Bugs Fixed in Original Code

| Location | Bug | Fix |
|----------|-----|-----|
| `add_child` | `sizeof(Node*) * count + 1` | `sizeof(Node*) * (count + 1)` — precedence |
| `build_sparse` / `rmq` | pointer comparison `Node_id[x] <= Node_id[y]` | compare `->depth` |
| `rmq` | `lg[l - r + 1]` (negative) | `lg[r - l + 1]` |
| `lca` | `if (r > l)` leaves l > r | `if (l > r)` — swap to ensure l ≤ r |

---

## 5. Central 2 — LCA via Binary Lifting (command-line args)

### Problem
Same LCA problem as above, but:
- Input comes from **command-line arguments** (argc/argv) instead of stdin.
- Algorithm replaced with **binary lifting**.

Usage:
```
./central2 N Q p2 p3 ... pN qu1 qv1 qu2 qv2 ...
```

### Key Insight — Binary Lifting

Each node stores a table of **power-of-2 ancestors** directly in its struct:

```c
typedef struct _Node {
    int id, depth;
    struct _Node *ancestor[LOG]; // ancestor[k] = 2^k-th ancestor
} Node;
```

**Preprocessing** — fill `ancestor[k]` for k = 1..LOG−1:
```c
node[i]->ancestor[k] = node[i]->ancestor[k-1]->ancestor[k-1];
```
To jump 2^k steps = jump 2^(k−1) steps twice. Root's all ancestors point to itself.

**LCA(u, v)**:
1. **Equalise depths** — lift the deeper node one bit at a time:
   ```c
   int diff = u->depth - v->depth;
   for (int k = 0; k < LOG; k++)
       if ((diff >> k) & 1) u = u->ancestor[k];
   ```
2. **If equal** → u is the LCA, return.
3. **Lift both** from the highest bit down — only jump when ancestors differ (stop just below LCA):
   ```c
   for (int k = LOG-1; k >= 0; k--)
       if (u->ancestor[k] != v->ancestor[k]) {
           u = u->ancestor[k];
           v = u->ancestor[k];
       }
   return u->ancestor[0]->id; // common parent
   ```

### Comparison

| | Euler Tour + Sparse Table | Binary Lifting |
|-|--------------------------|----------------|
| Preprocessing | O(N log N) | O(N log N) |
| Query | **O(1)** | O(log N) |
| Memory | O(N log N) — Euler array + table | O(N log N) — ancestor table only |
| Simplicity | More steps (DFS, RMQ build) | Simpler logic |

Binary lifting trades constant-time queries for simpler, more memory-efficient code — a good fit for most competitive programming constraints.

---

## Study Guide — Quick Memory Hooks

### 🌊 1. Hot Spring
> *"Count, kick, inherit mood, repeat."*

- Circle of people, step K, kick person at step K, their tolerance becomes next K
- **Key line:** `r = k % n` → if `r == 0`, clamp to `±n` (full lap = current person)
- Move `|k| - 1` steps, not `|k|` — you're already on position 0
- Negative K = go backwards

### 🐘 2. Queue Correction
> *"Find the gate (pre), flip the chain, reattach the ends."*

- 4 pointers: `pre` (before l), `tail` (l-th node = new tail), `prev` (new head after flip), `cur` (node after r)
- Reverse loop: `cur->next = prev`, advance both
- Reconnect: `pre->next = prev`, `tail->next = cur`

### 🌳 3. Same Tree
> *"Parse to the same struct, then compare."*

- Two formats, one internal tree — write one parser per format
- **T parser:** starts on `(` → NIL if no `(`
- **S parser:** starts on digit → NIL if no digit
- Both consume their delimiters in exact order, recurse for left/right
- Final check is just standard recursive tree equality

### 📐 4. Central (Euler Tour)
> *"Flatten → find range → shallowest = ancestor."*

- DFS the tree, record every visit (including backtrack) → Euler tour array
- LCA(u, v) = node with **minimum depth** between `first[u]` and `first[v]` in the tour
- Sparse table answers range-min in O(1): `sparse[k][i]` = best index in `[i, i+2^k-1]`
- Build bottom-up (k=1 to LOG), query with two overlapping windows of size `2^k`

### ⬆️ 5. Central 2 (Binary Lifting)
> *"Equalize depth → meet or lift together → parent is answer."*

- Each node holds `ancestor[k]` = pointer to its 2^k-th ancestor
- Build: `ancestor[k] = ancestor[k-1]->ancestor[k-1]` (jump half twice)
- Root's ancestors all point to itself (safe sentinel)
- LCA steps:
  1. Lift deeper node by `diff` bits
  2. If same → return
  3. Lift both top-down, jump only when ancestors differ
  4. Return `ancestor[0]` (one step above where they stopped)

---

## At-a-Glance Summary

| # | Problem | Data Structure | Core Trick |
|---|---------|---------------|------------|
| 1 | Hot Spring | Circular doubly-linked list | Signed modulo + dynamic step |
| 2 | Queue Correction | Singly linked list | 4-pointer in-place reversal |
| 3 | Same Tree | Binary tree (built on parse) | Two recursive descent parsers |
| 4 | Central | Tree + Euler array + sparse table | RMQ on flattened DFS tour |
| 5 | Central 2 | Tree + `ancestor[LOG]` per node | Binary lifting with struct pointers |
