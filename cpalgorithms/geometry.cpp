#include "init.h"

namespace Geometry2D {
    bool equals(double a, double b) { return fabs(a - b) < EPS; }
    double square(double a) { return a * a; }

    struct Point {
        double x, y;

        Point(double X = 0, double Y = 0) {
            x = X, y = Y;
        }

        Point operator+(const Point &o) const {
            return Point(x + o.x, y + o.y);
        }

        Point operator-(const Point &o) const {
            return Point(x - o.x, y - o.y);
        }

        double operator*(const Point &o) const {
            return (x * o.x + y * o.y);
        }

        double operator^(const Point &o) const {
            return (x * o.y - y * o.x);
        }

        Point operator*(double n) const {
            return Point(x * n, y * n);
        }

        Point operator/(double n) const {
            return Point(x / n, y / n);
        }

        Point rot(double ang) const {// rotate around the origin
            return Point(x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang));
        }

        Point rot(const Point &o, double ang) const {// rotate around a point
            Point p = *this - o;
            return p.rot(ang) + o;
        }

        bool operator==(const Point &o) const {
            return fabs(x - o.x) < EPS && fabs(y - o.y) < EPS;
        }

        bool operator!=(const Point &o) const {
            return fabs(x - o.x) > EPS || fabs(y - o.y) > EPS;
        }

        double abs() const {
            return hypot(x, y);
        }
    };

    int ccw(const Point &a, const Point &b, const Point &c) {// is counter clockwise
        double res = (b - a) ^(c - a);
        return fabs(res) < EPS ? 0 : res < 0 ? -1 : 1;
    }

    Point intersection(const Point &a, const Point &b, const Point &c, const Point &d) {
        // the point that 2 segment intersects
        double n = (d - c) ^(a - c);
        double m = (d - c) ^(b - c);
        return (a * m - b * n) / (m - n);
    }

    Point incenter(const Point &A, const Point &B, const Point &C) {
        // intersection of 3 edge bisectors
        double a = (B - C).abs(), b = (C - A).abs(), c = (A - B).abs();
        return (A * a + B * b + C * c) / (a + b + c);
    }

    struct LineE {
        double a, b, c;

        LineE(const Point &A, const Point &B) {
            Point u = B - A;
            a = u.y, b = -u.x;
            c = -(a * A.x + b * A.y);
        }

        double eval(const Point &P) const {
            return a * P.x + b * P.y + c;
        }

        double distTo(const Point &P) const {
            return fabs(eval(P)) / Point(a, b).abs();
        }
    };

    struct Segment {
        Point A, B;

        Segment(const Point &_A, const Point &_B) {
            A = _A, B = _B;
        }

        bool contains(const Point &P) const {
            return equals((A - P).abs() + (B - P).abs(), (B - A).abs());
        }

        bool intersected(const Segment &o) const {
            // is two segments intersected
            return (ccw(A, B, o.A) != ccw(A, B, o.B))
                   && (ccw(A, o.A, o.B) != ccw(B, o.A, o.B));
        }

        double distTo(const Point &P) const {
            // distance to a point (from segment, not line)
            if (((A - P) * (B - A)) * ((B - P) * (B - A)) > 0) {
                return min((A - P).abs(), (B - P).abs());
            }
            return LineE(A, B).distTo(P);
        }

        double distTo(const Segment &o) const {
            return intersected(o) ? 0 :
                   min(min(distTo(o.A), distTo(o.B)), min(o.distTo(A), o.distTo(B)));
        }
    };

    double angle(Point a) {
        // angle of a vector in radian equivalent to 0..360
        double ang = acos(a * Point(1, 0) / a.abs());
        return a.y >= 0 ? ang : M_PI * 2 - ang;
    }

    vector<Point> intersection(const Point &a, double ra, const Point &b, double rb) {
        // intersection between circles
        double d = hypot(a.x - b.x, a.y - b.y);
        double l = (square(ra) - square(rb) + square(d)) / (d + d);
        double h = sqrt(square(ra) - square(l));
        vector<Point> ans;
        for (int i = 0; i < 2; ++i) {
            double x = (l * (b.x - a.x) + h * (b.y - a.y)) / d + a.x;
            double y = (l * (b.y - a.y) - h * (b.x - a.x)) / d + a.y;
            if (ans.empty() || ans.back() != Point(x, y)) ans.push_back(Point(x, y));
            h = -h;
        }
        return ans;
    }
}