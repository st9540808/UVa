#include <iostream>
#include <string>
#include <map>
#include <algorithm>

int main(int argc, const char *argv[])
{
    int N, len;
    std::string text, str;
    
    while (std::cin >> N >> text) {
        std::map<std::string, int> occurrence;
        const int len = text.length();

        for (int i = 0; i <= len - N; i++) {
            str = text.substr(i, N);

            if (occurrence.find(str) != occurrence.end())
                occurrence[str]++;
            else
                occurrence[str] = 1;
        }

        auto max = std::max_element(occurrence.begin(), occurrence.end(),
            [](const std::map<std::string, int>::value_type& l,
               const std::map<std::string, int>::value_type& r) {
                return l.second < r.second;
            }
        );

        std::cout << (*max).first << '\n';
    }
    
    return 0;
}
