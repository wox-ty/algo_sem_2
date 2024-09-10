#include "iostream"
#include <vector>

void DFS(std::vector<std::vector<int>> &p,std::vector<bool> &vis, int start, bool &ans, int par){
    if (!vis[start]) {
        vis[start] = true;
        for (int j = 0; j < p[start].size(); ++j) {
            if (vis[p[start][j]] && (par != p[start][j])){
                ans = true;
                return;
            }
            if ((!vis[p[start][j]]) && (p[p[start][j]].size() >= 2)) {
                DFS(p, vis, p[start][j], ans, start);
            }

        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> graph;
    graph.reserve(N+1);
    for (int i = 0; i < N+1; ++i){
        graph.emplace_back();
    }
    int a, b;
    for (int i = 0; i < M; ++i){
        std::cin >> a >> b;
        graph[a].emplace_back(b);
        graph[b].emplace_back(a);
    }

    bool ans = false;
    for (int i = 1; i < N+1; ++i) {
        std::vector<bool> vis (N+1, false);
        if (graph[i].size() >= 2) {
            DFS(graph, vis, i, ans, 0);
        }
        if (ans){
            std::cout << "YES";
            return 0;
        }
    }

    std::cout << "NO";

    return 0;
}