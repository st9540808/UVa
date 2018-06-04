#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>

struct Graph_FlowNetWorks {
    using _2dvector = std::vector<std::vector<int>>;
    
    int mNumVertex;
    _2dvector mAdjMatrix;

    Graph_FlowNetWorks(int n);
    int FordFulkerson(int source, int termination);
    bool BFSfindExistingPath(const _2dvector& graphResidual, int predecessor[],
                             int source, int termination);
    int MinCapacity(const _2dvector& graphResidual,
                    int predecessor[], int termination);
};
Graph_FlowNetWorks::Graph_FlowNetWorks(int n)
    : mNumVertex(n)
    , mAdjMatrix(mNumVertex, std::vector<int>(mNumVertex, 0))
{}

bool Graph_FlowNetWorks::BFSfindExistingPath(const _2dvector& graph,
                                             int predecessor[], int s, int t) {
    bool visited[mNumVertex] = { false };

    std::queue<int> queue;
    queue.push(s);
    visited[s] = true;
    predecessor[s] = -1;

    while (!queue.empty()) {
        int exploring = queue.front(); queue.pop();
        for (int j = 0; j < mNumVertex; j++) {
            if (graph[exploring][j] != 0 && visited[j] == false) {
                queue.push(j);
                visited[j] = true;
                predecessor[j] = exploring;
            }
        }
    }

    return (visited[t] == true);
}

int Graph_FlowNetWorks::MinCapacity(const _2dvector& graph, int predecessor[], int t) {
    int min = INT_MAX;

    for (int idx = t; predecessor[idx] != -1; idx = predecessor[idx]) {
        if (graph[predecessor[idx]][idx] != 0 && graph[predecessor[idx]][idx] < min) {
            min = graph[predecessor[idx]][idx];
        }
    }
    return min;
}

int Graph_FlowNetWorks::FordFulkerson(int source, int termination) {
    std::vector<std::vector<int>> graphResidual(std::move(mAdjMatrix));    
    int maxflow = 0, mincapacity;
    int predecessor[mNumVertex];

    // BFS finds augmenting path
    while (BFSfindExistingPath(graphResidual, predecessor, source, termination)) {
        mincapacity = MinCapacity(graphResidual, predecessor, termination);
        maxflow += mincapacity;
        for (int Y = termination; Y != source; Y = predecessor[Y]) {
            // update residual graph
            int X = predecessor[Y];
            graphResidual[X][Y] -= mincapacity;
            graphResidual[Y][X] += mincapacity;
        }
    }
    return maxflow;
}


int main(int argc, char const *argv[])
{
    int T, n, m, k, num;
    
    std::cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        std::cin >> n >> m;
        Graph_FlowNetWorks graph(n + m + 2);

        for (int i = 1; i <= n; i++) {
            std::cin >> k;
            for (int j = 1; j <= k; j++) {
                std::cin >> num;
                graph.mAdjMatrix[i][num + n]++;
            }
        }

        for (int i = 2; i <= n; i++) {
            for (int j = n+1; j <= n+m; j++) {
                if (graph.mAdjMatrix[i][j] > 0)
                    graph.mAdjMatrix[i][j]--;
                else
                    graph.mAdjMatrix[j][i] = 1;
            }
        }

        for (int i = n+1; i <= n+m; i++)
            graph.mAdjMatrix[i][n+m+1] = 1;

        // for (int i = 1; i < graph.mNumVertex; i++) {
        //     std::cout << i << ": ";
        //     for (int j = 1; j < graph.mAdjMatrix[i].size(); j++)
        //         std::cout << graph.mAdjMatrix[i][j] << ' ';
        //     std::cout << '\n';
        // }
        std::cout << "Case #" << cases << ": "
                  << graph.FordFulkerson(1, n+m+1) << '\n';
    }

    return 0;
}
