#include <iostream>
#include <cstdio>
#include <string>
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
    std::string line;
    std::vector<point> pts, convex;
    point p;
    convex_hull sol;
    bool first = true;

    do {
        std::getline(std::cin, line);

        if (line.length() != 0) {
            std::sscanf(line.c_str(), "%d,%d", &p.x, &p.y);
            pts.push_back(p);
        }

        if (std::cin.eof() || line.length() == 0) {
            pts.pop_back();
            convex = sol(pts);

            std::rotate(
                convex.begin(),
                convex.begin() +
                    [&]() -> int {
                        for (int i = 0; i < pts.size(); i++) {
                            for (int j = 0; j < convex.size(); j++)
                                if (convex[j] == pts[i]) return j;
                        }
                    }(),
                convex.end()
            );

            if (!first) std::cout << '\n';
            for (point &p : convex)
                std::cout << p.x << ", " << p.y << '\n';
            std::cout << convex[0].x << ", " << convex[0].y << '\n';

            first = false;
            pts.clear();
        }
    } while (!std::cin.eof());

    return 0;
}
