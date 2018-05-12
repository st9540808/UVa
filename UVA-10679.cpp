#include <iostream>
#include <string>
#include <vector>

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

bool match(std::string& A, std::string& B, std::vector<int>& pi)
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
    int k, q;
    std::string S, T;

    std::cin >> k;
    while (k--) {
        std::cin >> S >> q;
 
        for (int i = 0; i < q; i++) {
            std::cin >> T;
            std::vector<int> pi(T.length());            
            
            fail(T, pi);
            std::cout << (match(S, T, pi) ? 'y' : 'n') << '\n';
        }
    }

    return 0;
}
