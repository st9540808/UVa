#include <iostream>
#include <string>
#include <set>
#include <algorithm>

int main(int argc, const char *argv[])
{
    std::set<std::string> dict;
    std::string str;

    while (std::cin >> str)
        dict.insert(str);

    for (auto it = dict.begin(); it != dict.end(); it++) {
        const std::string s = *it;
        
        for (int i = 0; i < s.length(); i++) {
            const std::string prefix = s.substr(0, i);
            const std::string suffix = s.substr(i);
            
            if (dict.find(prefix) != dict.end() &&
                dict.find(suffix) != dict.end()) {
                std::cout << s << '\n';
                break;
            }
        }
    }

    return 0;
}
