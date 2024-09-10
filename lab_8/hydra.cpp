#include <iostream>
#include <vector>
#include <algorithm>

void DFS(int node, std::vector<std::vector<int>> &g, std::vector<int> &visited, int par, std::vector<int> &cycle,
         bool &state) {
    visited[node] = 0;
    cycle.push_back(node);

    for (int connected: g[node]) {
        if (visited[connected] == -1) {
            DFS(connected, g, visited, node, cycle, state);
            if (state) {
                return;
            }
        } else if (connected != par) {
            state = true;
            return;
        }
    }

    cycle.pop_back();
}

bool make_tree(std::vector<std::vector<int>> &g, std::vector<int> &vis, std::vector<std::vector<int>> &trees, int cur, int start, std::vector<int> &Cycle, int BS){
    trees[cur].push_back(start);
    vis[start] = 1;
    for (auto i : g[start]){
        if (start == BS) {
            if (std::find(Cycle.begin(), Cycle.end(), i) != Cycle.end()) {
                continue;
            }
            else if (vis[i] == false){
                return make_tree(g, vis, trees, cur, i, Cycle, BS);
            }
        }
        else{
            if (std::find(Cycle.begin(), Cycle.end(), i) != Cycle.end() && i != BS) {
                return false;
            }
            else if (vis[i] == false){
                return make_tree(g, vis, trees, cur, i, Cycle, BS);
            }
        }
    }
    return true;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph(n + 1);

    int x, y;
    for (int i = 0; i < m; i++) {
        std::cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    for (auto &i : graph){
        std::sort(i.begin(), i.end());
    }

    std::vector<int> visited(n + 1, -1);
    std::vector<int> Cycle;
    bool state = false;
    for (int i = 1; i < n + 1; i++) {
        if (visited[i] == -1) {
            DFS(i, graph, visited, -1, Cycle, state);

            if (state) {
                break;
            }
        }
    }

    if (Cycle.empty()){
        std::cout << "EUCLID";
        return 0;
    }

    // проверка на деревья

    std::fill(visited.begin(), visited.end(), false);

    std::vector<std::vector<int>> trees(Cycle.size());

    for (auto i : Cycle){
        visited[i] = 1;
    }

    int c = 0;
    bool tmp;

    for (int i = 0; i < Cycle.size(); ++i){
        tmp = make_tree(graph, visited, trees, c, Cycle[i], Cycle, Cycle[i]);
        if(!tmp){
            std::cout << "EUCLID";
            return 0;
        }
        c++;
    }

    visited.erase(visited.begin());
    for (auto i : visited){
        if (i == 0){
            std::cout << "EUCLID";
            return 0;
        }
    }

    std::cout << "ARCHIMEDES";

    return 0;
}
/*
10 10
1 2
2 3
3 4
4 5
5 6
5 7
7 8
8 10
10 9
6 1

14 13
1 2
2 3
3 14
3 4
4 5
5 6
6 10
10 11
6 7
7 8
12 13
8 9
9 1


6 7
6 3
6 4
5 1
2 5
1 4
5 4
1 2

12 13
1 2
2 3
3 12
3 4
4 5
5 6
6 10
10 11
6 7
7 8
8 9
9 1
5 11

4 3
1 2
2 3
1 3

4 5
1 2
2 3
1 3
4 3
4 1

12 13
1 2
2 3
3 12
3 4
4 5
5 11
11 10
10 6
6 7
7 8
8 9
9 1
5 6
*/