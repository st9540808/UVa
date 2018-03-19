#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(void)
{
    static const auto make_vec = [](const std::string& s) {
        std::vector<int> v;
        for (int i = s.length() - 1; i >= 0; i--)
            v.push_back(static_cast<int>(s[i] - '0'));
        return v;
    };
    
    std::string str1, str2;

    while (std::cin >> str1 >> str2) {
        const std::vector<int> num1 = make_vec(str1);
        const std::vector<int> num2 = make_vec(str2);
        std::vector<int> res;
        res.resize(num1.size() + num2.size(), 0);

        for (int i = 0; i < num2.size(); i++) {
            for (int j = 0; j < num1.size(); j++)
                res[i + j] += num2[i] * num1[j];

            for (int j = 0; j < num1.size(); j++) {
                res[i + j + 1] += res[i + j] / 10;
                res[i + j] %= 10;
            }
        }

        std::find_if(res.rbegin(), res.rend() - 1, [&](int i) {
            if (i != 0) return true;
            res.pop_back(); return false;
        });
        std::for_each(res.rbegin(), res.rend(), [](int i) {
            std::cout << i;
        });
        std::cout << '\n';
    }

    return 0;
}