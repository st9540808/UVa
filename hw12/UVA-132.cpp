#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>

struct point {
    int x, y;
    bool operator<(const point& p) const {
        return this->x < p.x || (this->x == p.x && this->y < p.y);
    }
    bool operator==(const point& p) const {
        return this->x == p.x && this->y == p.y;
    }
};

struct convex_hull {
    std::vector<point> operator()(std::vector<point> P) {
        size_t k = 0, n = P.size();
        std::vector<point> H;

        H.resize(2 * n);
        std::sort(P.begin(), P.end());
        for (int i = 0; i < n; i++) {
            while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
            H[k++] = P[i];
        }

        for (int i = n-1, t = k+1; i >= 0; i--) {
            while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
            H[k++] = P[i];
        }

        H.resize(k-1);
        return H;
    }

    int cross(const point& O, const point& A, const point& B) {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }
    int dot(const point& O, const point& A, const point& B) {
        return (A.x - O.x) * (B.x - O.x) + (A.y - O.y) * (B.y - O.y);
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
    int ans;
    point mc, p;
    std::string id;
    std::vector<point> pts, convex;
    convex_hull sol;

    while (std::cin >> id && id[0] != '#') {
        pts.clear();

        std::cin >> mc.x >> mc.y;
        while (std::cin >> p.x >> p.y) {
            if (p.x == 0 && p.y == 0) break;
            pts.push_back(p);
        }

        convex = sol(pts);

        ans = INT_MAX;
        for (int i = 0, m = convex.size(); i < m; i++) {
            if (sol.dot(convex[i], convex[(i+1) % m], mc) >= 0 &&
                sol.dot(convex[(i+1) % m], convex[i], mc) >= 0) {
                int temp = 0;
                for (int k = 0; k < pts.size(); k++) {
                    if (sol.cross(convex[i], convex[(i+1) % m], pts[k]) == 0 &&
                        sol.onSegement(convex[i], convex[(i+1) % m], pts[k]))
                        temp = std::max(k, temp);
                }
                ans = std::min(temp, ans);
            }
        }

        std::printf("%-20s%d\n", id.c_str(), ans+1);
    }

    return 0;
}
