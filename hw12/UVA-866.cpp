#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

struct point {
    int x, y;
    point operator-(const point& rhs) {
        return { this->x - rhs.x, this->y - rhs.y };
    }
    static int cross(point p1, point p2) {
        return p1.x * p2.y - p1.y * p2.x;
    }
};
struct segment { point s, t; };

struct intersect {
    bool operator()(point p1, point p2, point p3, point p4) {
        int d1 = direction(p3, p4, p1);
        int d2 = direction(p3, p4, p2);
        int d3 = direction(p1, p2, p3);
        int d4 = direction(p1, p2, p4);
        if (std::signbit(d1) != std::signbit(d2) &&
            std::signbit(d3) != std::signbit(d4))
            return true;
        else if (d1 == 0 && onSegement(p3, p4, p1))
            return true;
        else if (d2 == 0 && onSegement(p3, p4, p2))
            return true;
        else if (d3 == 0 && onSegement(p1, p2, p3))
            return true;
        else if (d4 == 0 && onSegement(p1, p2, p4))
            return true;
        return false;
    }
    int inline direction(point pi, point pj, point pk) {
        return point::cross(pk - pi, pj - pi);
    }
    bool onSegement(point pi, point pj, point pk) {
        if ((std::min(pi.x, pj.x) <= pk.x && pk.x <= std::max(pi.x, pj.x)) &&
            (std::min(pi.y, pj.y) <= pk.y && pk.y <= std::max(pi.y, pj.y)))
            return true;
        return false;
    }
};


int main(int argc, char const *argv[])
{
    int cases, n;
    std::vector<segment> segs;
    intersect sol;

    for (std::cin >> cases; cases--;) {
        int ans;
        std::cin >> n;
        segs.resize(n);
        for (segment& seg : segs)
            std::cin >> seg.s.x >> seg.s.y >> seg.t.x >> seg.t.y;

        ans = n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && sol(segs[i].s, segs[i].t, segs[j].s, segs[j].t))
                    ans++;
            }
        }

        std::cout << ans << '\n';
        if (cases > 0) std::cout << '\n';
    }

    return 0;
}
