#include <iostream>
#include <string>
#include <vector>

int fail(const std::string &B, std::vector<int>& pi)
{
    int len = B.length(), cur_pos = -1;
    pi[0] = -1;

    for (int i = 1; i < len; i++) {
        while (cur_pos >= 0 && B[i] != B[cur_pos + 1])
            cur_pos = pi[cur_pos];
        if (B[i] == B[cur_pos + 1])
            cur_pos++;
        pi[i] = cur_pos;
    }

    return cur_pos;
}

void match(std::string& A, std::string& B, std::vector<int>& pi)
{
    int lenA = A.length(), lenB = B.length();

    for (int i = 0, cur_pos = -1; i < lenA; i++) {
        while (cur_pos >= 0 && A[i] != B[cur_pos+1])
            cur_pos = pi[cur_pos];
        if (A[i] == B[cur_pos+1])
            cur_pos++;
        if (cur_pos+1 == lenB) {
            /* Match!! */
            cur_pos = pi[cur_pos];
        }
    }
}

int main(int argc, const char *argv[])
{
    int len, lst_fail;
    std::string str;
    
    while (std::cin >> str && str != ".") {
        std::vector<int> pi(len = str.length());
        lst_fail = fail(str, pi);

        if (len % (len-lst_fail-1) || lst_fail == -1)
            std::cout << 1 << '\n';
        else
            std::cout << len / (len-lst_fail-1) << '\n';
    }

    return 0;
}