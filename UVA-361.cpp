#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>

struct point {
    double x, y;
    bool operator<(const point& p) const {
        return this->x < p.x || (this->x == p.x && this->y < p.y);
    }
};

struct convex_hull {
    static constexpr double eps = 1e-8;
    double cross(point O, point A, point B) {
        return (A.x-O.x) * (B.y-O.y) - (A.y-O.y) * (B.x-O.x);
    }
    bool onSegement(point a, point b, point p) {
        if (std::min(a.x, b.x)-eps <= p.x && p.x <= std::max(a.x, b.x)+eps &&
            std::min(a.y, b.y)-eps <= p.y && p.y <= std::max(a.y, b.x)+eps &&
            std::fabs(cross(a, b, p)) < eps)
            return true;
        return false;
    }
    bool inside(point p[], int n, point q) {
        int i, j, k = 0;
        
        for (i = 0, j = n-1; i < n; j = i++) {
            if (p[i].y > q.y != p[j].y > q.y &&
                q.x < (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x)
                k++;
            if (onSegement(p[i], p[j], q))
                return true;;
        }
        
        return k % 2;
    }
    int operator()(point P[], int n, point H[]) {
        int i, t, k = 0;
        
        std::sort(P, P+n);
        for (i = 0; i < n; i++) {
            while(k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
            H[k++] = P[i];
        }

        for (i = n-1, t = k+1; i >= 0; i--) {
            while(k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
            H[k++] = P[i];
        }

        return k-1;
    }
};

int main(int argc, char const *argv[])
{
    int c, r, o, cCH, rCH, cases = 1;
    typedef point cords_t[500];
    cords_t cops, robbers, citizens;
    cords_t copsCH, robbersCH;
    convex_hull sol;

    while (std::cin >> c >> r >> o && (c != 0 || r != 0 || o != 0)) {
        for (int i = 0; i < c; i++)
            std::cin >> cops[i].x >> cops[i].y;
        for (int i = 0; i < r; i++)
            std::cin >> robbers[i].x >> robbers[i].y;
        for (int i = 0; i < o; i++)
            std::cin >> citizens[i].x >> citizens[i].y;

        cCH = sol(cops, c, copsCH);
        rCH = sol(robbers, r, robbersCH);

        std::printf("Data set %d:\n", cases++);
        for (int i = 0; i < o; i++) {
            bool safe = false, robbed = false;
            
            if (sol.inside(copsCH, cCH, citizens[i]) && c >= 3)
                safe = true;
            else if (sol.inside(robbersCH, rCH, citizens[i]) && r >= 3)
                robbed = true;
            std::printf("     Citizen at (%.0lf,%.0lf) is %s.\n",
                        citizens[i].x, citizens[i].y,
                        safe ? "safe" : robbed ? "robbed" : "neither");
        }
        std::puts("");
    }

    return 0;
}
