#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstring>

int dfn[20000];
int low[20000];
int t;
std::vector<std::vector<int>> graph;
std::vector<std::pair<int, int>> ans;

void dfs(int cur, int prev)
{
    static const auto make = [](int u, int v) {
        if (u > v) return std::pair<int, int>{v, u};
        else return std::pair<int, int>{u, v};
    };

    low[cur] = dfn[cur] = ++t;
    
    for (int v : graph[cur]) {
        if (!dfn[v]) { // tree edge
            dfs(v, cur);
            low[cur] = std::min(low[cur], low[v]);
            if (low[v] > dfn[cur])
                ans.push_back(make(cur, v));
        } else if (v != prev) // back edge
            low[cur] = std::min(low[cur], dfn[v]);
    }
}

int main(void)
{
    int N, u, num;

    while (std::scanf(" %d", &N) != EOF) {
        t = 0;
        graph.resize(N);

        for (int i = 0; i < N; i++) {
            std::scanf(" %d (%d)", &u, &num);
            graph[u].resize(num);
            std::for_each(graph[u].begin(), graph[u].end(), [](int &v) {
                int _t;
                std::scanf(" %d", &_t);
                v = _t;
            });
        }

        // for (int i = 0; i < graph.size(); i++) {
        //     std::cout << i << ": ";
        //     for (int j = 0; j < graph[i].size(); j++)
        //         std::cout << graph[i][j] << ' ';
        //     std::cout << '\n';
        // }

        for (int i = 0; i < N; i++)
            if (!dfn[i]) dfs(i, i);
        std::sort(ans.begin(), ans.end());

        std::cout << ans.size() << " critical links\n";
        for (auto a : ans)
            std::cout << a.first << " - " << a.second << '\n';
        std::cout << '\n';

        ans.clear();
        std::memset(dfn, 0, sizeof dfn);
    }

    return 0;
}