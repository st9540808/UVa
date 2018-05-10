#include <iostream>
#include <algorithm>
#define INF 301

int dp[400][400];
struct coin { int conv, info; } coins[400];

int main(void)
{
    int n, m, S, min;
    
    std::cin >> n;
    while (n--) {
        min = INF;

        std::cin >> m >> S;
        for (int i = 0; i < m; i++)
            std::cin >> coins[i].conv >> coins[i].info;

        for (int i = 0; i <= S; i++) {
            for (int j = 0; j <= S; j++)
                dp[i][j] = INF;
        }
        dp[0][0] = 0;

        for (int idx = 0; idx < m; idx++) {
            for (int i = coins[idx].conv; i <= S; i++) {
                for (int j = coins[idx].info; j <= S; j++)
                    dp[i][j] = std::min(
                        dp[i][j],
                        dp[i - coins[idx].conv][j - coins[idx].info] + 1
                    );
            }
        }

        for (int i = 0; i <= S; i++) {
            for (int j = 0; j <= S; j++) {
                if (i*i + j*j == S*S && dp[i][j] < min)
                    min = dp[i][j];
            }
        }

        if (min == INF)
            std::cout << "not possible\n";
        else
            std::cout << min << '\n';
    }
    
    return 0;
}