#include <iostream>
#include <map>
#include <string>
#include <utility>

struct DisjointSets {
    int size;
    int max_group_size;
    std::map<std::string, std::string> p;
    std::map<std::string, int> group_size;

    DisjointSets(int size) : size(size), max_group_size(1) {}
    void add(const std::string& str) {
        p.insert(std::make_pair(str, str));
        group_size.insert(std::make_pair(str, 1));
    }

    void Union(std::string x, std::string y) {
        std::string X = Find(x), Y = Find(y);
        if (X != Y) {
            int sum = group_size[X] + group_size[Y];
            p[X] = Y;
            
            if (sum > max_group_size) max_group_size = sum;
            group_size[X] = group_size[Y] = sum;
        }
    }

    std::string Find(std::string str) {
        if (str != p[str]) {
            std::string s = Find(p[str]);
            p[str] = s;
            group_size[str] = group_size[s];
        }
        return p[str];
    }
};

int main(void)
{
    int C, R;

    while (std::cin >> C >> R && !(C == 0 && R == 0)) {
        DisjointSets set(C);

        for (int i = 0; i < C; i++) {
            std::string str;
            std::cin >> str;
            set.add(str);
        }

        for (int i = 0; i < R; i++) {
            std::string c1, c2;
            
            std::cin >> c1 >> c2;
            set.Union(c1, c2);
        }

        std::cout << set.max_group_size << '\n';
    }

    return 0;
}