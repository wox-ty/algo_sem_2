#include <vector>
#include "algorithm"
#include "iostream"
//#include "blazingio.hpp"

std::vector<int> cx = {-1, 0, 1, 0};
std::vector<int> cy = {0, 1, 0, -1};
std::vector<int> matching;
std::vector<bool> vis;
int ans = 0;

bool dfs(int start, std::vector<std::vector<int>> &g){
    if(vis[start]){
        return false;
    }
    vis[start] = true;
    for (auto i : g[start]){
        if (matching[i] == -1 || dfs(matching[i], g)){
            matching[i] = start;
            return true;
        }
    }
    return false;
}

void kun(std::vector<std::vector<int>> &g){
    matching.assign(g.size(), -1);
    for (int i = 0; i < g.size(); ++i) {
        vis.assign(g.size(), false);
        dfs(i, g);
    }
//    for (int i = 0; i < g.size(); ++i) {
//        if (matching[i] != -1){
//            std::cout << matching[i] << " " << i << "\n";
//        }
//    }
    for (int i = 0; i < g.size(); ++i) {
        if (matching[i] != -1){
            ans += 2;
        }
    }
}

int main() {
    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> map(N, std::vector<int>(M, -1));
    std::vector<std::vector<int>> graph(N*M);


    int Q;
    std::cin >> Q;

    int a, b;
    for (int i = 0; i < Q; ++i) {
        std::cin >> a >> b;
        --a;
        --b;
        map[a][b] = 1;
    }

    std::vector<std::vector<int>> colors(N, std::vector<int>(M, -1));

    int h1 = 0;
    int h2 = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            colors[i][j] = ((i % 2) ^ (j % 2));
            (colors[i][j] == 1 ? h1++ : h2++);
        }
    }

    int cur_m_h = (h1 < h2 ? 1 : 0);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (map[i][j] == -1  && colors[i][j] == cur_m_h) {
                for (int k = 0; k < 4; ++k) {
                    int tmp_c1 = i + cy[k];
                    int tmp_c2 = j + cx[k];
                    if (tmp_c1 >= 0 && tmp_c1 < N && tmp_c2 >= 0 && tmp_c2 < M) {
                        if (map[tmp_c1][tmp_c2] == -1) {
                            graph[j + (i * (M))].push_back(tmp_c2 + (tmp_c1 * (M)));
                        }
                    }
                }
            }
        }
    }

    kun(graph);

    std::cout << ans;

    return 0;
}
/*
2 10
0

3 4
3
1 2
1 3
3 4
*/