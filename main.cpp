#include <bits/stdc++.h>
#include "init.h"
using namespace std;

template <typename... T>
void print(T... args) {
    ((cout << args << " "), ...);
}
template <typename... T>
void input(T&... args) {
    ((cin >> args), ...);
}

int main() {
    ordered_set a;
    for (int i = 8; i >= 0; --i) {
        a.insert(i);
    }

    cout << (a.order_of_key(10)) << "\n";
    cout << (a.order_of_key(11)) << "\n";
    cout << (a.order_of_key(9)) << "\n";
    cout << (a.order_of_key(8)) << "\n";
    cout << (a.order_of_key(7)) << "\n";
    cout << (a.order_of_key(0)) << "\n";
    cout << (a.order_of_key(-1)) << "\n";
    cout << (a.order_of_key(-2)) << "\n";
    return 0;
}