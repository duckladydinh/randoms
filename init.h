#ifndef ALGO_CPP_INIT_H
#define ALGO_CPP_INIT_H

#include <bits/stdc++.h>
using namespace std;

typedef long long llint;

const llint INF = 1e16;
const double EPS = 1e-9;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; // pb_ds;

typedef tree<int, null_type, less<>, rb_tree_tag,
        tree_order_statistics_node_update> ordered_set;
// *X.find_by_order(0..<size)
// 0 <= X.order_of_key(-5) <= size

// unordered_map<int, int> s;
// mp.reserve(1024);
// s.max_load_factor(0.25);

#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, a, b) for(int i = a; i <= b; ++i)

#endif //ALGO_CPP_INIT_H
