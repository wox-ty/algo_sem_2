#include <vector>
#include "iostream"


void DFS(std::vector<std::vector<unsigned int>> &g, unsigned int v, int *parent) {
    for (auto &b: g[v]) {
        if (b != parent[v]) {
            parent[b] = v;
            DFS(g, b, parent);
        }
    }
}

void Prufer(std::vector<std::vector<unsigned int>> &g, int *deg, int *parent, unsigned int *res) {

    DFS(g, g.size() - 1, parent);

    unsigned int ptr = -1;
    for (unsigned int i = 0; i < g.size(); ++i) {
        deg[i] = g[i].size();
        if (deg[i] == 1 && ptr == -1) {
            ptr = i;
        }
    }

    unsigned int leaf = ptr;

    for (unsigned int i = 0; i < g.size() - 2; ++i) {
        unsigned int next = parent[leaf];
        res[i] = next;
        --deg[next];
        if (deg[next] == 1 && next < ptr) {
            leaf = next;
        } else {
            ++ptr;
            while (ptr < g.size() && deg[ptr] != 1) {
                ++ptr;
            }
            leaf = ptr;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    unsigned int n, m;
    std::cin >> n >> m;

    int parent[n];
    for (int i = 0; i < n; ++i) {
        parent[i] = -1;
    }
    int deg[n];


    std::vector<std::vector<unsigned int>> graph(n);
    unsigned int a, b;
    for (unsigned int i = 0; i < m; ++i) {
        std::cin >> a >> b;
        --a;
        --b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    unsigned int ans[n-2];
    Prufer(graph, deg, parent, ans);

    for (int i = 0; i < n-2; ++i) {
        std::cout << ans[i]+1 << ' ';
    }

    return 0;
}