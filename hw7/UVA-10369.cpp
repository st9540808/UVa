#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <cmath>

// from: (to, distance)
std::vector<std::vector<std::pair<int, double>>> graph;
struct { int x, y; } vertices[1000];

double prim(int n, int S)
{
    std::unordered_map<int, double> mst_map;
    std::vector<double> ans;
    auto cmp = [](std::pair<int, double> l, std::pair<int, double> r) {
        return l.second < r.second;
    };

    mst_map.emplace(0, 0.);
    for (int i = 1; i < n; i++)
        mst_map.emplace(i, 1e9);

    while (!mst_map.empty()) {
        auto min = *min_element(mst_map.begin(), mst_map.end(), cmp);
        int u = min.first;
        ans.push_back(min.second);
        mst_map.erase(min.first);

        for (const auto& p : graph[u]) {
            if (mst_map.find(p.first) != mst_map.end() and
                p.second < mst_map[p.first]) {
                mst_map[p.first] = p.second;
            }
        }
    }

    std::sort(ans.begin(), ans.end());
    return *(ans.crbegin() + (S - 1));
}

int main(void)
{
    int N, S, P;

    std::cin >> N;
    while (N--) {
        std::cin >> S >> P;
        for (int i = 0; i < P; i++)
            std::cin >> vertices[i].x >> vertices[i].y;

        graph.resize(P);
        for (auto& v : graph) v.clear();

        for (int i = 0; i < P; i++) {
            for (int j = i+1; j < P; j++) {
                double dis = std::sqrt(
                    std::pow(vertices[i].x - vertices[j].x, 2) +
                    std::pow(vertices[i].y - vertices[j].y, 2)
                );
                graph[i].emplace_back(j, dis);
                graph[j].emplace_back(i, dis);
            }
        }

        std::cout << std::fixed << std::setprecision(2) 
                  << prim(P, S) << '\n';
    }

    return 0;
}