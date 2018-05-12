#include <iostream>
#include <string>
#include <vector>
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

int match(const std::string& A, const std::string& B,
          const std::vector<int>& pi)
{
    int lenA = A.length(), lenB = B.length();
    int cnt = 0;

    for (int i = 0, cur_pos = -1; i < lenA; i++) {
        while (cur_pos >= 0 && A[i] != B[cur_pos+1])
            cur_pos = pi[cur_pos];
        if (A[i] == B[cur_pos+1])
            cur_pos++;
        if (cur_pos+1 == lenB) {
            /* Match!! */
            cur_pos = pi[cur_pos];
            cnt++;
        }
    }
    return cnt;
}

int main(int argc, const char *argv[])
{
    int N;
    std::string text;

    while (std::cin >> N && N != 0) {
        using str_pair = std::pair<std::string, int>;
        int max;
        std::string max_str;
        std::vector<str_pair> strs(N);

        std::for_each(strs.begin(), strs.end(), [](str_pair& s) {
            std::cin >> s.first;
            s.second = 0;
        });
        std::cin >> text;

        std::for_each(strs.begin(), strs.end(),
            [&max, &max_str, &text](str_pair& s) {
                std::vector<int> pi(s.first.length());
                fail(s.first, pi);
                s.second = match(text, s.first, pi);
            }
        );

        max = (*std::max_element(strs.begin(), strs.end(),
            [](const str_pair& l, const str_pair& r) {
                return l.second < r.second;
            }
        )).second;

        std::cout << max << '\n';
        std::for_each(strs.begin(), strs.end(),
            [max](const str_pair& s) {
                if (s.second == max) std::cout << s.first << '\n';
            }
        );
    }

    return 0;
}
