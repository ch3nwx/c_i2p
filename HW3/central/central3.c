#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 10005
#define LOG 18

typedef struct _Node {
  int id;
  int depth;
  struct _Node *ancestor[LOG]; // 2^k-th ancestor
} Node;

Node *node[MAXN]; // node[i] = pointer to node with id i

Node *create_node(int id) {
  Node *n = malloc(sizeof(Node));
  n->id = id;
  n->depth = 0;
  memset(n->ancestor, 0, sizeof(n->ancestor));
  node[id] = n;
  return n;
}

// Static adjacency lists (for efficient DFS)
int adj_to[MAXN * 2];
int adj_next[MAXN * 2];
int adj_head[MAXN];
int adj_cnt = 0;

void add_edge(int u, int v) {
  adj_to[adj_cnt] = v;
  adj_next[adj_cnt] = adj_head[u];
  adj_head[u] = adj_cnt++;
}

// DFS: set depth and direct parent (ancestor[0])
void dfs(Node *u, Node *par) {
  u->ancestor[0] = par;
  for (int i = adj_head[u->id]; i != -1; i = adj_next[i]) {
    Node *v = node[adj_to[i]];
    if (v != par) {
      v->depth = u->depth + 1;
      dfs(v, u);
    }
  }
}

// Build binary lifting table (ancestor[k] for k=1..LOG-1)
void build_lifting(int N) {
  for (int k = 1; k < LOG; k++)
    for (int i = 1; i <= N; i++)
      node[i]->ancestor[k] = node[i]->ancestor[k - 1]->ancestor[k - 1];
}

int lca(Node *u, Node *v) {
  // Bring u and v to same depth
  if (u->depth < v->depth) {
    Node *t = u;
    u = v;
    v = t;
  }
  int diff = u->depth - v->depth;
  for (int k = 0; k < LOG; k++)
    if ((diff >> k) & 1)
      u = u->ancestor[k];

  if (u == v)
    return u->id;

  // Lift both until parents converge
  for (int k = LOG - 1; k >= 0; k--)
    if (u->ancestor[k] != v->ancestor[k]) {
      u = u->ancestor[k];
      v = v->ancestor[k];
    }

  return u->ancestor[0]->id;
}

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q); // First two integers: N (nodes), Q (queries)

  // Initialize adjacency arrays (all to -1)
  memset(adj_head, -1, sizeof(adj_head));

  // Create all nodes (1 to N)
  for (int i = 1; i <= N; i++)
    create_node(i);

  // Read parent information (for nodes 2..N)
  for (int i = 2; i <= N; i++) {
    int p;
    scanf("%d", &p); // Parent of node i
    add_edge(p, i);
    add_edge(i, p);
  }

  // Initialize root (node 1) as the top of the tree
  for (int k = 0; k < LOG; k++)
    node[1]->ancestor[k] = node[1];

  // Build tree from root (DFS)
  dfs(node[1], node[1]);
  build_lifting(N);

  // Process all queries
  for (int i = 0; i < Q; i++) {
    int u, v;
    scanf("%d %d", &u, &v); // Query pair (u, v)
    printf("%d\n", lca(node[u], node[v]));
  }

  return 0;
}
