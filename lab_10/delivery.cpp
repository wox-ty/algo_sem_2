#include <vector>
#include <queue>
#include "iostream"

class Edge{
public:
    unsigned long long begin;
    unsigned long long end;
    unsigned long long weight;

    Edge(){}

    Edge(unsigned long long a, unsigned long long b, unsigned long long c){
        begin = a;
        end = b;
        weight = c;
    }

    bool operator()(const Edge a, const Edge b){
        return a.weight > b.weight;
    }
};

class dsu{
public:
    dsu(unsigned long long n){
        parent.resize(n);
        rank.resize(n,0);
        for (unsigned long long i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    unsigned long long find(unsigned long long x){
        if (parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(unsigned long long x, unsigned long long y){
        unsigned long long px = find(x);
        unsigned long long py = find(y);

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
    std::vector<unsigned long long> parent;
    std::vector<unsigned long long> rank;
};


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    unsigned long long N, M;
    std::cin >> N >> M;

    std::vector<Edge> edges;
    unsigned long long a, b, c;
    for (unsigned long long i = 0; i < M; ++i) {
        std::cin >> a >> b >> c;
        --a;
        --b;
        edges.emplace_back(a, b, c);
    }

    dsu DSU(N);

    unsigned long long ans = 0;

    std::priority_queue q(edges.begin(), edges.end(), Edge());
    unsigned long long v = q.size();
    for (unsigned long long i = 0; i < v; ++i){
//        std::cout << q.top().begin << " " << q.top().end << " " << q.top().weight << "\n";
        Edge tmp = q.top();
        q.pop();

        unsigned long long a1 = DSU.find(tmp.begin);
        unsigned long long a2 = DSU.find(tmp.end);
        if (a1 != a2){
            DSU.unite(tmp.begin, tmp.end);
            ans += tmp.weight;
        }
    }

    std::cout << ans;

    return 0;
}