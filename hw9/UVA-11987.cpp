#include <iostream>
#include <vector>
#include <unordered_set>
#include <utility>
#include <numeric>

struct DisjointSets {
    int p[100001];
    std::vector<std::unordered_set<int>> sets;

    DisjointSets() : sets(100001) {}

    void init(int size) {
        for (int i = 1; i <= size; i++) {
            p[i] = i;
            sets[i].clear();
            sets[i].insert(i);
        }
    }

    void Union(int x, int y) {
        int X = p[x], Y = p[y];
        if (X == Y) return;

        if (sets[X].size() >= sets[Y].size()) {
            for (int e : sets[Y]) {
                sets[X].insert(e);
                p[e] = X;
            }
            sets[Y].clear();
        } else {
            for (int e : sets[X]) {
                sets[Y].insert(e);
                p[e] = Y;
            }
            sets[X].clear();
        }
    }

    void Move(int x, int y) {
        int X = p[x], Y = p[y];
        if (X == Y) return;

        p[x] = Y;
        sets[Y].insert(x);
        sets[X].erase(x);
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    int n, m;
    char c;
    DisjointSets set;

    while (std::cin >> n >> m) {
        set.init(n);

        for (int i = 0; i < m; i++) {
            std::string str;
            int op, p, q;

            switch (std::cin >> op, op) {
            case 1:
                std::cin >> p >> q;
                set.Union(p, q);
                break;
            case 2:
                std::cin >> p >> q;
                set.Move(p, q);
                break;
            case 3:
                std::cin >> p;
                const auto& s = set.sets[set.p[p]]; 
                std::cout << s.size() << ' ' << 
                    std::accumulate(s.begin(), s.end(), 0) << '\n';
            }
        }
    }

    return 0;
}