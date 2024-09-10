#include <vector>
#include "algorithm"
#include "blazingio.hpp"

std::vector<int> av;
std::vector<int> bv;
std::vector<int> cv;
std::vector<bool> vis;

std::vector<std::vector<std::pair<int, int>>> child;

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
        return a.weight < b.weight;
    }

    bool operator==(const Edge a) const{
        return (a.weight == this->weight) && (a.end == this->end) && (a.begin == this->begin);
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

void kraskal(std::vector<Edge> &e, dsu &d){
    for (auto &tmp : e) {
        int a1 = d.find(tmp.begin);
        int a2 = d.find(tmp.end);
        if (a1 != a2){
            child[tmp.begin].emplace_back(tmp.end, tmp.weight);
            child[tmp.end].emplace_back(tmp.begin, tmp.weight);
            d.unite(tmp.begin, tmp.end);
        }
    }
}


void dfs(int start,std::vector<std::vector<std::pair<int, int>>> &c){
    vis[start] = true;

    for (auto i : c[start]){
        if (vis[i.first]) {
            continue;
        }
        dfs(i.first, c);
        av[start] = std::max(av[start], (bv[i.first] + i.second - cv[i.first]));
        bv[start] += cv[i.first];
    }

    av[start] += bv[start];
    cv[start] = std::max(av[start], bv[start]);
}

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

    av.assign(N, 0);
    bv.assign(N, 0);
    cv.assign(N, 0);
    vis.assign(N, false);


    dsu Dsu(N);
    std::sort(edges.begin(), edges.end(), Edge());
    child.resize(N);

    kraskal(edges, Dsu);


    int start;
    for (int i = 0; i < N; ++i) {
        if (child[i].size() == 1){
            start = i;
        }
    }

    dfs(start, child);

    std::cout << cv[start];

    return 0;
}