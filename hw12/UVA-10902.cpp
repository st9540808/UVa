#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

struct point {
    double x, y;
    point operator-(const point& rhs) {
        return { this->x - rhs.x, this->y - rhs.y };
    }
    static double outer(point p1, point p2) {
        return p1.x * p2.y - p1.y * p2.x;
    }
};
struct segment { point s, t; };

struct intersect {
    bool operator()(point p1, point p2, point p3, point p4) {
        double d1, d2, d3, d4;

        if (onSegement(p3, p4, p1) || onSegement(p3, p4, p2) ||
            onSegement(p1, p2, p3) || onSegement(p1, p2, p4))
            return true;
        
        d1 = direction(p3, p4, p1);
        d2 = direction(p3, p4, p2);
        d3 = direction(p1, p2, p3);
        d4 = direction(p1, p2, p4);
        if (std::signbit(d1) != std::signbit(d2) &&
            std::signbit(d3) != std::signbit(d4))
            return true;
        return false;
    }
    double inline direction(point pi, point pj, point pk) {
        return point::outer(pk - pi, pj - pi);
    }
    bool onSegement(point pi, point pj, point pk) {
        if ((std::min(pi.x, pj.x) <= pk.x && pk.x <= std::max(pi.x, pj.x)) &&
            (std::min(pi.y, pj.y) <= pk.y && pk.y <= std::max(pi.y, pj.y)) &&
            (pi.x - pj.x) * (pk.y - pi.y) == (pi.y - pj.y) * (pk.x - pi.x))
            return true;
        return false;
    }
};


int main(int argc, char const *argv[])
{
    int n;
    intersect sol;

    while (std::cin >> n && n != 0) {
        std::vector<segment> segs(n+1);
        std::vector<int> ans;

        std::for_each(segs.begin()+1, segs.end(), [](segment& seg) {
            std::cin >> seg.s.x >> seg.s.y >> seg.t.x >> seg.t.y;
        });

        for (int i = 1, j; i < n; i++) {
            for (j = i+1; j <= n; j++) {
                if (sol(segs[i].s, segs[i].t, segs[j].s, segs[j].t))
                    break;
            }
            if (j > n) ans.push_back(i);
        }
        std::cout << "Top sticks: ";
        if (ans.size() != 0) {
            std::cout << ans[0];
            std::for_each(ans.begin()+1, ans.end(), [](int i) {
                std::cout << ", " << i;
            });
            std::cout << ", " << n << ".\n";
        } else
            std::cout << n << ".\n";
    }
    
    return 0;
}
