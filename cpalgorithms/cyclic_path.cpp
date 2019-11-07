#include "init.h"

// https://open.kattis.com/problems/allpairspath
// a = floyd(g), online O(N)
llint a[100][100];
void ford_cyclic(int n, int i, int j) {
    for (int k = 0; k < n; ++k) {
        if (a[k][k] < 0 && a[i][k] < INF && a[k][j] < INF) {
            a[i][j] = -INF;
            break;
        }
    }
}

// https://open.kattis.com/problems/shortestpath3
// d = ford_bellman(g), offline O(N * M)
vector<pair<int, llint>> g[100000];
void bellman_cyclic(vector<llint> &d, int n) {
    for (int it = 0; it < n; ++it) {
        for (int u = 0; u < n; ++u) {
            if (d[u] >= INF) continue;
            for (auto &v: g[u]) {
                if (d[v.first] > d[u] + v.second) {
                    d[v.first] = -INF;
                }
            }
        }
    }
}