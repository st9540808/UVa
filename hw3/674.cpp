#include <iostream>

int dp[10000];
int v[5] = {1, 5, 10, 25, 50};

int main(void)
{
    int value;

    dp[0] = 1;
    for (int i = 0; i < 5; i++) {
        for (int j = v[i]; j < 10000; j++)
            if (dp[j - v[i]] > 0) dp[j] += dp[j - v[i]];
    }

    while (std::cin >> value) {
        std::cout << dp[value] << '\n';
    }

    return 0;
}