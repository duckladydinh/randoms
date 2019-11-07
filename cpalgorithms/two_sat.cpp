#include "init.h"

namespace TwoSat {
    const int MAXN = 10010; // 2-sat: MAXN = 2*maxvars

    vector<int> adj[MAXN], radj[MAXN], bycol[MAXN + 1], st;
    int col, color[MAXN];
    bool vis[MAXN];

    void init() {
        for (int i = 0; i < MAXN; ++i) {
            adj[i].clear(), radj[i].clear();
        }
    }

    void dfs(int u, vector<int> g[]) {
        if (vis[u]) return;
        vis[u] = true;
        for (int v: g[u]) {
            dfs(v, g);
        }
        if (col) {
            color[u] = col;
            bycol[col].push_back(u);
        } else st.push_back(u);
    }

    // this computes SCCs, outputs them in bycol, in topological order
    void kosaraju(int n) { // n = number of nodes
        st.clear();
        memset(vis, 0, sizeof vis);

        col = 0;
        for (int i = 0; i < n; ++i) {
            dfs(i, adj);
        }
        memset(vis, 0, sizeof vis);
        memset(color, 0, sizeof color);
        while (!st.empty()) {
            bycol[++col].clear();
            int x = st.back();
            st.pop_back();
            if (color[x]) continue;
            dfs(x, radj);
        }
    }

// 2-SAT
    int assign[MAXN]; // for 2-sat only
    int var(int x) {
        return x << 1;
    }

    bool solvable(int vars) {
        kosaraju(2 * vars);
        for (int i = 0; i < vars; ++i) {
            if (color[var(i)] == color[1 ^ var(i)]) return 0;
        }
        return true;
    }

    void assign_vars() {
        memset(assign, 0, sizeof assign);
        for (int c = 1; c <= col; ++c) {
            for (int it: bycol[c]) {
                int v = it >> 1;
                bool neg = it & 1;
                if (assign[v]) continue;
                assign[v] = neg ? 1 : -1;
            }
        }
    }

    void add_impl(int v1, int v2) {
        adj[v1].push_back(v2);
        radj[v2].push_back(v1);
    }

    void add_equiv(int v1, int v2) {
        add_impl(v1, v2);
        add_impl(v2, v1);
    }

    void add_or(int v1, int v2) {
        add_impl(1 ^ v1, v2);
        add_impl(1 ^ v2, v1);
    }

    void add_xor(int v1, int v2) {
        add_or(v1, v2);
        add_or(1 ^ v1, 1 ^ v2);
    }

    void add_true(int v1) {
        add_impl(1 ^ v1, v1);
    }

    void add_and(int v1, int v2) {
        add_true(v1);
        add_true(v2);
    }

    int parse(int i) {
        if (i > 0) return var(i - 1);
        else return 1 ^ var(-i - 1);
    }

    void sample_main() {
        int n, m;
        cin >> n >> m; // m = number of clauses to follow
        while (m--) {
            string op;
            int x, y;
            cin >> op >> x >> y;
            x = parse(x);
            y = parse(y);
            if (op == "or") add_or(x, y);
            if (op == "and") add_and(x, y);
            if (op == "xor") add_xor(x, y);
            if (op == "imp") add_impl(x, y);
            if (op == "equiv") add_equiv(x, y);
        }
        if (!solvable(n)) {
            cout << "Impossible" << endl;
            return;
        }
        assign_vars();
        for (int i = 0; i < n; ++i) {
            cout << ((assign[i] > 0) ? (i + 1) : -i - 1) << "\n";
        }
    }
}