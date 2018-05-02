#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <stack>
#include <string>

void LIS(const std::vector<int>& num)
{
    if (num.size() == 0) return;

    std::vector<int> v, lis;
    std::stack<int> ans;
    v.push_back(num[0]);
    
    for (int i = 0; i < num.size(); i++) {
        int n = num[i];
        if (n > v.back()) {
            v.push_back(n);
            lis.push_back(v.size() - 1);
        }
        else {
            auto it = std::lower_bound(v.begin(), v.end(), n);
            *it = n;
            lis.push_back(it - v.begin());
        }
    }
    
    for (int i = lis.size() - 1, n = v.size() - 1; n >= 0; i--) {
        if (lis[i] == n) {
            ans.push(num[i]);
            n--;
        }
    }

    std::cout << "Max hits: " << v.size() << "\n";
    //for (auto i : v) std::cout << i << '\n';
    while (!ans.empty()) {
        std::cout << ans.top() << '\n';
        ans.pop();
    }
}

int main(void)
{
    int n;
    std::string input;
    std::getline(std::cin, input);
    n = std::stoi(input);
    std::cin.ignore(1, '\n');

    while (n--) {
        std::vector<int> num;

        while (std::getline(std::cin, input) && !input.empty())
            num.push_back(std::stoi(input));

        LIS(num);
        if (n) std::cout << '\n';
    }
        
    return 0;
}