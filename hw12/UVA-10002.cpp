#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <utility>

struct point {
    long long x, y;
    bool operator<(const point& p) const {
        return this->x < p.x || (this->x == p.x && this->y < p.y);
    }
};

struct convex_hull {
    std::vector<point> operator()(std::vector<point> P) {
        int k = 0, n = P.size();
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

        H.resize(k);
        return H;
    }

    long long cross(const point& O, const point& A, const point& B) {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }

    std::pair<double, double> centerofmass(const std::vector<point>& convex) {
        double cmX, cmY, tmpX, tmpY, temp, area;
        auto calculate = [&convex, this](double& x, double& y, double& a, int i, int j) {
            x = (convex[0].x+convex[i].x+convex[j].x) / 3.;
            y = (convex[0].y+convex[i].y+convex[j].y) / 3.;
            a = cross(convex[0], convex[i], convex[j]) / 2.;
        };

        calculate(cmX, cmY, area, 1, 2);
        for (int i = 3; i < convex.size()-1; i++) {
            calculate(tmpX, tmpY, temp, i-1, i);
            cmX = cmX + (tmpX-cmX) * (temp) / (area+temp);
            cmY = cmY + (tmpY-cmY) * (temp) / (area+temp);
            area += temp;
        }
        return {cmX, cmY};
    }
};


int main(int argc, char const *argv[])
{
    int n;
    std::pair<double, double> cm;
    std::vector<point> pts;
    convex_hull sol;

    while (std::cin >> n && n >= 3) {
        pts.resize(n);
        for (point& p : pts)
            std::cin >> p.x >> p.y;

        cm = sol.centerofmass(sol(pts));
        std::cout << std::fixed << std::setprecision(3)
                  << cm.first << ' ' << cm.second << '\n';
    }

    return 0;
}
