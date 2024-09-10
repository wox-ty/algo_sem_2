#include "vector"
#include "queue"
#include "algorithm"
#include "climits"
#include "iostream"

struct Edge{
    int start;
    int finish;
    int len;

    Edge(){}

    Edge(int a, int b, int c){
        start = a;
        finish = b;
        len = c;
    }

    bool operator<(const Edge &a) const{
        return a.len < this->len;
    }

    bool operator==(const Edge &a) const{
        return (a.finish == this->finish) && (a.start == this->start) && (a.len == this->len);
    }
};

std::vector<Edge> BFS(std::vector<std::vector<std::pair<int, int>>>& g, int start, int end) {
    std::queue<int> q;
    std::vector<bool> visited(g.size(), false);
    std::vector<int> parent(g.size(), -1);
    std::vector<Edge> Edges(g.size());

    q.emplace(start);
    visited[start] = true;

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        if (current == end) {
            break;
        }

        for (auto i : g[current]) {
            if (i.second != 0 && !visited[i.first]) {
                q.emplace(i.first);
                visited[i.first] = true;
                parent[i.first] = current;
                Edges[i.first] = Edge(current, i.first, i.second)/*{current.first, i, current.second}*/;
            }
        }
    }

    std::vector<Edge> path;
    for (int at = end; parent[at] != -1; at = parent[at]) {
        path.push_back(Edges[at]);
    }

    std::reverse(path.begin(), path.end());

    return path;
}

int karp(std::vector<std::vector<std::pair<int, int>>> &g){
    int res = 0;

    for (auto i : g[0]){
        res += i.second;
    }

    std::vector<Edge> u;
    while (!(u = BFS(g, 0, g.size()-1)).empty()){
        int cl = INT_MAX;
        for (auto i : u) {
            cl = std::min(cl, i.len);
        }
        for (auto i : u){
            int ca = i.start;
            int cb = i.finish;
            g[ca][cb].second -= cl;
            g[cb][ca].second += cl;
        }
    }

    for (auto i : g[0]){
        res -= i.second;
    }

    return res;
}

int main(){
    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<std::pair<int, int>>> graph(N, std::vector<std::pair<int, int>>(N));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            graph[i][j] = {j, 0};
        }
    }

    int a, b, c;
    for (int i = 0; i < M; ++i) {
        std::cin >> a >> b >> c;
        --a;
        --b;
        graph[a][b] = {b,c};
//        graph[b][a] = {a, 0};
    }

    int res;
    res = karp(graph);

    std::cout << res;

    return 0;
}
/*
8 11
1 2 5
1 3 7
1 4 6
2 5 4
3 5 3
3 6 8
3 7 1
4 6 5
5 8 8
6 8 5
7 8 4

6 8
1 2 7
1 4 15
2 3 5
2 5 5
4 3 10
4 5 5
3 6 5
5 6 15
*/