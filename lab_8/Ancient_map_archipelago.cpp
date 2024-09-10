#include <iostream>
#include <vector>
#include <queue>



struct Vertex {
    int number;
    std::vector<int> connected;
    int color;
    int len;

    Vertex() {
        connected = std::vector<int>();
        color = -1;
        number = -1;
        len = 0;
    };

    Vertex(int a) {
        connected = std::vector<int>();
        color = -1;
        number = a;
        len = 0;
    };
};

void BFS(std::vector<Vertex>& graph, int start) {
    std::vector<bool> visited(graph.size(), false);
    std::queue<int> q;

    q.push(start);
    visited[start] = true;
    graph[start].len = 0;

    while (!q.empty()) {
        int tmp = q.front();
        q.pop();
        for (int con : graph[tmp].connected) {
            if (!visited[con]) {
                q.push(con);
                visited[con] = true;
//                graph[con].len = std::min(graph[tmp].len + 1, graph[con].len);
                graph[con].len = graph[tmp].len + 1;
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int N, M, K;
    std::cin >> N >> M >> K;

    int i, j;
    std::vector<Vertex> graph;
    graph.push_back(Vertex(-99));
    for (int k = 0; k < N; ++k) {
        graph.push_back(Vertex(k + 1));
    }
    for (int k = 0; k < M; ++k) {
        std::cin >> i >> j;
        graph[i].connected.push_back(j);

        graph[j].connected.push_back(i);
    }

    BFS(graph, 1);

    int c = 0;
    for (auto v : graph) {
        if (v.len == K) {
            std::cout << v.number << "\n";
            ++c;
        }
    }
    if (c == 0) {
        std::cout << "NO";
    }

    return 0;
}
/*
7
9 2
1 2
1 3
2 4
3 4
3 5
3 6
4 5
5 6
6 7

7
7 2
1 2
2 4
2 6
1 3
4 5
3 5
3 7

6
5 3
1 2
1 4
4 5
4 3
3 6
 */