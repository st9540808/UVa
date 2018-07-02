#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

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

        if (n == 1) {
            P.push_back(P[0]);
            return P;
        } else if (n < 3)
            return P;

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
    int n;
    double ans;
    point target;
    std::vector<point> pts;
    std::vector<std::vector<point>> convexs;
    convex_hull sol;

    while (std::cin >> n && n != -1) {
        pts.resize(n);
        for (int i = 0; i < n; i++)
            std::cin >> pts[i].x >> pts[i].y;
        
        convexs.push_back(sol(pts));
    }

    while (std::cin >> target.x >> target.y) {
        for (int i = 0; i < convexs.size(); i++) {
            if (sol.inside(convexs[i], target)) {
                ans += sol.area(convexs[i]);
                convexs.erase(convexs.begin()+i);
                break;
            }
        }
    }

    std::cout << std::fixed << std::setprecision(2) << ans << '\n';
    return 0;
}
