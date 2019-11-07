#include "init.h"

// MO trick
// S = int(sqrt(N));
int S = sqrt(100000);
bool cmp(pair<int, int> A, pair<int, int> B) {
    if ((A.first / S) != (B.first / S)) {
        return A.first / S < B.first / S;
    }
    return A.second > B.second;
}

int N, K, opt[1000][1000], f[1000][0100], c[1000][1000];

// Divide and Conquer Optimization Tricks for DP
// Equation:	f[i][k] = min(f[j][k - 1] + c[j + 1][i])
// Condition:	opt[i - 1][k] <= opt[i][k] <= opt[i + 1][k]
// Complexity:	O(nklogn) instead of O(n^2 * k)
void divide_and_conquer(int l, int r, int k, int L, int R) {
    if (l > r) return;
    const int m = (l + r) / 2;
    for (int j = L; j <= min(m - 1, R); ++j) {
        if (opt[m][k] != -1 && f[m][k] <= f[j][k - 1] + c[j + 1][m]) {
            continue;
        }
        f[m][k] = f[j][k - 1] + c[j + 1][m];
        opt[m][k] = j;
    }
    divide_and_conquer(l, m - 1, k, L, opt[m][k]);
    divide_and_conquer(m + 1, r, k, opt[m][k], R);
}
void solve() {
    // Solve the base case k = 1, then
    for (int k = 2; k <= K; ++k) {
        divide_and_conquer(1, N, k, 1, N);
    }
}

// Knuth's Optimization for DP
// Equation: f[i][j] = min(f[i][k] + f[k + 1][j])
// Condition: opt[i][j - 1] <= opt[i][j] <= opt[i + 1][j]
// Complexity: O(n^2) instead of O(n^3)
int knuth() {
    for (int j = 1; j <= N; ++j) {
        // Solve base case: i = j
        for (int i = j - 1; i >= 1; --j) {
            for (int k = max(i, opt[i][j - 1]); k <= min(j - 1, opt[i + 1][j]); ++k) {
                if (opt[i][j] != -1 && f[i][j] <= f[i][k] + f[k + 1][j]) {
                    continue;
                }
                f[i][j] = f[i][k] + f[k + 1][j];
                opt[i][j] = k;
            }
        }
    }
    return f[1][N];
}