#include <vector>
#include <algorithm>
#include <queue>
#include "iostream"

struct Edge{
    long long s;
    long long f;
    long long w;
    long long t;
    long long state;

    Edge(){}

    Edge(long long a, long long b, long long c, long long d, long long g){
        s = a;
        f = b;
        w = c;
        t = d;
        state = g;
    }

    bool operator()(const Edge a, const Edge b){
        return a.w > b.w;
    }

    bool operator==(const Edge a) const{
        return (a.w == this->w) && (a.f == this->f) && (a.s == this->s) && (a.t == this->t);
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

long long kraskal(std::priority_queue<Edge, std::vector<Edge>, Edge> &q, dsu &d, std::vector<Edge> &u){
    long long ans = 0;

    while (!q.empty()) {
        Edge tmp = q.top();
        q.pop();

        long long a1 = d.find(tmp.s);
        long long a2 = d.find(tmp.f);
        if (a1 != a2){
            u.push_back(tmp);
            d.unite(tmp.s, tmp.f);
            ans += tmp.w;
        }
    }

    return ans;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long N, M, K;
    std::cin >> N >> M >> K;

    std::vector<Edge> graph;

    long long X, Y, S;
    for (long long i = 0; i < M; ++i) {
        std::cin >> X >> Y >> S;
        --X;
        --Y;
        graph.emplace_back(X, Y, S, 1, 0);
    }

    for (long long i = 0; i < K; ++i) {
        std::cin >> X >> Y >> S;
        --X;
        --Y;
        graph.emplace_back(X, Y, S, 2, 0);
    }

    dsu DSU(N);
    std::vector<Edge> MST;
    std::priority_queue pq(graph.begin(), graph.end(), Edge());
    long long res;

    res = kraskal(pq, DSU, MST);

//    for (auto i : MST){
//        graph.erase(std::remove(graph.begin(), graph.end(), i), graph.end());
//    }

    for (auto i : MST){
        if (i.t == 1){
            res -= i.w;
            std::find(graph.begin(), graph.end(), i)->state = 1;
        }
    }

    for (auto i : graph){
        if (i.t == 1 && i.state == 0){
            res -= i.w;
        }
    }

    std::cout << (res >= 0 ? res : 0);

    return 0;
}