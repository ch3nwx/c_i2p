#include "13858.h"
#include <vector>
using namespace std;

// Open-Loop TSP on a tree.
//
// Closed-loop TSP on a tree costs 2 * sum_of_edge_weights (every edge crossed
// twice). Dropping the "return to start" rule lets us avoid retracing one
// path -- and the most we can save is the LONGEST path between any two
// nodes (the tree's diameter). So:
//
//     answer = 2 * total_weight - diameter
//
// Diameter in ONE DFS:
// For every node u, the longest path that turns AT u is
//     (longest downward path through one child) + (longest through another).
// So during a single post-order DFS we track, at each node, the top TWO
// values of (down[child] + edge_weight) among its children. Their sum is a
// candidate diameter (a path that passes through u). The single longest
// downward branch is what we return upward to the parent.
//
// One traversal, O(N), and it replaces the older "BFS twice" approach.

static long long dfs(int u, int parent, vector<vector<Edge>> &adj,
                     long long &diameter) {
    long long best1 = 0, best2 = 0; // top two downward path lengths from u
    for (Edge &e : adj[u]) {
        if (e.to == parent) continue;       // don't walk back up
        long long d = dfs(e.to, u, adj, diameter) + e.w;
        if (d > best1)      { best2 = best1; best1 = d; }
        else if (d > best2) { best2 = d; }
    }
    // path that bends at u: down through best1's child, back up, down through best2's
    if (best1 + best2 > diameter) diameter = best1 + best2;
    return best1; // tell parent: longest downward branch through u
}

long long openLoopTSP(int n, vector<vector<Edge>> &adj, long long total) {
    if (n <= 1) return 0;
    long long diameter = 0;
    dfs(0, -1, adj, diameter);
    return 2 * total - diameter;
}
