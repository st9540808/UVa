#include <iostream>
#include <cmath>

int main(void)
{
    long long M, N, ans;
    
    while (std::cin >> M >> N && M != 0) {
        ans = 0;
        if (N > M)
            std::swap(M, N);
        ans += M * N * (N - 1);
        ans += N * M * (M - 1);
        ans += 4 * ((M - N + 1)*N*(N - 1)/2 + 2*(N*(N - 1)*(N - 2)/6));
        std::cout << ans << '\n';
    }

    return 0;
}