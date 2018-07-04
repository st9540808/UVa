#include <iostream>
#include <cmath>

struct point {
    int x, y;
    point operator-(const point& rhs) {
        return { this->x - rhs.x, this->y - rhs.y };
    }
    static int outer(point p1, point p2) {
        return p1.x * p2.y - p1.y * p2.x;
    }
};

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
    int n, left, top, right, bottom;
    point start, end;
    intersect sol;
    
    std::cin >> n;
    while (n--) {
        std::cin >> start.x >> start.y >> end.x >> end.y
                 >> left >> top >> right >> bottom;

        if (left > right) std::swap(left, right);
        if (bottom > top) std::swap(bottom, top);
        
        if (sol({left, top}, {right, top}, start, end) ||
            sol({right, top}, {right, bottom}, start, end) ||
            sol({right, bottom}, {left, bottom}, start, end) ||
            sol({left, bottom}, {left, top}, start, end) ||
            left <= start.x && start.x <= right && left <= end.x && end.x <= right &&
            bottom <= start.y && start.y <= top && bottom <= end.y && end.y <= top)
            std::cout << "T\n";
        else
            std::cout << "F\n";
    }

    return 0;
}
