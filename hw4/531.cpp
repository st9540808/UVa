#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> text1, text2;
int lcs[200][200];
int pre[200][200];

void printLCS(int i, int j);
void LCS(void)
{
    int n1 = text1.size() - 1, n2 = text2.size() - 1;

    for (int i = 1; i <= n1; i++) {
        for (int j = 1; j <= n2; j++) {
            if (text1[i] == text2[j]) {
                lcs[i][j] = lcs[i-1][j-1] + 1;
                pre[i][j] = 0; // upper left
            } else {
                if (lcs[i-1][j] <= lcs[i][j-1]) {
                    lcs[i][j] = lcs[i][j-1];
                    pre[i][j] = 1; // left
                } else {
                    lcs[i][j] = lcs[i-1][j];
                    pre[i][j] = 2; // upper
                }
            }
        }
    }
    printLCS(n1, n2);
}

void printLCS(int i, int j)
{
    int l = lcs[i][j];
    std::vector<std::string> ans(l);

    while (l > 0) {
        if (pre[i][j] == 0) {
            ans[--l] = text1[i];
            i--; j--;
        } else if (pre[i][j] == 1)
            j--;
        else if (pre[i][j] == 2)
            i--;
    }

    if (ans.size() > 0) std::cout << ans[0];
    for (int k = 1; k < ans.size(); k++)
        std::cout << ' ' << ans[k];
}

int main(void)
{
    std::string str;
    bool first = true;

    while (std::cin.peek(), !std::cin.eof()) {
        text1.clear();
        text2.clear();

        text1.push_back("");
        while (std::cin >> str && str != "#")
            text1.push_back(str);

        text2.push_back("");
        while (std::cin >> str && str != "#")
            text2.push_back(str);

        if (first)
            first = false;
        else
            std::cout << '\n';

        LCS();
    }
}