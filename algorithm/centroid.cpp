// LAM GIA THUAN - centroid decomposition
// tested on http://codeforces.com/contest/321/problem/C
// return a tree with edge i to mom[i], mom[root] = -1
const int MAX = 200100;

vector<int> G[MAX];
namespace centroid {
    vector<int> sz(MAX), mom(MAX);
    auto &g = G;

    int dfs(int i, int s, int p) {
        sz[i] = 1; // no need to empty sz again
        int child = 0, ans = -1;
        for (int j: g[i]) {
            if (j != p && mom[j] == 0) {
                int res = dfs(j, s, i);
                if (res != -1) ans = res;
                child = max(child, sz[j]);
                sz[i] += sz[j];
            }
        }
        return max(child,s-sz[i])*2 <= s ? i : ans;
        // '<=' not < or will get MLE
    }
    // root can be any vertex, p is the previous centroid
    void run(int root, int n, int p) {
        int i = dfs(root, n, -1);
        if (i != -1) {
            if (i != root) dfs(i, n, -1);
            mom[i] = p;
            for (int j: g[i]) {
                if (mom[j] == 0) run(j, sz[j], i);
            }
        }
    }
}
