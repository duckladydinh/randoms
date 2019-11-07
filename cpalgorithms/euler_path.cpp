#include "init.h"

// https://open.kattis.com/problems/eulerianpath

// Check existence condition before use
vector<int> adj[10000];
vector<int> euler(int i) {
    vector<int> o;
    stack<int> s;
    s.push(i);
    while (!s.empty()) {
        i = s.top();
        if (adj[i].empty()) {
            o.emplace_back(i);
            s.pop();
        } else {
            s.push(adj[i].back());
            adj[i].pop_back();
        }
    }
    reverse(begin(o), end(o));
    return o;
}
