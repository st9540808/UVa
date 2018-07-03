#include <iostream>
#include <vector>
#include <cmath>

struct DisjointSets {
    int size;
    std::vector<int> p, rank;

    DisjointSets(int size)
        : size(size)
        , p(this->size), rank(this->size) {
        for (int i = 0; i < size; i++) {
            p[i] = i;
            rank[i] = 0;
        }
    }

    void Union(int x, int y) {
        int X = Find(x), Y = Find(y);
        if (X != Y) {
            size--;
            Link(X, Y);
        }
    }

    void Link(int x, int y) {
        if (rank[x] > rank[y])
            p[y] = x;
        else {
            p[x] = y;
            if (rank[x] == rank[y]) rank[y]++;
        }
    }

    int Find(int x) {
        if (x != p[x]) p[x] = Find(p[x]);
        return p[x];
    }
};

struct point {
    int x, y;
    point operator-(const point& rhs) {
        return { this->x - rhs.x, this->y - rhs.y };
    }
    static int outer(point p1, point p2) {
        return p1.x * p2.y - p1.y * p2.x;
    }
};
struct segment { point s, t; };

struct intersect {
    bool operator()(point p1, point p2, point p3, point p4) {
        int d1 = direction(p3, p4, p1);
        int d2 = direction(p3, p4, p2);
        int d3 = direction(p1, p2, p3);
        int d4 = direction(p1, p2, p4);
        if (std::signbit(d1) != std::signbit(d2) &&
            std::signbit(d3) != std::signbit(d4))
            return true;
        else if (d1 == 0 && onSegement(p3, p4, p1))
            return true;
        else if (d2 == 0 && onSegement(p3, p4, p2))
            return true;
        else if (d3 == 0 && onSegement(p1, p2, p3))
            return true;
        else if (d4 == 0 && onSegement(p1, p2, p4))
            return true;
        return false;
    }
    int inline direction(point pi, point pj, point pk) {
        return point::outer(pk - pi, pj - pi);
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
    int cases, n, x, y;
    std::vector<segment> segs;
    intersect sol;

    for (std::cin >> cases; cases--;) {
        DisjointSets set(({std::cin >> n; n+1;}));
        segs.resize(n+1);
       
        for (int i = 1; i <= n; i++)
            std::cin >> segs[i].s.x >> segs[i].s.y >> segs[i].t.x >> segs[i].t.y;

        for (int i = 1; i < n; i++) {
            for (int j = i+1; j <= n; j++) {
                if (sol(segs[i].s, segs[i].t, segs[j].s, segs[j].t))
                    set.Union(i, j);
            }
        }

        while (std::cin >> x >> y && (x != 0 && y != 0)) {
            std::cout << (set.Find(x) == set.Find(y) ?
                          "CONNECTED" : "NOT CONNECTED") << '\n';
        }
        if (cases > 0) std::cout << '\n';
    }

    return 0;
}
