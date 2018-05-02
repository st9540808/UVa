#include <iostream>
#include <climits>

int dp[20000];

int main(void)
{
    int n, value;
    
    for (int i = 1; i <= 10000; i++)
        dp[i] = INT_MAX;

    for (int i = 1; i <= 100; i++) {
        for (int j = i*i; j <= 10000; j++)
            if (dp[j] > dp[j - i*i] + 1) dp[j] = dp[j - i*i] + 1;
    }

    std::cin >> n;
    while (n--) {
        std::cin >> value;
        std::cout << dp[value] << '\n';
    }

    return 0;
}