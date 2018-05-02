#include <iostream>

int main(void)
{
    long long a, b, c, d;
    double n;

    while (std::cin >> a >> b >> n) {
        long double r1 = (long double) a / b , r2;
        for (d = 1; ; d++) {
            c = (long long) (r1 * d);
            
            while (a * d >= b * c)
                c++;

            r2 = (long double) c / d;
            if (r2 - r1 <= n) {
                std::cout << c << ' ' << d << '\n';
                break;
            }
        }
    }

    return 0;
}