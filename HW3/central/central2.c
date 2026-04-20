#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 10005
#define LOG 18

typedef struct _Node {
  int id;
  int depth;
  struct _Node *ancestor[LOG]; // ancestor[k] = 2^k-th ancestor
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

// Children adjacency list (for DFS to compute depths and ancestor[0])
int adj_to[MAXN * 2], adj_next[MAXN * 2], adj_head[MAXN];
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

// Fill ancestor[k] for k = 1..LOG-1 using ancestor[k-1]
void build_lifting(int N) {
  for (int k = 1; k < LOG; k++)
    for (int i = 1; i <= N; i++)
      node[i]->ancestor[k] = node[i]->ancestor[k - 1]->ancestor[k - 1];
}

int lca(Node *u, Node *v) {
  // Bring u and v to the same depth
  if (u->depth < v->depth) { Node *t = u; u = v; v = t; }
  int diff = u->depth - v->depth;
  for (int k = 0; k < LOG; k++)
    if ((diff >> k) & 1)
      u = u->ancestor[k];

  if (u == v) return u->id;

  // Lift both until their parents converge
  for (int k = LOG - 1; k >= 0; k--)
    if (u->ancestor[k] != v->ancestor[k]) {
      u = u->ancestor[k];
      v = v->ancestor[k];
    }

  return u->ancestor[0]->id;
}

// Usage: ./central2 N Q p2 p3 ... pN qu1 qv1 qu2 qv2 ...
// p2..pN = parent of node 2..N (node 1 is root); then Q query pairs
int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s N Q p2 p3 ... pN qu1 qv1 ...\n", argv[0]);
    return 1;
  }

  int idx = 1;
  int N = atoi(argv[idx++]);
  int Q = atoi(argv[idx++]);

  memset(adj_head, -1, sizeof(adj_head));
  for (int i = 1; i <= N; i++)
    create_node(i);

  for (int i = 2; i <= N; i++) {
    int p = atoi(argv[idx++]);
    add_edge(p, i);
    add_edge(i, p);
  }

  // Root (node 1): depth 0, all ancestors point to itself
  for (int k = 0; k < LOG; k++)
    node[1]->ancestor[k] = node[1];

  dfs(node[1], node[1]);
  build_lifting(N);

  for (int i = 0; i < Q; i++) {
    int u = atoi(argv[idx++]);
    int v = atoi(argv[idx++]);
    printf("%d\n", lca(node[u], node[v]));
  }

  return 0;
}
