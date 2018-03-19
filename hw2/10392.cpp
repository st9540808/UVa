#include <iostream>
#include <string>
#include <vector>
#include <cmath>

std::vector<int> prime;

bool is_prime(int n) {
    int sqrt_n = std::sqrt(n);
    for (int i = 0; prime[i] <= sqrt_n; i++) {
        if (n % prime[i] == 0)
            return false;
    }
    return true;
}

int main(void)
{
    std::string input;
    long long int num;

    prime.push_back(2);
    prime.push_back(3);
    for (int i = 5, gap = 2; i < 2000000; i += gap, gap = 6 - gap) {
        if (is_prime(i))
            prime.push_back(i);
    }
    prime.push_back(6494693);

    while (std::cin >> num && num != -1) {
        for (const int p : prime) {
            while (num % p == 0) {
                std::cout << "    " << p << '\n';
                num /= p;
            }
            if (num == 1) break;
        }

        if (num != 1)
            std::cout << "    " << num << '\n';
        std::cout << '\n';
    }

    return 0;
}