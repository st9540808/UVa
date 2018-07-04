#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <string>
#include <cmath>

#define TOSTRING(val) ({ \
    char buf[30]; std::sprintf(buf, "%.1f", val); std::string s(buf); s; \
})
#define TOSTRING2(val) ({ \
    char buf[30]; std::sprintf(buf, "%.2f", val); std::string s(buf); s; \
})

struct point {
    double x, y;
    bool operator<(const point& p) const {
        return this->x < p.x || (this->x == p.x && this->y < p.y);
    }
};

struct convex_hull {
    std::vector<point> operator()(std::vector<point> P) {
        if (P.size() == 1) {
            P.push_back(P[0]);
            return P;
        } else if (P.size() < 3)
            return P;

        size_t n = P.size(), k = 0;
        std::vector<point> H(2 * n);

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

    double cross(const point& O, const point& A, const point& B) {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }
};

int main(int argc, char const *argv[])
{
    int n, cases = 1;
    convex_hull sol;

    while (std::cin >> n && n != 0) {
        std::vector<point> P(n), H;
        std::string convex;
        double length = 0.;

        std::for_each(P.begin(), P.end(), [](point& p) {
            std::cin >> p.x >> p.y;
        });

        H = std::move(sol(P));
        convex = std::accumulate(
            std::next(H.rbegin()), H.rend(),
            '(' + TOSTRING(H.rbegin()->x) + ',' + TOSTRING(H.rbegin()->y) + ')',
            [](std::string str, const point& p) {
                return str + '-' + '(' + TOSTRING(p.x) + ',' + TOSTRING(p.y) + ')';
            }
        );

        for (size_t i = 1; i < H.size(); i++) {
            length += std::sqrt( 
                std::pow(H[i].x - H[i-1].x, 2) + std::pow(H[i].y - H[i-1].y, 2)
            );
        }

        if (cases > 1) std::cout << '\n';
        std::cout << "Region #" << cases++ << ":\n";
        std::cout << convex << '\n';
        std::cout << "Perimeter length = " << TOSTRING2(length) << '\n';
    }

    return 0;
}
