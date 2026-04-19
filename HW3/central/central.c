#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 10005
#define LOG 18

typedef struct _Node {
  int id;
  int depth;
  struct _Node **children;
  int count;
} Node;

Node *Node_id[MAXN];

Node *create_note(int val) {
  Node *n = malloc(sizeof(Node));
  n->id = val;
  n->depth = 0;
  n->children = NULL;
  n->count = 0;
  Node_id[val] = n;
  return n;
}

void add_child(Node *parent, Node *child) {
  parent->children =
      realloc(parent->children, sizeof(Node *) * (parent->count + 1)); // FIX: parens
  parent->children[parent->count++] = child;
  child->depth = parent->depth + 1;
}

int euler[MAXN * 2];
int first[MAXN];
int euler_sz = 0;

void dfs(Node *u) {
  first[u->id] = euler_sz;
  euler[euler_sz++] = u->id;
  for (int i = 0; i < u->count; i++) {
    dfs(u->children[i]);
    euler[euler_sz++] = u->id;
  }
}

int sparse[LOG][MAXN * 2];
int lg[MAXN * 2];

void build_sparse() {
  lg[1] = 0;
  for (int i = 2; i < euler_sz; i++)
    lg[i] = lg[i / 2] + 1;

  for (int i = 0; i < euler_sz; i++)
    sparse[0][i] = i;

  for (int k = 1; (1 << k) <= euler_sz; k++) {
    for (int i = 0; i + (1 << k) <= euler_sz; i++) {
      int a = sparse[k - 1][i];
      int b = sparse[k - 1][i + (1 << (k - 1))];
      // FIX: compare depth, not pointer
      sparse[k][i] = (Node_id[euler[a]]->depth <= Node_id[euler[b]]->depth) ? a : b;
    }
  }
}

int rmq(int l, int r) {
  int k = lg[r - l + 1]; // FIX: r - l, not l - r
  int a = sparse[k][l];
  int b = sparse[k][r - (1 << k) + 1];
  // FIX: compare depth, not pointer
  return (Node_id[euler[a]]->depth <= Node_id[euler[b]]->depth) ? a : b;
}

int lca(int u, int v) {
  int l = first[u], r = first[v];
  if (l > r) { // FIX: swap so l <= r (was r > l, which left l > r)
    int tmp = l;
    l = r;
    r = tmp;
  }
  return euler[rmq(l, r)];
}

// Adjacency list for building undirected tree
int adj_to[MAXN * 2], adj_next[MAXN * 2], adj_head[MAXN];
int adj_cnt = 0;

void add_edge(int u, int v) {
  adj_to[adj_cnt] = v;
  adj_next[adj_cnt] = adj_head[u];
  adj_head[u] = adj_cnt++;
}

void build_tree(int u, int par) {
  for (int i = adj_head[u]; i != -1; i = adj_next[i]) {
    int v = adj_to[i];
    if (v != par) {
      add_child(Node_id[u], Node_id[v]);
      build_tree(v, u);
    }
  }
}

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);

  memset(adj_head, -1, sizeof(adj_head));
  for (int i = 1; i <= N; i++)
    create_note(i);

  // Line 2: parent of node 2, 3, ..., N (node 1 is root)
  for (int i = 2; i <= N; i++) {
    int p;
    scanf("%d", &p);
    add_edge(p, i);
    add_edge(i, p);
  }

  build_tree(1, -1);
  dfs(Node_id[1]);
  build_sparse();

  for (int i = 0; i < Q; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    printf("%d\n", lca(u, v));
  }

  return 0;
}
