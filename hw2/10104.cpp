#include <iostream>

int ex_gcd(int a, int b, int& X, int& Y) {
    if (b == 0) {
        X = 1;
        Y = 0;
        return a;
    } else {
        int gcd = ex_gcd(b, a % b, X, Y);
        int tmp = X;
        X = Y;
        Y = tmp - (a / b) * Y;
        return gcd;
    }
}

int main(void)
{
    int a, b, X, Y;
    
    while (std::cin >> a >> b) {
        int gcd = ex_gcd(a, b, X, Y);
        std::cout << X << ' ' << Y << ' ' << gcd << '\n';
    }

    return 0;
}