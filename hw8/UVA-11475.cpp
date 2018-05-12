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
    int cur_pos = -1;

    for (int i = 0; i < lenA; i++) {
        while (cur_pos >= 0 && A[i] != B[cur_pos+1])
            cur_pos = pi[cur_pos];
        if (A[i] == B[cur_pos+1])
            cur_pos++;
        // if (cur_pos+1 == lenB) {
        //     /* Match!! */
        //     cur_pos = pi[cur_pos];
        // }
    }
    return cur_pos+1;
}

int main(int argc, const char *argv[])
{
    std::string S;

    while (std::cin >> S) {
        std::string R(S.rbegin(), S.rend());
        std::vector<int> pi(R.length());

        fail(R, pi);
        std::cout << S + R.substr(match(S, R, pi)) << '\n';
    }

    return 0;
}
