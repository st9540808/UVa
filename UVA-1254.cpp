#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

int fail(const std::string& B, std::vector<int>& pi)
{
    int len = B.length();
    pi[0] = -1;

    for (int i = 1, cur_pos = -1; i < len; i++) {
        while (cur_pos >= 0 && B[i] != B[cur_pos+1])
            cur_pos = pi[cur_pos];
        if (B[i] == B[cur_pos+1]) cur_pos++;
        pi[i] = cur_pos;
    }
}

bool match(const std::string& A, const std::string& B,
           const std::vector<int>& pi)
{
    int lenA = A.length(), lenB = B.length();

    for (int i = 0, cur_pos = -1; i < lenA; i++) {
        while (cur_pos >= 0 && A[i] != B[cur_pos+1])
            cur_pos = pi[cur_pos];
        if (A[i] == B[cur_pos+1])
            cur_pos++;
        if (cur_pos+1 == lenB) {
            /* Match!! */
            // cur_pos = pi[cur_pos];
            return true;
        }
    }
    return false;
}

int main(int argc, const char *argv[])
{
    int N, Q;
    std::vector<std::string> dict;
    std::string query;

    std::cin >> N;
    dict.resize(N+1);
    std::for_each(dict.begin()+1, dict.end(), [](std::string& s) {
        std::cin >> s;
    });

    std::cin >> Q;
    for (int i = 0; i < Q; i++) {
        std::vector<int> pi;
        std::list<int> ans;
        std::cin >> query;
        
        pi.resize(query.length());
        fail(query, pi);

        for (int i = 1; i <= N; i++) {
            if (match(dict[i], query, pi))
                ans.push_back(i);
        }

        if (!ans.size())
            std::cout << -1;
        else {
            for (int i = 0; i < 10 && ans.size() > 0; i++) {
                auto it = std::min_element(ans.begin(), ans.end(),
                    [&dict](int r, int l) {
                        if (dict[r].length() < dict[l].length())
                            return true;
                        if (dict[r].length() == dict[l].length() &&
                            dict[r].compare(dict[l]) < 0)
                            return true;
                        return r < l;
                    }
                );
                if (i == 0) std::cout << *it;
                else std::cout << ' ' << *it;
                ans.erase(it);
            }
        }
        std::cout << '\n';
    }

    return 0;
}
