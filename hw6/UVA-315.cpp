#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

int dfn[200];
int low[200];
int t;
std::vector<std::vector<int>> graph;

int dfs(int prev, int cur)
{
    int child = 0, ans = 0;
    bool cut = false;
    low[cur] = dfn[cur] = ++t;
    
    for (int v : graph[cur]) {
        if (!dfn[v]) { // tree edge
            child++;
            ans += dfs(cur, v);
            low[cur] = std::min(low[cur], low[v]);
            if (low[v] >= dfn[cur])
                cut = true;
        } else if (v != prev) // back edge
            low[cur] = std::min(low[cur], dfn[v]);
    }
    if ((child >= 2 || prev != -1) && cut)
        ans++;
    
    return ans;
}

int main(void)
{
    int N, u, v;
    
    while (std::cin >> N && N != 0) {
        std::string str;
        std::memset(dfn, 0, sizeof dfn);
        graph.resize(N + 1);
        t = 0;
        
        while (std::getline(std::cin, str)) {
            std::stringstream ss(str);
            if (ss >> u && u == 0) break;
            while (ss >> v) { 
                graph[u].push_back(v);
                graph[v].push_back(u);
            }
        }
        
        std::cout << dfs(-1, 1) << '\n';
        graph.clear();
    }
    
    return 0;
}