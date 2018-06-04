#include <iostream>
#include <vector>
#include <queue>
#include <utility>

class Graph_FlowNetWorks {
private:
    int num_vertex;
    std::vector<std::vector<int>> AdjMatrix;
public:
    Graph_FlowNetWorks(int n);
    void AddEdge(int from, int to, int capacity);

    int FordFulkerson(int source, int termination);
    bool BFSfindExistingPath(const std::vector<std::vector<int>>& graphResidual, 
                             int *predecessor, int source, int termination);
    int MinCapacity(std::vector<std::vector<int>> graphResidual, 
                    int *predecessor, int termination);

};
Graph_FlowNetWorks::Graph_FlowNetWorks(int n)
    : num_vertex(n)
    , AdjMatrix(num_vertex + 1, std::vector<int>(num_vertex + 1, 0))
{}

bool Graph_FlowNetWorks::BFSfindExistingPath(
    const std::vector<std::vector<int>>& graph, int predecessor[], int s, int t) {
    bool visited[num_vertex + 1] = { false };

    std::queue<int> queue;
    queue.push(s);
    visited[s] = true;
    predecessor[s] = -1;

    while (!queue.empty()) {
        int exploring = queue.front(); queue.pop();
        for (int j = 1; j <= num_vertex; j++) {
            if (graph[exploring][j] != 0 && visited[j] == 0) {
                queue.push(j);
                visited[j] = true;
                predecessor[j] = exploring;
            }
        }
    }
    return (visited[t] == true);
}

int Graph_FlowNetWorks::MinCapacity(std::vector<std::vector<int>> graph, 
                                    int predecessor[], int t) {
    int min = 1000;

    for (int idx = t; predecessor[idx] != -1; idx = predecessor[idx]) {
        if (graph[predecessor[idx]][idx] != 0 && graph[predecessor[idx]][idx] < min) {
            min = graph[predecessor[idx]][idx];
        }
    }
    return min;
}

int Graph_FlowNetWorks::FordFulkerson(int source, int termination) {
    std::vector<std::vector<int>> graphResidual(std::move(AdjMatrix));    
    int maxflow = 0;                                           
    int predecessor[num_vertex + 1];

    // BFS finds augmenting path,
    while (BFSfindExistingPath(graphResidual, predecessor, source, termination)) {
        int mincapacity = MinCapacity(graphResidual, predecessor, termination);
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
void Graph_FlowNetWorks::AddEdge(int from, int to, int capacity) {
    AdjMatrix[from][to] += capacity;
}

int main(int argc, char const *argv[])
{
    int n, s, t, c;
    int cases = 1;

    while (std::cin >> n && n != 0) {
        Graph_FlowNetWorks graph(n);
        int from, to, capacity;
        
        std::cin >> s >> t >> c;
        for (int i = 0; i < c; i++) {
            std::cin >> from >> to >> capacity;
            graph.AddEdge(from, to, capacity);
            graph.AddEdge(to, from, capacity);
        }
        std::cout << "Network " << cases++ << '\n'
                  << "The bandwidth is " << graph.FordFulkerson(s, t) << ".\n"
                  << "\n";
    }

    return 0;
}
