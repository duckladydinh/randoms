#include "init.h"

void z_algo(string &s, int left, int eright, int *z) {
    int L = -1, R = -1, i = left;
    z[i] = 0;
    while (++i < eright) {
        z[i] = i >= R ? 0 : min(R - i, z[i - L + left]);
        while (i + z[i] < eright && s[i + z[i]] == s[z[i] + left]) ++z[i];
        if (i + z[i] > R) L = i, R = i + z[i];
    }
}

int fsm[100][26];
void FSM(string s, int m, int *p) {
    int n = s.length();
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            if ((s[i] - 'a') == j) fsm[i][j] = i + 1;
            else fsm[i][j] = (i == 0) ? 0 : fsm[p[i - 1]][j];
        }
    }
}


void p_algorithm(string s, int n, int *p) {
    int k = p[0] = 0;
    for (int i = 1; i < n; ++i) {
        while (k > 0 && s[k] != s[i]) {
            k = p[k - 1];
        }
        k += (s[k] == s[i]);
        p[i] = k;
    }
}

void KMP(string str, string pat, int *p) {
    pat += "#";
    int n = pat.size(), m = str.size(), k = 0;
    p_algorithm(pat, n, p);
    for (int i = 0; i < m; ++i) {
        while (k > 0 && pat[k] != str[i]) {
            k = p[k - 1];
        }
        k += (pat[k] == str[i]);
        if (k == n - 1) {
            cout << "Matched at position " << i << "\n";
        }
    }
}