#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#define INF 1000000

struct Edge {
    int x, y, len;
};
std::vector<Edge> edge;
int T[10];
int floors[100];
int dist[100];

bool relax(const Edge &e)
{
    bool done = true;

    if (dist[e.x] + e.len + 60 < dist[e.y]) {
        dist[e.y] = dist[e.x] + e.len + 60;
        done = false;
    }

    if (dist[e.y] + e.len + 60 < dist[e.x]) {
        dist[e.x] = dist[e.y] + e.len + 60;
        done = false;
    }

    return done;
}

int bellmanFord(int k)
{
    for (int i = 1; i < 100; i++)
        dist[i] = INF;
    dist[0] = 0;

    for (int i = 0; i < 100; i++) {
        bool done = true;
        for (auto &e : edge)
            if (!relax(e)) done = false;
        if (done) break;
    }

    return k == 0 ? 0 : dist[k] == INF ? -1 : dist[k] - 60;
}

int main(void)
{
    int n, k, ans;

    std::ios::sync_with_stdio(false);
    while (std::cin >> n >> k) {
        edge.clear();

        for (int i = 0; i < n; i++)
            std::cin >> T[i];
        std::cin.ignore();

        for (int i = 0; i < n; i++) {
            int count = 0;
            std::string str;

            std::getline(std::cin, str);
            std::stringstream ss(str);

            while (ss >> floors[count]) count++;
            for (int x = 0; x < count; x++) {
                for (int y = x+1; y < count; y++)
                    edge.emplace_back(Edge {
                        floors[x], floors[y], (floors[y] - floors[x]) * T[i]}
                    );
            }
        }
        
        if ((ans = bellmanFord(k)) == -1)
            std::cout << "IMPOSSIBLE\n";
        else
            std::cout << ans << '\n';
    }

    return 0;
}