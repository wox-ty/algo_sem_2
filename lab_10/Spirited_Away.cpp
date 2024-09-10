#include <vector>
#include <queue>
#include <stack>
#include "climits"
#include "algorithm"
#include "iostream"


#define INF INT_MAX
int mcolor = 0;
std::stack<int> s;
std::vector<int> colors;
int tin = 0;
std::vector<int> in;
std::vector<int> up;
std::vector<bool> vis;


void color(int v) {
    mcolor++;
    int l = -1;
    while (l != v && !s.empty()) {
        colors[s.top()] = mcolor;
        l = s.top();
        s.pop();
    }
}

void dfs(int v, std::vector<std::vector<int>> &g, int par) {
    tin++;
    s.push(v);
    in[v] = tin;
    up[v] = tin;
    vis[v] = true;
    for (auto i: g[v]) {
        if (vis[i] && i != par){
            up[v] = std::min(up[v], in[i]);
        }

        if (!vis[i]) {
            dfs(i, g, v);
            up[v] = std::min(up[v], up[i]);
            if (up[i] > in[v]) {
                color(i);
            }
        }
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, q;
    std::cin >> n >> m >> q;
    ++n;

    std::vector<std::vector<int>> graph(n);

    colors.resize(n);
    in.resize(n);
    up.resize(n);
    vis.assign(n, false);

    int a, b;
    for (int i = 0; i < m; ++i) {
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(0, graph, -1);
    color(0);

    for (int i = 0; i < q; ++i) {
        std::cin >> a >> b;
        std::cout << (colors[a] == colors[b] ? "YES\n" : "NO\n");
    }

    return 0;
}