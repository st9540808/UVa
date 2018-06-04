#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

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
    int T, n, m;
    std::vector<int> setA, setB;

    std::cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        std::cin >> n;
        setA.resize(n + 1);
        std::for_each(setA.begin() + 1, setA.end(), [](int& elem) {
            std::cin >> elem;
        });

        std::cin >> m;
        setB.resize(m + 1);
        std::for_each(setB.begin() + 1, setB.end(), [](int& elem) {
            std::cin >> elem;
        });

        bipartite sol(n, m);
        for (int i = 1; i < setA.size(); i++) {
            for (int j = 1; j < setB.size(); j++) {
                if ((setA[i] == 0 &&  setB[j] == 0) ||
                     setA[i] != 0 && (setB[j] == 0  || setB[j] % setA[i] == 0))
                    sol.edge[i][j] = true;
            }
        }

        std::cout << "Case " << cases << ": " << sol() << '\n';
    }
    
    return 0;
}
