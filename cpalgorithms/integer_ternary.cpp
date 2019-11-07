#include "init.h"
void ternary_search(int lo, int hi, function<llint(llint)> f) {
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (f(mid) > f(mid + 1)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
}
