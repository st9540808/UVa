#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <stack>

int LIS(const std::vector<int>& num)
{
    if (num.size() == 0) return 0;

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

    std::cout << v.size() << "\n-\n";
    while (!ans.empty()) {
        std::cout << ans.top() << '\n';
        ans.pop();
    }
}

int main(void)
{
    std::vector<int> num;
    std::copy(std::istream_iterator<int>(std::cin),
              std::istream_iterator<int>(),
              std::back_inserter(num)
    );
    LIS(num);
    
    return 0;
}