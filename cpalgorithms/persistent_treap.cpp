#include "init.h"

// Time Complexity: Avg. O(logN)
// Non-persistent Treap is 50% faster
// All queries can be put in update()
// AVOID TOO MANY calls to merge, split
namespace Treap {
    struct Treap {
        llint x;
        int y, s = 1;
        Treap *l = nullptr, *r = nullptr;

        explicit Treap(llint _x) : x(_x), y(rand()) {}
    };

    int size(Treap *t) {
        return (!t) ? 0 : t->s;
    }

    void update(Treap *t) {
        t->s = 1 + size(t->l) + size(t->r);
    }

    Treap *merge(Treap *l, Treap *r) {
        if (!l) return r;
        if (!r) return l;
        Treap *t = nullptr;
        if (l->y < r->y) {
            t = new Treap(*l); // t = l non-persistent
            t->r = merge(l->r, r);
        } else {
            t = new Treap(*r); // t = r non-per
            t->l = merge(l, r->l);
        }
        update(t);
        return t;
    }

    pair<Treap *, Treap *> split(Treap *a, int n) {
        if (!a) return {nullptr, nullptr};
        int s = size(a->l) + 1;
        Treap *t = new Treap(*a); // t = a non-per
        pair<Treap *, Treap *> p;
        if (s <= n) {
            p = split(t->r, n - s);
            t->r = p.first;
            p.first = t;
        } else {
            p = split(t->l, n);
            t->l = p.second;
            p.second = t;
        }
        update(t);
        return p;
    }
}