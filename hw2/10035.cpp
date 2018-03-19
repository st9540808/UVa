#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int main(void)
{
    static const auto make_vec = [](const std::string& s, int size) {
        std::vector<int> v;
        for (int i = s.length() - 1; i >= 0; i--)
            v.push_back(static_cast<int>(s[i] - '0'));
        for (int i = 0; i < size - s.length(); i++)
            v.push_back(0);
        return v;
    };

    std::string str1, str2;
    int size, carry;

    while (std::cin >> str1 >> str2 && !(str1 == "0" && str2 == "0")) {
        size = std::max(str2.length(), str1.length());
        
        const std::vector<int> num1 = make_vec(str1, size);
        const std::vector<int> num2 = make_vec(str2, size);
        std::vector<int> res;

        res.resize(std::max(num1.size(), num2.size()) + 1, 0);
        carry = 0;

        for (int i = 0; i < size; i++)
            res[i] = num2[i] + num1[i];

        for (int i = 0; i < res.size() - 1; i++) {
            carry += res[i] / 10;
            res[i + 1] += res[i] / 10;
            res[i] %= 10;
        }

        if (carry == 0)
            std::cout << "No carry operation.\n";
        else
            std::cout << carry << " carry operation"
                      << (carry > 1 ? "s.\n" : ".\n");
    }

    return 0;
}