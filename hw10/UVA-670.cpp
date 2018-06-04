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
    int K, n, m;
    std::vector<int> lx, ly, rx, ry;

    std::cin >> K;
    while (K--) {
        std::cin >> n >> m;
        bipartite sol(n, m);
        
        lx.resize(n + 1); ly.resize(n + 1);
        rx.resize(m + 1); ry.resize(m + 1);

        for (int i = 1; i <= n; i++)
            std::cin >> lx[i] >> ly[i];
        for (int i = 1; i <= m; i++)
            std::cin >> rx[i] >> ry[i];
        
        for (int i = 1; i < n; i++) {
            double len = 2 * std::sqrt(
                std::pow(lx[i] - lx[i+1], 2) + std::pow(ly[i] - ly[i+1], 2)
            );

            for (int j = 1; j <= m; j++) {
                double len1 = std::sqrt(
                    std::pow(lx[i] - rx[j], 2) + std::pow(ly[i] - ry[j] , 2)
                );
                double len2 = std::sqrt(
                    std::pow(lx[i+1] - rx[j], 2) + std::pow(ly[i+1] - ry[j], 2)
                );

                if (len1 + len2 <= len)
                    sol.edge[i][j] = true;
            }
        }

        std::cout << n + sol() << '\n';
        for (int i = 1; i < n; i++) {
            std::cout << lx[i] << ' ' << ly[i];
            
            if (sol.llink[i] != 0)
                std::cout << ' ' << rx[sol.llink[i]] << ' ' << ry[sol.llink[i]];
            if (i != n - 1) std::cout << ' ';
        }
        std::cout << ' ' << lx[n] << ' ' << ly[n] << '\n';

        if (K != 0) std::cout << '\n';
    }

    return 0;
}
