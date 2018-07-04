#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define eps 1e-8

struct point {
    double x, y;
    point operator-(const point& rhs) {
        return { this->x - rhs.x, this->y - rhs.y };
    }
    bool operator<(const point& p) const {
        return this->x < p.x || (this->x == p.x && this->y < p.y);
    }
};

int M, C;
point ptsMajestix[1000], convexMajestix[2000];
point ptsCleverdix[1000], convexCleverdix[2000];

struct convex_hull {
    double cross(point O, point A, point B) {
        return (A.x-O.x) * (B.y-O.y) - (A.y-O.y) * (B.x-O.x);
    }
    bool inside(point pts[], point q, int n) {
        int k = 0;
        if (n == 1) return false;
        else if (n == 2) {
            if (pts[0].x > q.x != pts[1].x > q.x && pts[0].y > q.y != pts[1].y > q.y &&
                std::fabs(cross(pts[0], pts[1], q)) < eps)
                return true;
            return false;
        }
        for (int i = 0, j = n-1; i < n; j = i++) {
            if (pts[i].y > q.y != pts[j].y > q.y &&
                q.x < (pts[j].x-pts[i].x)*(q.y-pts[i].y) / (pts[j].y-pts[i].y) + pts[i].x)
                k++;
        }
        return k % 2;
    }

    int andrewMonotone(point p[], int n, point ch[]) {
        std::sort(p, p+n);
        int k = 0, t;
        for (int i = 0; i < n; i++) {
            while (k >= 2 && cross(ch[k-2], ch[k-1], p[i]) <= 0) k--;
            ch[k++] = p[i];
        }
        for (int i = n-1, t = k+1; i >= 0; i--) {
            while(k >= t && cross(ch[m-2], ch[m-1], p[i]) <= 0) k--;
            ch[k++] = p[i];
        }
        return k-1;
    }
    bool intersection(point p1, point p2, point p3, point p4) {
        double d1, d2, d3, d4;
        d1 = cross(p3, p4, p1);
        d2 = cross(p3, p4, p2);
        d3 = cross(p1, p2, p3);
        d4 = cross(p1, p2, p4);
        if (std::signbit(d1) != std::signbit(d2) &&
            std::signbit(d3) != std::signbit(d4))
            return true;
        return false;
    }
    void operator()() {
        int Mn = andrewMonotone(ptsMajestix, M, convexMajestix),
            Cn = andrewMonotone(ptsCleverdix, C, convexCleverdix);

        for (int i = 0; i < Cn; i++) {
            if (inside(convexMajestix, convexCleverdix[i], Mn)) {
                std::puts("No");
                return;
            }
        }

        for (int i = 0; i < Mn; i++) {
            if (inside(convexCleverdix, convexMajestix[i], Cn)) {
                std::puts("No");
                return;
            }
        }

        for (int i = 0, j = Mn-1; i < Mn; j = i++) {
            for (int k = 0, l = Cn-1; k < Cn; l = k++) {
                if (intersection(convexMajestix[i], convexMajestix[j], convexCleverdix[k], convexCleverdix[l])) {
                    std::puts("No");
                    return;
                }
            }
        }
        std::puts("Yes");
    }
};

int main() {
    convex_hull sol;

    while (std::scanf("%d %d", &M, &C) == 2 && M) {
        for (int i = 0; i < M; i++)
            std::scanf("%lf %lf", &ptsMajestix[i].x, &ptsMajestix[i].y);
        for (int i = 0; i < C; i++)
            std::scanf("%lf %lf", &ptsCleverdix[i].x, &ptsCleverdix[i].y);
        sol.operator()();
    }
    return 0;
}
