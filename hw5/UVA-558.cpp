#include <iostream>

struct Edge {
    int from, to, len;
} edge[3000];
int dist[3000];
int n, m;

void relax(const Edge &e)
{
    if (dist[e.from] + e.len < dist[e.to]) {
        dist[e.to] = dist[e.from] + e.len;
    }
}

bool bellmanFord()
{
    dist[0] = 0;
    for (int i = 1; i < n; i++)
        dist[i] = 10000000;

    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < m; j++)
            relax(edge[j]);
    }

    for (int j = 0; j < m; j++)
        if (dist[edge[j].from] + edge[j].len < dist[edge[j].to])
            return true;
    return false;
}

int main(void)
{
    int cases;
    std::cin >> cases;

    while (cases--) {
        std::cin >> n >> m;
        for (int i = 0; i < m; i++)
            std::cin >> edge[i].from >> edge[i].to >> edge[i].len;
        if (bellmanFord())
            std::cout << "possible\n";
        else
            std::cout << "not possible\n";
    }

    return 0;
}