#include <iostream>

int n;
int num[20], ans[20];
bool visit[20];

void backtrack(int idx, int len)
{
    if (len == 6) {
        std::cout << ans[0];
        for (int i = 1; i < 6; i++)
            std::cout << ' ' << ans[i];
        std::cout << '\n'; 
        return;
    }

    for (int i = idx; i < n; i++) {
        if (!visit[i]) {
            visit[i] = true;
            ans[len] = num[i];
            backtrack(i + 1, len + 1);
            visit[i] = false;
        }
    }
}

int main(void)
{
    bool first = true;

    while (std::cin >> n && n != 0) {
        for (int i = 0; i < n; i++) {
            std::cin >> num[i];
            visit[i] = false;
        }

        if (!first)
            std::cout << '\n';
        first = false;
        
        backtrack(0, 0);
    }

    return 0;
}