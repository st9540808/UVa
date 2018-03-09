#include <iostream>
#include <map>
#include <string>
#include <sstream>

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
        p[Find(x)] = Find(y);
    }

    int Find(int x) {
        if (x != p[x]) p[x] = Find(p[x]);
        return p[x];
    }
};

int main(void)
{
    int cases;
    std::string str;
    std::cin >> cases;
    
    for (int i = 0; i < cases; i++) {
        int nSuccess = 0, nUnsucess = 0;
        int n, c1, c2;
        char c;
        
        std::cin >> n;
        while (std::cin.get(c) && c != '\n') ;

        DisjointSets set(n);
        while (std::getline(std::cin, str) && str.length() != 0) {
            std::stringstream ss(str);
            ss >> c >> c1 >> c2;
           
            if (c == 'c')
               set.Union(c1, c2);
            else {
                if (set.Find(c1) == set.Find(c2))
                    nSuccess++;
                else
                    nUnsucess++;
            }
        }

        std::cout << nSuccess << ',' << nUnsucess << '\n';
        if (i != cases - 1) std::cout << '\n';
    }
    return 0;
}