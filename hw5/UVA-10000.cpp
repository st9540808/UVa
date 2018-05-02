#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#define INF 1000000

struct Edge {
    int from; int to;
};
std::array<int, 200> dist;

int main(void)
{
    static const auto relax = [](const Edge &e) {
        if (dist[e.from] - 1 < dist[e.to])
            dist[e.to] = dist[e.from] - 1;
    };
    int n, s, p, q;
    int cases = 1;
    
    while (std::cin >> n && n != 0) {
        std::vector<Edge> edge;
        std::cin >> s;
        
        while (std::cin >> p >> q && p != 0 && q != 0)
            edge.push_back({p, q});
        
        for (int i = 1; i <= n; i++)
            dist[i] = INF;
        dist[s] = 0;
        
        for (int i = 0; i < n-1; i++) {
            for (const auto &e : edge)
                relax(e);
        }

        auto it = std::min_element(dist.begin()+1, dist.begin()+n+1);
        int pos = std::distance(dist.begin(), it);

        printf("Case %d: The longest path from %d has length %d, finishing at %d.\n\n",
                cases++, s, -*it, pos);
    }

    return 0;
}