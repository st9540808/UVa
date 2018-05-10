#include <iostream>
#include <cmath>

int f(int n)
{
    int edges = n * (n - 1) / 2;
    if (n != 1)
        return (int) std::ceil(edges / (n - 1));
}

int main(void)
{
    int cases = 1, n;

    while (std::cin >> n && n != 0) {
        std::cout << "Case " << cases++ << ": "
                  << f(n) << '\n';
    }

    return 0;
}