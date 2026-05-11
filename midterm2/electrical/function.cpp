#include "14224.h"
#include <queue>
#include <vector>
using namespace std;

// Huffman coding.
//
// Each appliance i contributes a[i] * depth_i to the total cost, where depth_i
// is the number of edges from the outlet (root) to that appliance. So we want
// to minimise sum(a_i * depth_i) — the classical Huffman tree cost.
//
// Algorithm: keep a min-heap of subtree weights. Repeatedly pull the two
// smallest, combine them under a new internal node (a power strip) with
// weight equal to their sum, and add that sum to the total. The accumulated
// sum equals sum(a_i * depth_i).
long long huffman(int n, long long *a) {
    if (n <= 0) return 0;
    if (n == 1) return a[0]; // degenerate: single appliance, one edge of current a[0]

    priority_queue<long long, vector<long long>, greater<long long>> pq;
    for (int i = 0; i < n; i++) pq.push(a[i]);

    long long total = 0;
    while (pq.size() > 1) {
        long long x = pq.top(); pq.pop();
        long long y = pq.top(); pq.pop();
        long long s = x + y;
        total += s;     // this sum becomes the current on the edge above the new node
        pq.push(s);
    }
    return total;
}
