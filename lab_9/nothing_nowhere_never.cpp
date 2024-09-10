#include <vector>
#include "algorithm"
#include "iostream"

std::vector<int> in;
std::vector<int> up;
int counter = 0;


void DFS(std::vector<std::vector<int>> &g, int start, int parent, std::vector<std::pair<int, int>> &a) {
    in[start] = up[start] = counter++;

    for (auto &i: g[start]) {
        if (i == parent) {
            continue;
        }
        if (in[i] == -1) {
            DFS(g, i, start, a);
            up[start] = std::min(up[start], up[i]);
            if (up[i] > in[start]) {
                a.emplace_back(std::min(start, i), std::max(i, start));
            }
        } else {
            up[start] = std::min(up[start], in[i]);
        }
    }
}

void Find_Bridges(std::vector<std::vector<int>> &g, std::vector<std::pair<int, int>> &a) {
    for (int i = 1; i < g.size(); ++i) {
        if (in[i] == -1) {
            DFS(g, i, -1, a);
        }
    }
}


int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph(n + 1);
    int x, y;
    for (int i = 0; i < m; ++i) {
        std::cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    in.assign(n + 1, -1);
    up.assign(n + 1, -1);
    std::vector<std::pair<int, int>> ans;

    Find_Bridges(graph, ans);

    std::sort(ans.begin(), ans.end());

    for (auto &[f, s]: ans) {
        std::cout << f << " " << s << "\n";
    }

    return 0;
}