#include <iostream>
#include <cmath>
#include <vector>

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
    int n, m, k;

    while (std::cin >> n >> m >> k) {
        bipartite sol(n, m);
        int jobNum, x, y;

        for (int i = 0; i < k; i++) {
            std::cin >> jobNum >> x >> y;
            if (x != 0 && y != 0)
                sol.edge[x][y] = true;
        }

        std::cout << sol() << '\n';
    }
    
    return 0;
}
