#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>

struct point {
    int x, y;
    bool operator<(const point& p) const {
        return this->x < p.x || (this->x == p.x && this->y < p.y);
    }
};

struct convex_hull {
    std::vector<point> operator()(std::vector<point> P) {
        size_t k = 0, n = P.size();
        std::vector<point> H;

        H.resize(2 * n);
        std::sort(P.begin(), P.end());
        for (size_t i = 0; i < n; i++) {
            while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
            H[k++] = P[i];
        }

        for (size_t i = n-1, t = k+1; i > 0; i--) {
            while (k >= t && cross(H[k-2], H[k-1], P[i-1]) <= 0) k--;
            H[k++] = P[i-1];
        }

        H.resize(k);
        return H;
    }

    int cross(const point& O, const point& A, const point& B) {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }

    double area(const std::vector<point>& convex) {
        int a = 0;
        for (int i = 1; i < convex.size(); i++)
            a += convex[i-1].x * convex[i].y - convex[i].x * convex[i-1].y;
        return (double) a / 2.;
    }

    bool inside(const std::vector<point>& convex, point p) {
        for (int i = 1; i < convex.size(); i++) {
            if (cross(convex[i-1], convex[i], p) < 0)
                return false;
        }
        return true;
    }
};


int main(int argc, char const *argv[])
{
    int n,cases = 1;
    double areaPolygon, areaContainer;
    std::vector<point> pts, convex;
    convex_hull sol;

    while (std::cin >> n && n != 0) {
        pts.resize(n);
        for (point& p : pts)
            std::cin >> p.x >> p.y;

        convex = sol(pts);

        pts.push_back(pts[0]);
        areaPolygon = sol.area(pts);
        areaContainer = sol.area(convex);

        std::cout << "Tile #" << cases++ << '\n';
        std::cout << "Wasted Space = " << std::fixed << std::setprecision(2)
                  << (std::fabs(areaContainer) - std::fabs(areaPolygon)) /
                      std::fabs(areaContainer) * 100. << " %\n";
        std::cout << "\n";
    }

    return 0;
}
