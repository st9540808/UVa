#include <iostream>
#include <vector>
#include <array>
#include <queue>
#define INF 50000000

struct dest { int y; int len; };
std::array<std::vector<dest>, 30000> adjList;
int dist[30000];
int n, m, S, T;

int SPFA(void)
{
    bool inqueue[30000] = {false}, cycle = false;
    int count[30000] = {0};
    std::queue<int> q;

    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[S] = 0;
    inqueue[S] = true;
    count[S]++;
    q.push(S);

    while (!q.empty() && !cycle) {
        int now = q.front(); q.pop();
        inqueue[now] = false;
        
        for (auto &v : adjList[now]) {
            if (dist[v.y] > dist[now] + v.len) {
                dist[v.y] = dist[now] + v.len;
                if (!inqueue[v.y]) { 
                    q.push(v.y);
                    inqueue[v.y] = true;
                    count[v.y]++;
                    if (count[v.y] >= n) cycle = true;
                }
            }
        }
    }

    return dist[T];
}

int main(void)
{
    int N, ans;
    std::cin >> N;
    
    for (int cases = 1; cases <= N; cases++) {
        std::cin >> n >> m >> S >> T;
        
        for (int i = 0; i < n; i++)
            adjList[i].clear();
        
        for (int i = 0; i < m; i++) {
            int x, y, len;
            std::cin >> x >> y >> len;
            adjList[x].push_back({y, len});
            adjList[y].push_back({x, len});
        }

        ans = SPFA();
        std::cout << "Case #" << cases << ": ";
        if (ans == INF)
            std::cout << "unreachable\n";
        else
            std::cout << ans << '\n';
    }

    return 0;
}