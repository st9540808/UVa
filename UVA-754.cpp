#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <algorithm>
#include <climits>

struct point {
    double x, y;
    point operator-(const point& rhs) {
        return { this->x - rhs.x, this->y - rhs.y };
    }
    bool operator==(const point& rhs) {
        return this->x == rhs.x && this->y == rhs.y;
    }
    bool operator<(const point& p) const {
        return this->x < p.x || (this->x == p.x && this->y < p.y);
    }
    static double cross(point p1, point p2) {
        return p1.x * p2.y - p1.y * p2.x;
    }
};

struct intersect {
    bool operator()(point p1, point p2, point p3, point p4) {
        double d1 = direction(p3, p4, p1), d2 = direction(p3, p4, p2),
               d3 = direction(p1, p2, p3), d4 = direction(p1, p2, p4);
        if (std::signbit(d1) != std::signbit(d2) &&
            std::signbit(d3) != std::signbit(d4))
            return true;
        return false;
    }
    double inline direction(point pi, point pj, point pk) {
        return point::cross(pk - pi, pj - pi);
    }
};


int main(int argc, char const *argv[])
{
    int cases, n, doors;
    std::array<std::vector<point>, 4> edges;
    std::array<std::array<point, 2>, 50> pts;
    point p, treasure, corners[] = {
        {0, 0}, {0, 100}, {100, 0}, {100, 100}
    };
    intersect sol;

    for (std::cin >> cases; cases--;) {
        bool visible[4] = {false};

        for (auto& edge : edges)
            edge.clear(); 
        
        std::cin >> n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2; j++) {
                std::cin >> pts[i][j].x >> pts[i][j].y;
                if (pts[i][j].x == 0)
                    edges[0].push_back(pts[i][j]);
                if (pts[i][j].x == 100)
                    edges[1].push_back(pts[i][j]);
                if (pts[i][j].y == 0)
                    edges[2].push_back(pts[i][j]);
                if (pts[i][j].y == 100)
                    edges[3].push_back(pts[i][j]);
                for (int k = 0; k < 4; k++) {
                    if (corners[k] == pts[i][j])
                        visible[k] = true;
                }
            }
        }

        std::cin >> treasure.x >> treasure.y;
        
        for (int i = 0; i < 4; i++) {
            if (!visible[i]) {
                if (corners[i].x == 0)
                    edges[0].push_back(corners[i]);
                if (corners[i].x == 100)
                    edges[1].push_back(corners[i]);
                if (corners[i].y == 0)
                    edges[2].push_back(corners[i]);
                if (corners[i].y == 100)
                    edges[3].push_back(corners[i]);
            }
        }

        for (auto& edge : edges)
            std::sort(edge.begin(), edge.end());
        
        doors = INT_MAX;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < edges[i].size()-1; j++) {
                int temp = 1;
                p = {
                    (edges[i][j].x + edges[i][j+1].x) / 2,
                    (edges[i][j].y + edges[i][j+1].y) / 2
                };

                for (int k = 0; k < n; k++) {
                    if (sol(p, treasure, pts[k][0], pts[k][1]))
                        temp++;
                }
                doors = std::min(doors, temp);
            }
        }

        std::cout << "Number of doors = " << doors << '\n';
        if (cases > 0) std::cout << '\n';
    }
    
    return 0;
}
