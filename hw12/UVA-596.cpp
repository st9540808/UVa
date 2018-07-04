#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>

#define GETCORD(inputStream) ({ \
    int cord; inputStream >> cord; cord; \
})

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

        H.resize(k-1);
        return H;
    }

    int cross(const point& O, const point& A, const point& B) {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }
};


int main(int argc, char const *argv[])
{
    int numVertices;
    std::string line, id;
    std::set<point> set;
    std::vector<point> pts, convex;
    point input;
    convex_hull sol;

    std::getline(std::cin, line);
    id = line.substr(2);
    pts.clear();
    set.clear();

    while (std::getline(std::cin, line)) {
        switch (line[0]) {
        case 'P': {
            std::stringstream ss(line.substr(2));
            ss >> numVertices;
            
            for (int i = 0; i < numVertices; i++) {
                input = {GETCORD(ss), GETCORD(ss)};
                if (set.find(input) == set.end()) {
                    set.insert(input);
                    pts.push_back(input);
                }
            }
            break;
        }
        case 'E':
        case 'S': {
            convex = sol(pts);
            auto first = std::max_element(convex.begin(), convex.end(),
                [](point& lhs, point& rhs) {
                    return lhs.x < rhs.x ? true :
                           lhs.x == rhs.x && lhs.y > rhs.y ? true : false;
                }
            );

            std::rotate(convex.begin(), first, convex.end());
            std::cout << id << " convex hull:\n";
            for (const point& p : convex)
                std::cout << " (" << p.x << ',' << p.y << ')';
            std::cout << '\n';
            
            id = line.substr(2);
            pts.clear();
            set.clear();
            break;
        }
        default:
            break;
        }
    }

    return 0;
}
