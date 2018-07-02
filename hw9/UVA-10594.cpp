#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#define INF 1000000

typedef long long board[200][200];
typedef long long array[200];

std::vector<std::vector<int>> edge(200);
board cap, flow, cost;
array pre, dis;
long long N, M, D, K;
long long MCMF(long long S, long long T);
bool SPFA(long long S, long long T);
void update(long long S, long long T, long long bottleneck);

int main()
{
    long long res;

    while (std::cin >> N >> M) {
        for (long long i = 0; i <= N; ++i)
            edge[i].clear();
        std::memset(flow, 0, sizeof(flow));

        long long u, v, c;
        for (long long i = 0; i < M; ++i) {
            std::cin >> u >> v >> c;
            edge[u].push_back(v);
            edge[v].push_back(u);
            cost[u][v] = cost[v][u] = c;
        }
        std::cin >> D >> K;

        for (long long i = 1; i <= N; ++i) {
            for (long long j : edge[i])
                cap[i][j] = K;
        }
        cap[0][1] = D;
        edge[0].push_back(1);

        res = MCMF(0, N);
        if (res == -1)
            std::cout << "Impossible.\n";
        else
            std::cout << res << '\n';
    }
}

long long MCMF(long long S, long long T)
{
    long long max_flow = 0;
    long long min_cost = 0;

    while (SPFA(S, T)) {
        long long ff = [&]() {
            long long bottleneck = INF;
            for (long long u = T; u != S; u = pre[u])
                bottleneck = std::min(bottleneck, cap[pre[u]][u] - flow[pre[u]][u]);
            return bottleneck;
        }();
        update(S, T, ff);
        max_flow += ff;
        min_cost += ff * dis[T];
    }
    if (max_flow != D) return -1;
    else return min_cost;
}

bool SPFA(long long S, long long T)
{
    bool inQueue[200] = {0};
    std::queue<int> q;

    std::fill(std::begin(dis), std::end(dis), INF);
    dis[S] = 0;
    q.push(S);
    inQueue[S] = true;

    while (!q.empty()) {
        long long u = q.front(); q.pop();
        inQueue[u] = false;

        for (long long v : edge[u]) {
            if (flow[v][u] > 0 && dis[u] - cost[v][u] < dis[v]) {
                dis[v] = dis[u] + (-cost[v][u]);
                pre[v] = u;
                if (!inQueue[v]) { q.push(v); inQueue[v] = true; }
            }
            else if (cap[u][v] > flow[u][v] && dis[u] + cost[u][v] < dis[v]) {
                dis[v] = dis[u] + cost[u][v];
                pre[v] = u;
                if (!inQueue[v]) { q.push(v); inQueue[v] = true; }
            }
        }
    }
    if (dis[T] == INF) return false;
    else return true;
}

void update(long long S, long long T, long long bottleneck)
{
    for (long long u = T; u != S; u = pre[u]) {
        flow[pre[u]][u] += bottleneck;
        flow[u][pre[u]] -= bottleneck;
    }
}
