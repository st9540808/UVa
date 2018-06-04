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
    int n, m, s, v;

    while (std::cin >> n >> m >> s >> v) {
        bipartite sol(n, m);
        struct { double x, y; } gopher[n + 1], hole[m + 1];

        for (int i = 1; i <= n; i++)
            std::cin >> gopher[i].x >> gopher[i].y;
        for (int i = 1; i <= m; i++)
            std::cin >> hole[i].x >> hole[i].y;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                double distance = std::sqrt(
                    std::pow(gopher[i].x - hole[j].x, 2) +
                    std::pow(gopher[i].y - hole[j].y, 2)
                );
                if (distance / v <= s)
                    sol.edge[i][j] = true;
                else
                    sol.edge[i][j] = false;
            }
        }

        std::cout << n - sol() << '\n';
    }

    return 0;
}
