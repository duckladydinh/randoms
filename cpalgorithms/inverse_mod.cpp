#include "init.h"

// 2 = 500000004, 6 = 166666668, 24 = 41666667
vector<llint> inverse_mod(llint n, llint mod) {
    vector<llint> inv(n + 1, 0);
    inv[1] = 1;
    for (int i = 2; i < min(n + 1, mod); ++i) {
        inv[i] = (mod - (mod / i) * inv[mod % i] % mod) % mod;
    }
    return inv;
}
