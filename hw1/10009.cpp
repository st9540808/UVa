#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <utility>

struct Map {
    std::unordered_map<char, std::unordered_set<char>> cities;
    
    void add(char c1, char c2) {
        auto connect1 = cities.find(c1);
        auto connect2 = cities.find(c2);

        if (connect1 == cities.end())
            cities.emplace(c1, std::unordered_set<char> {c2});
        else
            (*connect1).second.insert(c2);

        if (connect2 == cities.end())
            cities.emplace(c2, std::unordered_set<char> {c1});
        else
            (*connect2).second.insert(c1);
    }

    std::string search(char c1, char c2) {
        std::queue<std::pair<std::string, std::unordered_set<char>>> q;
        q.emplace(std::string {c1}, std::unordered_set<char> {c1});
        
        while (!q.empty()) {
            auto path = q.front(); q.pop();
            char city = path.first.back();

            if (city == c2)
                return path.first;
            
            for (char connect : cities[city]) {
                if (path.second.find(connect) == path.second.end()) {
                    std::string new_path = path.first + std::string {connect};
                    auto s = path.second;
                    s.insert(connect);
                    q.emplace(new_path, s);
                }
            }
        }

        return "";
    }
};

int main(void)
{
    int cases, n, m;
    std::cin >> cases;

    while (cases--) {
        Map map;
        std::cin >> n >> m;
        std::cin.ignore(32, '\n');
        
        for (int i = 0; i < n; i++) {
            std::string str1, str2;
            std::cin >> str1 >> str2;
            map.add(str1[0], str2[0]);
        }

        for (int i = 0; i < m; i++) {
            std::string str1, str2;
            std::cin >> str1 >> str2;
            std::cout << map.search(str1[0], str2[0]) << '\n';
        }

        if (cases) std::cout << '\n';
    }

    return 0;
}