#include <iostream>

int m, n;
char grid[100][100];
static int nPockets = 0;

void dfs(const int x, const int y)
{
    if (nPockets == 100)
        return;
        
    static const struct { int x; int y; } offset[8] {
        {0, -1}, {1, -1}, {1, 0}, {1, 1},
        {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}
    };

    for (int i = 0; i < 8; i++) {
        int newX = x + offset[i].x;
        int newY = y + offset[i].y;
        
        if ((0 <= newY && newY < m) && (0 <= newX && newX < n)) {
            if (grid[newY][newX] == '@') {
                grid[newY][newX] = '*';
                nPockets++;
                dfs(newX, newY);
            }
        }   
    }
}

int search(void)
{
    int nDeposit = 0;
    nPockets = 0;
    
    for (int y = 0; y < m; y++) {
        for (int x = 0; x < n; x++) {
            if (grid[y][x] == '@') {
                grid[y][x] = '*';
                nPockets++; nDeposit++;
                dfs(x, y);
            }
        }
    }

    return nDeposit;
}


int main(void)
{
    while (std::cin >> m >> n && m != 0) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                std::cin >> grid[i][j];
        }

        std::cout << search() << "\n";
    }

    return 0;
}
