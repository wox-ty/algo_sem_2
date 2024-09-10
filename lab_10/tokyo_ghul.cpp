#include <vector>
#include <queue>
#include "iostream"
//#include "blazingio.hpp"

struct Edge{
    long long s;
    long long f;
    long long w;

    Edge(){}

    Edge(long long a, long long b, long long c){
        s = a;
        f = b;
        w = c;
    }

    bool operator()(const Edge a, const Edge b){
        return a.w > b.w;
    }

    bool operator==(const Edge a) const{
        return (a.w == this->w) && (a.f == this->f) && (a.s == this->s);
    }
};

class dsu{
public:
    dsu(long long n){
        parent.resize(n);
        rank.resize(n,0);
        for (long long i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    long long find(long long x){
        if (parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(long long x, long long y){
        long long px = find(x);
        long long py = find(y);

        if (rank[px] > rank[py]){
            parent[py] = px;
            rank[px] = rank[py] + 1;
        }
        else{
            parent[px] = py;
            rank[py] = std::max(rank[py], rank[px] + 1);
        }
    }

private:
    std::vector<long long> parent;
    std::vector<long long> rank;
};

long long kraskal(std::priority_queue<Edge, std::vector<Edge>, Edge> &q, dsu &d){
    long long ans = 0;

    while (!q.empty()) {
        Edge tmp = q.top();
        q.pop();

        long long a1 = d.find(tmp.s);
        long long a2 = d.find(tmp.f);
        if (a1 != a2){
            d.unite(tmp.s, tmp.f);
            ans += tmp.w;
        }
    }

    return ans;
}

int main(){
//    std::ios::sync_with_stdio(false);
//    std::cin.tie(nullptr);
//    std::cout.tie(nullptr);

    long long n, m;
    std::cin >> n >> m;

    std::vector<Edge> graph;

    long long v, u, w;
    for (long long i = 0; i < m; ++i) {
        std::cin >> v >> u >> w;
        --v;
        --u;
        graph.emplace_back(v, u, w);
    }


    for (long long i = 0; i < m; ++i) {
        dsu DSU(n);
        std::priority_queue pq(graph.begin(), graph.end(), Edge());
        Edge cur = graph[i];
        long long res = 0;
        DSU.unite(cur.s, cur.f);
        res += cur.w;

        res += kraskal(pq, DSU);
        std::cout << res << "\n";
    }


    return 0;
}