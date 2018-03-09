#include <iostream>
#include <map>

struct DisjointSets {
    int size;
    std::map<int, int> p;
    std::map<int, int> rank;

    DisjointSets(int size) : size(size) {
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

int main(void)
{
    int n, m, cases = 1;
    int stu1, stu2;
    
    while (std::cin >> n >> m && n != 0 && m != 0) {
        DisjointSets set(n);

        for (int i = 0; i < m; i++) {
            std::cin >> stu1 >> stu2;
            set.Union(stu1, stu2);
        }

        std::cout << "Case " << cases++ << ": " << set.size << '\n';
    }

    return 0;
}