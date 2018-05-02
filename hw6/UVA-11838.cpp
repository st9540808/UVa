#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>

int dfn[4000];
int low[4000];
int t;
std::vector<std::vector<int>> graph;

int ans;
bool in_stk[4000];
std::stack<int> stk;

void dfs(int cur)
{
    int top;
    low[cur] = dfn[cur] = ++t;
    
    stk.push(cur);
    in_stk[cur] = true;
    for (int v : graph[cur]) {
        if (!dfn[v]) {
            dfs(v);
            low[cur] = std::min(low[cur], low[v]);
        } else if (in_stk[v])
            low[cur] = std::min(low[cur], dfn[v]);
    }

    if (dfn[cur] == low[cur]) {
        do {
            top = stk.top();
            stk.pop();
            in_stk[top] = false;
        } while (top != cur);
        ans++;
    }
}

int main(void)
{
    int N, M;

    while (std::cin >> N >> M && N != 0 && M != 0) {
        graph.resize(N + 1);
        t = 0;

        for (int i = 0; i < M; i++) {
            int V, W, P;
            std::cin >> V >> W >> P;
            graph[V].push_back(W);
            if (P == 2) graph[W].push_back(V);
        }

        ans = 0;
        for (int i = 1; i <= N; i++)
            if (!dfn[i] && ans <= 1) dfs(i);
        std::cout << !!(ans == 1) << '\n';

        std::memset(dfn, 0, sizeof dfn);
        std::memset(in_stk, 0, sizeof in_stk);
        std::for_each(graph.begin(), graph.end(),
            [](std::vector<int>& v) { v.clear(); }
        );
    }

    return 0;
}