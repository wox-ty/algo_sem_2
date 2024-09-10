#include <iostream>
#include <vector>
#include <queue>

void bfs(const std::vector<std::vector<int>>& graph, int start) {
    std::vector<bool> visited(graph.size(), false);
    std::queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        std::cout << node << " ";

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }

        // Учитываем кратные рёбра
        for (int i = 0; i < graph.size(); ++i) {
            for (int neighbor : graph[i]) {
                if (neighbor == node && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }
}

int main() {
    std::vector<std::vector<int>> graph = {
            {1, 2, 2},     // вершина 0 связана с вершинами 1, 2 и 2 (кратное ребро)
            {0, 3, 4},
            {0, 5},
            {1},
            {1},
            {2}
    };

    int startNode = 0;
    std::cout << "Обход графа в ширину с учетом кратных рёбер, начиная с вершины " << startNode << ": ";
    bfs(graph, startNode);

    return 0;
}
