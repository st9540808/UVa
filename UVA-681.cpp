#include <iostream>
#include <vector>
#include <algorithm>

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
};


int main(int argc, char const *argv[])
{
    int K, N, delimiter;
    std::vector<point> pts, convex;
    convex_hull sol;

    std::cin >> K;
    std::cout << K << '\n';
    while (K--) {
        std::cin >> N;

        pts.resize(N);
        for (point& p : pts)
            std::cin >> p.x >> p.y;
        std::cin >> delimiter;

        convex = sol(pts);
        std::rotate(
            convex.begin(),
            std::min_element(convex.begin(), convex.end(),
                [](point& lhs, point& rhs) {
                    return lhs.y <  rhs.y ? true :
                           lhs.y == rhs.y && lhs.x < rhs.x ? true : false;
                }
            ), convex.end()
        );
        convex.push_back(convex[0]);

        std::cout << convex.size() << '\n';
        for (const point& p : convex)
            std::cout << p.x << ' ' << p.y << '\n';
        if (K > 0) std::cout << "-1\n";
    }

    return 0;
}
