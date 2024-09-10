#include <vector>
#include <queue>
#include <map>
#include "iostream"
#include "algorithm"

struct Xgra {

    bool operator()(const std::pair<int, std::pair<int, int>> &a, const std::pair<int, std::pair<int, int>> &b) {
        return a.second < b.second;
    }
};

int LBS(std::vector<std::pair<int, std::pair<int, int>>> &d, std::pair<int, int> t) {
    int l = 0;
    int r = d.size() - 1;
    int res = -1;

    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (d[mid].second == t) {
            res = mid;
            r = mid - 1;
        } else if (d[mid].second < t) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return res;
}

int RBS(std::vector<std::pair<int, std::pair<int, int>>> &d, std::pair<int, int> t) {
    int l = 0;
    int r = d.size() - 1;
    int res = -1;

    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (d[mid].second == t) {
            res = mid;
            l = mid + 1;
        } else if (d[mid].second < t) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return res;
}

void BFS(std::vector<std::vector<int>> &g, std::vector<std::pair<int, std::pair<int, int>>> &cor,
         std::vector<std::pair<int, int>> &d, int height, std::map<std::pair<std::vector<int>, std::vector<int>>, int> &map) {
    std::vector<bool> visited(g.size(), false);
    std::queue<std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, int>> q;
    std::vector<int> path;
    std::vector<int> color;
    q.push(std::make_tuple(g[1], path, color, 1));
    visited[1] = true;

    while (!q.empty()){
        std::tuple<std::vector<int>, std::vector<int>, std::vector<int>, int> tmpr = q.front();
        q.pop();

        visited[std::get<3>(tmpr)] = true;
        if (std::get<3>(tmpr) == g.size()-1){
            map[std::make_pair(std::get<1>(tmpr), std::get<2>(tmpr))]++;
        }

        for (auto &i : std::get<0>(tmpr)){
            if (!visited[i]){
                int tmp1 = LBS(cor, std::make_pair(std::min(std::get<3>(tmpr), i), std::max(std::get<3>(tmpr), i)));
                int tmp2 = RBS(cor, std::make_pair(std::min(std::get<3>(tmpr), i), std::max(std::get<3>(tmpr), i)));
                for (int j = tmp1; j <= tmp2; ++j) {
                    if (height >= d[cor[j].first].first && height <= d[cor[j].first].second){
//                        visited[i] = true;
                        path = std::get<1>(tmpr);
                        path.push_back(i);
                        color = std::get<2>(tmpr);
                        color.push_back(j);
                        q.push(std::make_tuple(g[i], path, color, i));
                    }
                }
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n + 1);
    std::vector<std::pair<int, std::pair<int, int>>> coridor(m);
    int u, v;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        coridor[i].first = i;
        if (u > v) {
            coridor[i].second = std::make_pair(v, u);
        } else {
            coridor[i].second = std::make_pair(u, v);
        }
        if (std::find(graph[u].begin(), graph[u].end(), v) == graph[u].end()) {
            graph[u].push_back(v);
        }
        if (std::find(graph[v].begin(), graph[v].end(), u) == graph[v].end()) {
            graph[v].push_back(u);
        }
    }

    std::vector<std::pair<int, int>> door(m);
    int l, r;
    int min_l = 2147483647;
    int max_r = -2147483648;
    for (int i = 0; i < m; ++i) {
        std::cin >> l >> r;
        door[i] = std::make_pair(l, r);
        min_l = std::min(l, min_l);
        max_r = std::max(r, max_r);
    }

    std::sort(coridor.begin(), coridor.end(), Xgra());

    std::map<std::pair<std::vector<int>, std::vector<int>>, int> map;
    for (int i = min_l; i <= max_r; ++i) {
        BFS(graph, coridor, door, i, map);
    }

//    for (auto &i: map) {
//        for (auto &k: i.first.first) {
//            std::cout << k << " ";
//        }
//        std::cout << "| ";
//        for (auto &k: i.first.second) {
//            std::cout << k << " ";
//        }
//        std::cout << ": " << i.second << "\n";
//    }

    int c = -1;
    for (auto &i : map){
        c = std::max(c, i.second);
    }
    std::cout << c;

    return 0;
}