#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

struct DisjointSets {
    int size;
    std::map<int, int> p;
    std::map<int, int> rank;

    DisjointSets(int size) : size(size) {
        for (int i = 1; i <= size; i++) {
            p[i] = i;
            rank[i] = 0;
        }
    }

    bool Union(int x, int y) {
        int X = Find(x), Y = Find(y);
        if (X != Y) {
            size--; Link(X, Y);
            return true;
        }
        return false;
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

struct edge {
    int x, y, w;
};

int main(void)
{
    int cases, N, M;
    int x[1000], y[1000];
    edge e[1000 * (1000 - 1) / 2];
    
    std::cin >> cases;
    while (cases--) {
        std::cin >> N;
        DisjointSets set(N);

        for (int i = 1; i <= N; i++)
            std::cin >> x[i] >> y[i];

        std::cin >> M;
        for (int i = 0; i < M; i++) {
            int u, v;
            std::cin >> u >> v;
            set.Union(u, v);
        }

        if (set.size == 1) {
            std::cout << "No new highways need\n";
        } else {
            int idx = 0;
            for (int i = 1; i <= N; i++) {
                for (int j = i+1; j <= N; j++) {
                    e[idx].x = i; e[idx].y = j;
                    e[idx].w = (x[i]-x[j]) * (x[i]-x[j]) + 
                               (y[i]-y[j]) * (y[i]-y[j]);
                    idx++;
                }
            }

            std::sort(std::begin(e), std::begin(e) + idx,
                [](edge& l, edge& r) { return l.w < r.w; }
            );
            for (int i = 0; i < idx; i++) {
                if (set.Union(e[i].x, e[i].y))
                    std::cout << e[i].x << ' ' << e[i].y << '\n';
            }
        }

        if (cases) std::cout << '\n';
    }

    return 0;
}