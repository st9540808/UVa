#include <iostream>
#include <algorithm>
#define INF 1000000

struct Edge {
    int x, y, len;
} edge[2000];
int dist[200][200];

void floydWarshall(int C, int S)
{
    for (int i = 1; i <= C; i++) {
        for (int j = 1; j <= C; j++)
            dist[i][j] = INF;
        dist[i][i] = 0;
    }
    for (int i = 0; i < S; i++) {
        dist[edge[i].x][edge[i].y] = edge[i].len;
        dist[edge[i].y][edge[i].x] = edge[i].len;
    }

    for (int k = 1; k <= C; k++) {
        for (int i = 1; i <= C; i++) {
            for (int j = 1; j <= C; j++) {
                if (dist[i][j] > std::max(dist[i][k], dist[k][j]))
                    dist[i][j] = std::max(dist[i][k], dist[k][j]);
            }
        }
    }
}

int main(void)
{
    int C, S, Q, cases = 1;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    while (std::cin >> C >> S >> Q && (C != 0 && S != 0 && Q != 0)) {
        for (int i = 0; i < S; i++)
            std::cin >> edge[i].x >> edge[i].y >> edge[i].len;
        
        floydWarshall(C, S);
        
        if (cases != 1) std::cout << '\n';
        std::cout << "Case #" << cases << '\n';

        for (int i = 0; i < Q; i++) {
            int x, y;
            std::cin >> x >> y;
            
            if (dist[x][y] == INF)
                std::cout << "no path\n";
            else
                std::cout << dist[x][y] << '\n';
        }

        cases++;
    }

    return 0;
}