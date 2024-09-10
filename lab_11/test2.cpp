#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

class Graph {
    int V;
    std::vector<std::vector<int>> adj;

    void dfs(int u, std::vector<int>& disc, std::vector<int>& low, std::stack<int>& st, std::vector<bool>& stacked, std::vector<int>& comp, int& time, std::vector<int>& result) {
        disc[u] = low[u] = ++time;
        st.push(u);
        stacked[u] = true;

        for (int v : adj[u]) {
            if (disc[v] == -1) {
                dfs(v, disc, low, st, stacked, comp, time, result);
                low[u] = std::min(low[u], low[v]);
            } else if (stacked[v]) {
                low[u] = std::min(low[u], disc[v]);
            }
        }

        if (low[u] == disc[u]) {
            int w = -1;
            std::vector<int> component;
            while (w != u) {
                w = st.top();
                st.pop();
                stacked[w] = false;
                component.push_back(w);
            }
            if (component.size() > 1) {
                for (int c : component) {
                    comp[c] = component.size(); // Записываем размер компоненты связности в вершине
                }
            }
        }
    }

public:
    Graph(int vertices) : V(vertices), adj(vertices) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int findSafeSegments() {
        std::vector<int> disc(V, -1), low(V, -1), comp(V, -1);
        std::vector<bool> stacked(V, false);
        std::stack<int> st;
        int time = 0;
        std::vector<int> result;

        for (int i = 0; i < V; ++i) {
            if (disc[i] == -1) {
                dfs(i, disc, low, st, stacked, comp, time, result);
            }
        }

        return *std::max_element(comp.begin(), comp.end()); // Находим размер наибольшей компоненты связности
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;

    Graph graph(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph.addEdge(u - 1, v - 1);
    }

    int result = graph.findSafeSegments();
    std::cout << result << std::endl;

    return 0;
}
