#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>

struct Edge {
    int to;
    long long w;
};

long long openLoopTSP(int n, std::vector<std::vector<Edge>> &adj, long long total);

#endif
