#include <vector>
#include <queue>
#include "algorithm"
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

long long kraskal(std::priority_queue<Edge, std::vector<Edge>, Edge> &q, dsu &d, std::vector<Edge> &mst){
    long long ans = 0;

    while (!q.empty()) {
        Edge tmp = q.top();
        q.pop();

        long long a1 = d.find(tmp.s);
        long long a2 = d.find(tmp.f);
        if (a1 != a2){
            mst.push_back(tmp);
            d.unite(tmp.s, tmp.f);
            ans += tmp.w;
        }
    }

    return ans;
}

long long lca(long long v, long long u){
    
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


    std::vector<Edge> MST;
    dsu DSU(n);
    std::priority_queue pq(graph.begin(), graph.end(), Edge());
    long long mst_sum = kraskal(pq, DSU, MST);
    long long copy_sum;
    long long largest;
    std::vector<Edge> TMPST;
    for (int i = 0; i < m; ++i) {
        if (std::find(MST.begin(), MST.end(), graph[i]) != MST.end()){
            std::cout << mst_sum << "\n";
        }
        else {
            Edge cur = graph[i];

            copy_sum = mst_sum;
            TMPST = MST;
            TMPST.push_back(cur);
            copy_sum += cur.w;

            // бин подъём
            largest =  lca(cur.s, cur.f);

            copy_sum -= largest;
            std::cout << copy_sum << "\n";
        }
    }


    return 0;
}