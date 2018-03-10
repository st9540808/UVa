#include <iostream>
#include <queue>

int L, R, C;
char dungeon[31][31][31];
int distance[31][31][31];

int bfs(int i, int j, int k, int level) {
    static const struct pos { int i; int j; int k; } move[] = {
        {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}, {1, 0, 0}, {-1, 0, 0}
    };
    static const auto is_legal_move = [](const pos& p) {
        return (0 <= p.i && p.i < L) && (0 <= p.j && p.j < R) &&
               (0 <= p.k && p.k <= C) && !(dungeon[p.i][p.j][p.k] == '#');
    };

    std::queue<pos> q;
    q.push(pos{i, j, k});
    dungeon[i][j][k] = '#';
    distance[i][j][k] = 0;
    
    while (!q.empty()) {
        pos p = q.front(); q.pop();
        
        for (const auto &m : move) {
            pos np {p.i + m.i, p.j + m.j, p.k + m.k};
            
            if (is_legal_move(np)) {
                distance[np.i][np.j][np.k] = distance[p.i][p.j][p.k] + 1;
                if (dungeon[np.i][np.j][np.k] == 'E')
                    return distance[np.i][np.j][np.k];
                dungeon[np.i][np.j][np.k] = '#';
                q.push(np);
            }
        }
    }
    return 0;
}

int main(void)
{
    int cost;

    while (std::cin >> L >> R >> C && (L != 0 && R != 0 && C != 0)) {
        int sI, sJ, sK;
        
        for (int i = 0; i < L; i++) {
            for (int j = 0; j < R; j++) {
                for (int k = 0; k < C; k++) {
                    std::cin >> dungeon[i][j][k];
                    if (dungeon[i][j][k] == 'S') { sI = i; sJ = j; sK = k; }
                }
            }
        }

        if (cost = bfs(sI, sJ, sK, 0))
            std::cout << "Escaped in " << cost << " minute(s).\n";
        else
            std::cout << "Trapped!\n";
    }

    return 0;
}