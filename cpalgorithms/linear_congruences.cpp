#include "init.h"

// Equation: ax + by = gcd(a, b).
// Assume the return result is (x0, y0), the solution family is (x_0+kb/d,y_0-ka/d) for k in Z.
// Equation ax + by = d has a solution iff d is divisible by gcd(a, b).
// ax + by = gcd(a, b)
llint ext_gcd(llint a, llint b, llint &x, llint &y) {
    llint g = a; x = 1; y = 0;
    if (b != 0) g = ext_gcd(b, a % b, y, x), y -= (a / b) * x;
    return g;
}

// https://open.kattis.com/problems/generalchineseremainder
// Solve linear congruences equation:
// - a[i] * x = b[i] MOD m[i] (mi don't need to be co-prime)
bool linearCongruences(const vector<llint> &a, const vector<llint> &b,
                       const vector<llint> &m, llint &x, llint &M) {
    llint n = a.size();
    x = 0; M = 1;
    for (int i = 0; i < n; ++i) {
        llint a_ = a[i] * M, b_ = b[i] - a[i] * x, m_ = m[i];
        llint y, t, g = ext_gcd(a_, m_, y, t);
        if (b_ % g) return false;
        b_ /= g; m_ /= g;
        x += M * (y * b_ % m_);
        M *= m_;
    }
    x = (x + M) % M;
    return true;
}
