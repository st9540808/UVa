#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

int dfn[20000];
int low[20000];
int val[20000];
int t;
std::vector<std::vector<int>> graph;
std::vector<std::pair<int, int>> ans;

void dfs(int prev, int cur)
{
    low[cur] = dfn[cur] = ++t;
    val[cur] = 1;
    
    for (int v : graph[cur]) {
        if (!dfn[v]) { // tree edge
            dfs(cur, v);
            low[cur] = std::min(low[cur], low[v]);
            if (low[v] >= dfn[cur])
                val[cur]++;
        } else if (v != prev) // back edge
            low[cur] = std::min(low[cur], dfn[v]);
    }
}

int main(void)
{
    int n, m, u, v;
    
    while (std::cin >> n >> m && n != 0 && m != 0) {
        graph.resize(n);
        t = 0;
        
        while (std::cin >> u >> v && u != -1 && v != -1) {
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        dfs(0, 0);
        val[0]--;
        
        for (int i = 0; i < n; i++)
            ans.push_back(std::make_pair(i, val[i]));

        std::sort(ans.begin(), ans.end(),
            [](std::pair<int, int>& left, std::pair<int, int>& right) {
                if (left.second > right.second) return true;
	            if (left.second == right.second && left.first < right.first)
		            return true;
	            return false;
            }
        );

        for (int i = 0; i < m; i++)
            std::cout << ans[i].first << ' ' << ans[i].second << std::endl;
        std::cout << std::endl;
        
        std::for_each(graph.begin(), graph.end(),
            [](std::vector<int>& v) { v.clear(); }
        );

        ans.clear();
        std::memset(dfn, 0, sizeof dfn);
        std::memset(low, 0, sizeof low);
    }

    return 0;
}