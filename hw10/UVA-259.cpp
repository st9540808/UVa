#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

struct bipartite {
    int n, m;
    std::vector<int> llink;
    std::vector<int> rlink;
    std::vector<std::vector<bool>> edge;

    bipartite(int n, int m)
        : n(n), m(m)
        , llink(n + 1, 0), rlink(m + 1, 0)
        , edge(n + 1, std::vector<bool>(m + 1, false))
    {}

    int operator()() {
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            std::vector<bool> used(m + 1, false);
            if (dfs(i, used)) ans++;
        }
        return ans;
    }

    bool dfs(int now, std::vector<bool>& used) {
        for (int nxt = 1; nxt <= m; nxt++) {
            if (!used[nxt] && edge[now][nxt]) {
                used[nxt] = true;
                if (!rlink[nxt] || dfs(rlink[nxt], used)) {
                    llink[now] = nxt;
                    rlink[nxt] = now;
                    return true;
                }
            }
        }
        return false;
    }
};


int main(int argc, char const *argv[])
{
    std::string line;
    int app, numUsers;
    struct pair { int required, cur; };

    while (!std::cin.eof()) {
        bipartite sol(10, 270);
        std::map<char, pair> config;
        std::string ans;

        while (std::getline(std::cin, line) && !line.empty()) {
            std::vector<int> machines;

            app = line[0] - 'A' + 1;
            config[app].required = numUsers = line[1] - '0';
            config[app].cur = 0;

            for (int i = 3; line[i] != ';'; i++)
                machines.push_back(line[i] - '0' + 1);
            for (int m : machines) {
                for (int i = 0; i < numUsers; i++)
                    sol.edge[m][app * 10 + i] = true;
            }
        }

        sol();

        for (int i = 1; i <= 10; i++) {
            if (sol.llink[i] != 0)
                config[sol.llink[i] / 10].cur++;
        }

        if (std::find_if(config.begin(), config.end(),
            [](const std::pair<const char, pair> p)
                { return p.second.cur < p.second.required; }) != config.end()) {
            ans = "!";
        } else {
            for (int i = 1; i <= 10; i++) {
                ans.push_back(
                    sol.llink[i] != 0 ?
                    static_cast<char>(sol.llink[i] / 10 + 'A' - 1) :
                    '_'
                );
            }
        }

        std::cout << ans << '\n';
    }

    return 0;
}
