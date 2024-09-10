#include <vector>
#include <map>
#include "iostream"
#include "climits"

#define INF LONG_MAX

std::vector<long> DXTR(std::vector<std::map<long, long>> &g){
    std::vector<long> dist(g.size(), INF);
    dist[0] = 0;
    std::vector<long> visited(g.size(), -1);

    long unseen;
    for (long i = 0; i < g.size(); ++i) {
        unseen = -1;
        for (long j = 0; j < g.size(); ++j) {
            if (visited[j] == -1 && (unseen == -1 || dist[unseen] > dist[j])){
                unseen = j;
            }
        }

        visited[unseen] = 1;

        for (auto &b : g[unseen]){
            if (dist[unseen] != INF && b.second != INF && dist[b.first] > dist[unseen] + b.second){
                dist[b.first] = dist[unseen] + b.second;
            }
        }
    }

    return dist;
}

int main(){
    long n, m, k;
    std::cin >> n >> m >> k;
// start = 0 fin = k-1
    std::vector<std::map<long, long>> graph(n);

    for (long i = 0; i < n; ++i) {
        for (long j = 0; j < n; ++j) {
            if (i == j){
                continue;
            }
            graph[i][j] = INF;
        }
    }

    std::vector<long> cur_stream;
    long a, num, dist;
    for (long i = 0; i < m; ++i) {
        std::cin >> num >> dist;
        for (long j = 0; j < num; ++j) {
            std::cin >> a;
            --a;
            cur_stream.push_back(a);
        }
        for (auto cur1 : cur_stream){
            for (auto cur2 : cur_stream){
                if (cur1 == cur2){
                    continue;
                }
                graph[cur1][cur2] = std::min(dist, graph[cur1][cur2]);
            }
        }
        cur_stream.clear();
    }

    std::vector<long> ans = DXTR(graph);

//    for (auto i : ans){
//        std::cout << i << " ";
//    }

//    for (int i = 0; i < graph.size(); ++i){
//        for (auto b : graph[i]){
//            if (b.second != INF){
//                std::cout << i+1 << " --> " << b.first+1 << " = " << b.second << "\n";
//            }
//        }
//        std::cout << "------------------\n";
//    }

    std::cout << (ans[k-1] == INF ? -1 : ans[k-1]);

    return 0;
}
/*
5 4 5
3 7 1 2 3
3 11 2 4 5
4 4 2 3 4 5
2 2 1 3

5 4 5
3 7 1 2 3
2 11 2 4
3 4 2 3 4
2 2 1 3

6 2 6
3 5 1 2 3
3 4 4 5 6
*/