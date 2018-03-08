#include <iostream>

int gcd(int a, int b) {
    if (b == 0) return a;
    if (a % b == 0) return b;
    return gcd(b, a % b);
}

int main(void) {
    std::cout << gcd(51, 70) << std::endl;
    return 0;
}