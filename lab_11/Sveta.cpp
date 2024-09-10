#include <iostream>
#include <vector>
#include <climits>
#include <queue>

const int INF = INT_MAX;
int flow = 0, cost = 0;


struct Edge {
    int from, to, capacity, price;
    Edge(int f, int t, int c, int p){
        from = f;
        to = t;
        capacity = c;
        price = p;
    }
};

int siz;
std::vector<std::vector<int>> g;
std::vector<Edge> edges;

bool SPFA(int start, int t, std::vector<int>& dist, std::vector<int>& parent) {
    dist.assign(siz, INF);
    dist[start] = 0;
    parent.assign(siz, -1);
    std::vector<bool> inq(siz, false);

    std::queue<int> q;
    q.push(start);
    inq[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;

        for (int j : g[u]) {
            Edge& e = edges[j];
            if (e.capacity > 0 && dist[u] + e.price < dist[e.to]) {
                dist[e.to] = dist[u] + e.price;
                parent[e.to] = j;
                if (!inq[e.to]) {
                    q.push(e.to);
                    inq[e.to] = true;
                }
            }
        }
    }

    return dist[t] != INF;
}

void mcmf(int s, int t) {
    std::vector<int> parent(siz), dist(siz);

    while (SPFA(s, t, dist, parent)) {
        int cur_flow = INF;
        for (int v = t; v != s; v = edges[parent[v]].from) {
            cur_flow = std::min(cur_flow, edges[parent[v]].capacity);
        }

        flow += cur_flow;
        cost += cur_flow * dist[t];

        for (int v = t; v != s; v = edges[parent[v]].from) {
            edges[parent[v]].capacity -= cur_flow;
            edges[parent[v] ^ 1].capacity += cur_flow;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    --s;
    --t;
    siz = n;

    g.resize(n);

    for (int i = 0; i < m; ++i) {
        int u, v, capacity, price;
        std::cin >> u >> v >> capacity >> price;
        --u;
        --v;
        g[u].push_back(edges.size());
        edges.emplace_back(u, v, capacity, price);
        g[v].push_back(edges.size());
        edges.emplace_back(v, u, 0, -price);
    }

    mcmf(s, t);

    std::cout << flow << " " << cost;

    return 0;
}