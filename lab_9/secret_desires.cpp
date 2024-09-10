#include <vector>
#include <algorithm>
#include "tuple"
#include "iostream"

int INF = 2147483647;

int find_cycle(std::vector<std::tuple<int, int, int>> &g, int vertices, int start) {
    std::vector<int> dist(vertices, INF);
    dist[start] = 0;
    std::vector<int> par(vertices, -1);
    int x;
    for (int i = 0; i < vertices; ++i) {
        x = -1;
        for (auto &edge : g){
            int first = std::get<0>(edge);
            int second = std::get<1>(edge);
            int normality = std::get<2>(edge);
            if (dist[first] != INF && dist[second] > (dist[first] + normality)){
                dist[second] = dist[first] + normality;
                par[second] = first;
                x = second;
            }
        }
    }

    if (x == -1){
        return -1;
    }
    else {
        int y;
        y = x;

        for (int i = 0; i < vertices; ++i) {
            y = par[y];
        }

        int counter = 0;
        int cur = y;
        do{
            cur = par[cur];
            ++counter;
        } while (cur != y);

//        --counter;
        return counter;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int N, k;
    std::cin >> N >> k;
    std::vector<std::tuple<int, int, int>> graph;
    std::vector<int> counters;
    int u, v, h;
    int n, m;

    for (int i = 0; i < N; ++i) {
        std::cin >> n >> m;
        graph.resize(m);
        for (int j = 0; j < m; j++) {
            std::cin >> u >> v >> h;
            --u;
            --v;
            graph[j] = std::make_tuple(u, v, h);
//            graph[j+1] = std::make_tuple(v, u, h);
        }


        for (int j = 0; j < n; ++j){
            counters.push_back(find_cycle(graph, n, j));
        }

        if (*std::max_element(counters.begin(), counters.end()) < k) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }

        graph.clear();
        counters.clear();
    }


    return 0;
}
/*
1 0
10 9
3 1 12383
3 8 5115
8 4 7123
8 10 1870
8 6 11696
3 9 14100
10 2 1126
3 7 538
8 5 6869

1 0
7 7
1 2 10
2 3 2
3 4 4
3 6 -6
4 5 7
6 7 -5
7 3 2

1 3
7 7
1 2 10
2 3 2
3 4 4
3 6 -6
4 5 7
6 7 -5
7 3 2

1 1
7 7
1 2 10
2 3 2
3 4 4
3 6 -6
4 5 7
6 7 -5
7 3 2


2 0
7 7
1 2 10
2 3 2
3 4 4
3 6 -6
4 5 7
6 7 -5
7 3 2
7 7
1 2 10
2 3 2
3 4 4
3 6 -6
4 5 7
6 7 -5
7 3 2
*/