#include "init.h"

namespace Tarjan {
    // BRIDGE, CUT, SCC, CONFIGURE BEFORE USE
    const bool IS_DIRECTED = true;

    vector<int> removed, num, low, s;
    vector<vector<int>> g, sccs;
    int timer;

    void dfs(int i, int p = -1) {
        num[i] = low[i] = ++timer;
        s.push_back(i);
        int children = 0;
        for (int to: g[i]) {
            if (removed[to] || (to == p && !IS_DIRECTED)) {
                continue;
            }
            if (num[to]) {
                low[i] = min(low[i], num[to]);
            } else {
                dfs(to, i);
                low[i] = min(low[i], low[to]);
                if (low[to] > num[i]) {
                    /*BRIDGE i->to*/
                }
                if (low[to] >= low[i] && p < 0) {
                    /*CUT i*/
                }
                ++children;
            }
        }
        if (p < 0 && children > 1) {
            /*CUT i*/
        }
        if (low[i] == num[i]) { // SCC
            vector<int> scc;
            do {
                scc.push_back(s.back());
                removed[s.back()] = 1;
                s.pop_back();
            } while (scc.back() != i);
            sccs.push_back(scc);
        }
    }
}