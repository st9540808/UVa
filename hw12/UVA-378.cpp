#include <iostream>
#include <utility>
#include <cmath>
#include <iomanip>

struct point {
    double x, y;
    point operator-(const point& rhs) {
        return { this->x - rhs.x, this->y - rhs.y };
    }
    static double cross(point p1, point p2) {
        return p1.x * p2.y - p1.y * p2.x;
    }
};
struct segment { point s, t; };
using vec = point;

struct karmer {
    // double getc(segment seg) {
    //     if (seg.t.y == seg.s.y) return seg.t.y;
    //     else if (seg.t.x == seg.s.x) return seg.t.x;
    //     return (seg.t.y-seg.s.y)/(seg.t.x-seg.s.x);
    // }
    point operator()(segment s1, segment s2) {
        double A1 = s1.s.y-s1.t.y, B1 = s1.s.x-s1.t.x, C1 = A1*s1.s.x-B1*s1.s.y;
	    double A2 = s2.s.y-s2.t.y, B2 = s2.s.x-s2.t.x, C2 = A2*s2.s.x-B2*s2.s.y;
	    double x = (C1*B2-C2*B1)/(A1*B2-A2*B1);
	    double y = (C1*A2-C2*A1)/(A1*B2-A2*B1);
        return {x, y};
    }
};


int main(int argc, char const *argv[])
{
    int n;
    segment s1, s2;
    karmer sol;

    std::cout << "INTERSECTING LINES OUTPUT\n";
    for (std::cin >> n; n--;) {
        std::cin >> s1.s.x >> s1.s.y >> s1.t.x >> s1.t.y
                 >> s2.s.x >> s2.s.y >> s2.t.x >> s2.t.y;

        if (vec::cross(s1.t - s1.s, s2.t - s2.s) == 0 &&
            vec::cross(s1.t - s1.s, s2.t - s1.s) == 0)
            std::cout << "LINE\n";
        else if (vec::cross(s1.t - s1.s, s2.t - s2.s) == 0)
            std::cout << "NONE\n";
        else {
            point intersect = sol(s1, s2);
            std::cout << "POINT " << std::fixed << std::setprecision(2)
                      << intersect.x << " " << intersect.y << '\n';
        }
    }
    std::cout << "END OF OUTPUT\n";

    return 0;
}
