#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <cmath>

// from: (to, distance)
std::vector<std::vector<std::pair<int, double>>> graph;
struct { double x, y; } vertices[200];

double prim(int n)
{
    std::unordered_map<int, double> mst_map;
    double sum = 0.;
    auto cmp = [](std::pair<int, double> l, std::pair<int, double> r) {
        return l.second < r.second;
    };

    mst_map.emplace(0, 0.);
    for (int i = 1; i < n; i++)
        mst_map.emplace(i, 1e9);

    while (!mst_map.empty()) {
        auto min = *min_element(mst_map.begin(), mst_map.end(), cmp);
        int u = min.first;
        sum += min.second;
        mst_map.erase(min.first);

        for (const auto& p : graph[u]) {
            if (mst_map.find(p.first) != mst_map.end() and
                p.second < mst_map[p.first]) {
                mst_map[p.first] = p.second;
            }
        }
    }

    return sum;
}

int main(void)
{
    int cases, n;
    
    std::cin >> cases;
    while (cases--) {
        std::cin >> n;
        for (int i = 0; i < n; i++)
            std::cin >> vertices[i].x >> vertices[i].y;

        graph.resize(n);
        for (auto& v : graph) v.clear();

        for (int i = 0; i < n-1; i++) {
            for (int j = i+1; j < n; j++) {
                double dis = std::sqrt(
                    std::pow(vertices[i].x - vertices[j].x, 2) +
                    std::pow(vertices[i].y - vertices[j].y, 2)
                );
                graph[i].emplace_back(j, dis);
                graph[j].emplace_back(i, dis);
            }
        }

        std::cout << std::fixed << std::setprecision(2) 
                  << prim(n) << '\n';
        if (cases) std::cout << '\n';
    }

    return 0;
}