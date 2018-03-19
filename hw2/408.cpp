#include <iostream>
#include <iomanip>

int gcd(int a, int b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

int main(void)
{
    int step, mod;

    while (std::cin >> step >> mod) {
        std::cout << std::setw(10) << step;
        std::cout << std::setw(10) << mod;        
        std::cout << "    " << (gcd(step, mod) == 1 ? "Good Choice" : "Bad Choice")
                  << '\n';
        std::cout << '\n';
    }

    return 0;
}