#include <vector>
#include "iostream"


const int BIG = 2147483647;

std::vector<int> DXTR(std::vector<std::vector<std::pair<int, int>>> &g){
    std::vector<int> dist(g.size(), BIG);
    dist[1] = 0;
    std::vector<int> visited(g.size(), -1);

    int unseen;
    for (int i = 1; i < g.size(); ++i) {
        unseen = -1;
        for (int j = 1; j < g.size(); ++j) {
            if (visited[j] == -1 && (unseen == -1 || dist[unseen] > dist[j])){
                 unseen = j;
            }
        }

        if (dist[unseen] == BIG || unseen == -1){
            return std::vector<int>(0);
        }

        visited[unseen] = 1;

        for (auto &[near, time] : g[unseen]){
            if (dist[near] > dist[unseen] + time){
                dist[near] = dist[unseen] + time;
            }
        }
    }
    return dist;
}

int main(){
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int, int>>> graph(n+1);
    int a, b, t;
    for (int i = 0; i < m; ++i) {
        std::cin >> a >> b >> t;
        graph[a].emplace_back(b, t);
//        graph[b].emplace_back(a, t);
    }

    std::vector<int> ans = DXTR(graph);

    if (ans.empty() || ans[n] == BIG){
        std::cout << -1;
    }
    else{
        std::cout << ans[n];
    }

    return 0;
}