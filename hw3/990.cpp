#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

struct item {
    int d, v;
};

int main(void)
{
    int t, w; // time and constant
    bool first = true;

    while (std::cin >> t >> w) {
        int n;
        std::cin >> n;

        std::vector<item> items(n);
        std::for_each(items.begin(), items.end(), [](item& i) {
            std::cin >> i.d >> i.v;
        });
        std::vector<std::vector<int>> dp(n+1, std::vector<int>(t+1, 0));
        std::stack<int> ans;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= t; j++) {
                if (j - 3 * w * items[i].d < 0)
                    dp[i + 1][j] = dp[i][j];
                else
                    dp[i + 1][j] = std::max(
                        dp[i][j],
                        dp[i][j - 3 * w * items[i].d] + items[i].v
                    );
            }
        }
        
        for (int i = n-1, j = t; i >= 0; i--) {
            if (j - 3*w*items[i].d >= 0 &&
                dp[i+1][j] == dp[i][j - 3*w*items[i].d] + items[i].v) {
                ans.push(i);
                j -= 3*w*items[i].d;
            }
        }

        if (first)
            first = false;
        else
            std::cout << '\n';

        std::cout << dp[n][t] << '\n';
        std::cout << ans.size() << '\n';

        while (!ans.empty()) {
            int idx = ans.top(); ans.pop();
            std::cout << items[idx].d << ' ' << items[idx].v << '\n';
        }
    }

    return 0;
}