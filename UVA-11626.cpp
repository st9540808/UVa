#include <cstdio>
#include <algorithm>
#include <cstring>

struct point {
    long long x, y;
    bool operator<(const point& p) const {
        return this->x < p.x || (this->x == p.x && this->y < p.y);
    }
    bool operator==(const point& p) const {
        return this->x == p.x && this->y == p.y;
    }
} H[120000], P[120000];

struct convex_hull {
    void operator()(int num) {
        int k = 0, n = num;

        std::sort(P, P + n);
        for (int i = 0; i < n; i++) {
            while (k >= 2 && cross(H[k-2], H[k-1], P[i]) < 0) k--;
            H[k++] = P[i];
        }

        for (int i = n-2, t = k+1; i >= 0; i--) {
            while (k >= t && cross(H[k-2], H[k-1], P[i]) < 0) k--;
            H[k++] = P[i];
        }
    }

    long long cross(const point& O, const point& A, const point& B) {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }
};


int main(int argc, char const *argv[])
{
    int cases, n, cnt;
    char buf[50], *token, xBuf[20], yBuf[20];
    convex_hull sol;

    std::scanf("%d", &cases);
    while (cases--) {
        cnt = 0;
        
        std::scanf("%d ", &n);
        for (int i = 0; i < n; i++) {
            std::fgets(buf, sizeof(buf), stdin);
            
            std::strcpy(xBuf, std::strtok(buf,  " \n"));
            std::strcpy(yBuf, std::strtok(NULL, " \n"));

            if (std::strtok(NULL, " \n")[0] == 'Y') {
                P[cnt].x = std::atoll(xBuf);
                P[cnt].y = std::atoll(yBuf);
                cnt++;
            }
        }

        sol(cnt);
        std::printf("%d\n", cnt);
        for (int i = 0; i < cnt; i++)
            std::printf("%lld %lld\n", H[i].x, H[i].y);
    }

    return 0;
}
