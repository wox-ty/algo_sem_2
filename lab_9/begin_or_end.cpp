#include <vector>
#include <stack>
#include "algorithm"
#include "iostream"

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
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, q;
    std::cin >> n >> m >> q;

    dsu DSU(n+1);
    std::vector<std::vector<int>> graph(n+1);
    int x, y;
    for (int i = 0; i < m; ++i) {
        std::cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    std::stack<std::tuple<char, int, int>> history;

    char command;
    int p1, p2;
    for (int i = 0; i < q; ++i) {
        std::cin >> command;
        if (command == '?'){
            std::cin >> p1 >> p2;
            history.emplace(command, p1, p2);
        }
        else{
            std::cin >> p1 >> p2;
            graph[p1].erase(std::find(graph[p1].begin(), graph[p1].end(), p2));
            graph[p2].erase(std::find(graph[p2].begin(), graph[p2].end(), p1));
            history.emplace(command, p1, p2);
        }
    }

    for (int i = 1; i < n+1; ++i) {
        for (auto &j : graph[i]){
            DSU.unite(i, j);
        }
    }

    std::vector<std::string> ans;

    while (!history.empty()){
        std::tuple<char, int, int> tmp = history.top();
        history.pop();
        command = std::get<0>(tmp);
        p1 = std::get<1>(tmp);
        p2 = std::get<2>(tmp);
        if (command == '?'){
            if (DSU.find(p1) == DSU.find(p2)){
                ans.push_back("YES\n");
            }
            else{
                ans.push_back("NO\n");
            }
        }
        else{
            DSU.unite(p1, p2);
        }
    }

    for (int i = ans.size()-1; i >= 0; --i) {
        std::cout << ans[i];
    }

    return 0;
}