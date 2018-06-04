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
    int N, M, B, D;

    while (std::cin >> N) {
        Graph_FlowNetWorks graph(2*N + 2);

        for (int i = 1; i <= N; i++) {
            int capacity;
            std::cin >> capacity;
            graph.mAdjMatrix[i][i + N] = capacity;
        }
        
        std::cin >> M;
        for (int i = 0; i < M; i++) {
            int from, to, capacity;
            std::cin >> from >> to >> capacity;
            graph.mAdjMatrix[from + N][to] = capacity;
        }

        std::cin >> B >> D;
        for (int i = 0; i < B; i++) {
            int to;
            std::cin >> to;
            graph.mAdjMatrix[0][to] = INT_MAX;
        }

        for (int i = 0; i < D; i++) {
            int from;
            std::cin >> from;
            graph.mAdjMatrix[from + N][2*N + 1] = INT_MAX;
        }

        std::cout << graph.FordFulkerson(0, 2*N + 1) << '\n';
    }

    return 0;
}
