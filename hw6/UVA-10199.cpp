#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstring>
#include <set>

int dfn[200];
int low[200];
int t;
std::vector<std::vector<int>> graph;
std::set<std::string> ans;
std::unordered_map<std::string, int> indx;
std::unordered_map<int, std::string> name;

void dfs(int cur, int prev = -1)
{
    int child = 0;
    dfn[cur] = low[cur] = ++t;

    for (int v : graph[cur]) {
        if (!dfn[v]) {
            child++;
            dfs(v, cur);
            low[cur] = std::min(low[cur], low[v]);

            if ((prev == -1 && child > 1) || (prev != -1 && low[v] >= dfn[cur]))
                ans.insert(name[cur]);
        } else if (v != prev)
            low[cur] = std::min(low[cur], dfn[v]);
    }
}

int main(void)
{
    int N, num, cases = 1;
    std::string str1, str2;
    
    while (std::cin >> N && N != 0) {
        graph.resize(N);
        
        for (int i = 0; i < N; i++) {
            std::cin >> str1;
            indx[str1] = i;
            name[i] = str1;
        }

        std::cin >> num;
        for (int i = 0; i < num; i++) {
            std::cin >> str1 >> str2;
            graph[indx[str1]].push_back(indx[str2]);
            graph[indx[str2]].push_back(indx[str1]);
        }

        // for (int i = 0; i < graph.size(); i++) {
        //     std::cout << name[i] << ": ";
        //     for (int j = 0; j < graph[i].size(); j++)
        //         std::cout << graph[i][j] << ' ';
        //     std::cout << '\n';
        // }
        // std::cout << '\n';

        for (int i = 0; i < N; i++) {
            if (!dfn[i])
                dfs(i);
        }

        if (cases != 1) std::cout << '\n';
        std::cout << "City map #" << cases++ <<": " 
                  << ans.size() << " camera(s) found\n";
        for (auto& s : ans)
            std::cout << s << '\n';
        // std::cout << '\n';

        t = 0;
        for (int i = 0; i < N; i++)
            graph[i].clear();
        graph.clear();
        ans.clear();
        indx.clear();
        name.clear();
        std::memset(dfn, 0, sizeof dfn);
        std::memset(low, 0, sizeof low);
    }

    return 0;
}