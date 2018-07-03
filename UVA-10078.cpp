#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct point {
    int x, y;
    bool operator<(const point& p) const {
        return this->x < p.x || (this->x == p.x && this->y < p.y);
    }
    bool operator==(const point& p) const {
        return this->x == p.x && this->y == p.y;
    }
};

struct orientation {
    bool operator()(std::vector<point> P) {
        int n = P.size();
        P.push_back(P[0]);
        P.push_back(P[1]);

        if (cross(P[0], P[1], P[2]) >= 0) {
            for (int i = 0; i < n; i++) {
                if (cross(P[i], P[i+1], P[i+2]) < 0)
                    return false;
            }
        } else {
            for (int i = 0; i < n; i++) {
                if (cross(P[i], P[i+1], P[i+2]) > 0)
                    return false;
            }
        }
        return true;
    }

    int cross(const point& O, const point& A, const point& B) {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }
};


int main(int argc, char const *argv[])
{
    int n;
    std::vector<point> pts, convex;
    orientation sol;

    while (std::cin >> n && n != 0) {
        pts.resize(n);
        for (point& p : pts)
            std::cin >> p.x >> p.y;

        std::cout << (sol(pts) ? "No\n" : "Yes\n");
    }

    return 0;
}
