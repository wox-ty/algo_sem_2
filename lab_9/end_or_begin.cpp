#include <vector>
#include <queue>
#include "algorithm"
#include "iostream"

bool BFS(std::vector<std::vector<int>> &g, int start, int end){

    std::vector<int> visited(g.size(), -1);
    std::queue<int> q;

    visited[start] = 1;
    q.push(start);

    while (!q.empty()){
        int tmp = q.front();
        q.pop();

        if (tmp == end){
            return true;
        }

        for (auto &i : g[tmp]){
            if (visited[i] == -1){
                visited[i] = 1;
                q.push(i);
            }
        }
    }

    return false;
}

int main(){
    int n, m, q;

    std::cin >> n >> m >> q;

    std::vector<std::vector<int>> graph(n+1);

    int Ai, Bi;
    for (int i = 0; i < m; ++i) {
        std::cin >> Ai >> Bi;
        graph[Ai].push_back(Bi);
        graph[Bi].push_back(Ai);
    }

    int a, b;
    char command;
    for (int i = 0; i < q; ++i) {
        std::cin >> command >> a >> b;
        if (command == '?'){
            std::cout << (BFS(graph, a, b) ? "YES\n" : "NO\n");
        }
        else if (command == '-'){
            graph[a].erase(std::find(graph[a].begin(), graph[a].end(), b));
            graph[b].erase(std::find(graph[b].begin(), graph[b].end(), a));
        }
    }

    return 0;
}