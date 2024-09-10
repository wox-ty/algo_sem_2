#include <vector>
#include <queue>
#include "climits"
#include "algorithm"
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
        size_t = n;
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

    void clear(){
        for (int i = 0; i < size_t; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int size(){
        return size_t;
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;
    int size_t;
};

int kraskal1(std::priority_queue<Edge, std::vector<Edge>, Edge> &q, dsu &d, std::vector<Edge> &u){
    int ans = 0;

    while (!q.empty()) {
        Edge tmp = q.top();
        q.pop();

        int a1 = d.find(tmp.begin);
        int a2 = d.find(tmp.end);
        if (a1 != a2){
            u.push_back(tmp);
            d.unite(tmp.begin, tmp.end);
            ans += tmp.weight;
        }
    }

    return ans;
}

int kraskal2(std::priority_queue<Edge, std::vector<Edge>, Edge> &q, dsu &d){
    int ans = 0;
    while (!q.empty()) {
        Edge tmp = q.top();
        q.pop();

        int a1 = d.find(tmp.begin);
        int a2 = d.find(tmp.end);
        if (a1 != a2){
            d.unite(tmp.begin, tmp.end);
            ans += tmp.weight;
        }
    }

    return ans;
}


int main(){
    int N, M;
    std::cin >> N >> M;

    std::vector<Edge> graph(M);

    int a, b, h;
    for (int i = 0; i < M; ++i) {
        std::cin >> a >> b >> h;
        --a;
        --b;
        graph[i] = {a, b, h};
    }

    dsu Dsu(N);

    std::priority_queue q(graph.begin(), graph.end(), Edge());

    int sum_mst_1;
    std::vector<Edge> used_in_mst_1;
    sum_mst_1 = kraskal1(q, Dsu, used_in_mst_1);

    int sum_mst_2 = INT_MAX;
    for (auto &i: used_in_mst_1) {
        Dsu.clear();
        std::vector<Edge> cop = graph;
        cop.erase(std::find(cop.begin(), cop.end(), i));
        std::priority_queue copy(cop.begin(), cop.end(), Edge());
        int tmp_res = kraskal2(copy, Dsu);
        sum_mst_2 = std::min(sum_mst_2, tmp_res);
    }


    std::cout << sum_mst_1 << " " << sum_mst_2;

    return 0;
}