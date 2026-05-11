#include "13858.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<vector<Edge>> adj(n);
    long long total = 0;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        total += w;
    }

    cout << openLoopTSP(n, adj, total) << "\n";
    return 0;
}
