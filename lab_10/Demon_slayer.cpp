#include <vector>
#include <queue>
#include "iostream"

class Edge{
public:
    int begin;
    int end;
    int weight;

    Edge(){}

    Edge(int a, int b, int c){
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
    dsu(int n){
        parent.resize(n);
        rank.resize(n,0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x){
        if (parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y){
        int px = find(x);
        int py = find(y);

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
    std::vector<int> parent;
    std::vector<int> rank;
};


int main(){
    int N, M;
    std::cin >> N >> M;

    std::vector<Edge> edges;
    int a, b, c;
    for (int i = 0; i < M; ++i) {
        std::cin >> a >> b >> c;
        --a;
        --b;
        edges.emplace_back(a, b, c);
    }

    dsu DSU(N);

    int ans = 0;

    std::priority_queue q(edges.begin(), edges.end(), Edge());
    int v = q.size();
    for (int i = 0; i < v; ++i){
//        std::cout << q.top().begin << " " << q.top().end << " " << q.top().weight << "\n";
        Edge tmp = q.top();
        q.pop();

        int a1 = DSU.find(tmp.begin);
        int a2 = DSU.find(tmp.end);
        if (a1 != a2){
            DSU.unite(tmp.begin, tmp.end);
            ans += tmp.weight;
        }
    }

    std::cout << ans;

    return 0;
}