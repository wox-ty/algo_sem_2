#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include "string"
#include "iostream"


int find_string(std::vector<std::string> &g, std::string &a){
    for (int i = 0; i < g.size(); ++i) {
        if (g[i] == a){
            return i;
        }
    }
    return -1;
}

std::vector<int> in;
std::vector<int> up;
int counter = 0;


void DFS(std::vector<std::vector<int>> &g, int start, int parent, std::vector<std::pair<int, int>> &a) {
    in[start] = up[start] = counter++;

    for (auto &i: g[start]) {
        if (i == parent) {
            continue;
        }
        if (in[i] == -1) {
            DFS(g, i, start, a);
            up[start] = std::min(up[start], up[i]);
            if (up[i] > in[start]) {
                a.emplace_back(std::min(start, i), std::max(i, start));
            }
        } else {
            up[start] = std::min(up[start], in[i]);
        }
    }
}

void Find_Bridges(std::vector<std::vector<int>> &g, std::vector<std::pair<int, int>> &a) {
    for (int i = 0; i < g.size(); ++i) {
        if (in[i] == -1) {
            DFS(g, i, -1, a);
        }
    }
}

int BFS(std::vector<std::vector<int>> &g, int start, std::vector<int> &gv){

    std::vector<int> visited(g.size(), -1);
    std::vector<int> dist(g.size(), 0);

    std::queue<int> q;
    gv[start] = 1;
    q.push(start);
    visited[start] = 1;

    int c = 0;
    while (!q.empty()){
        int tmp = q.front();
        q.pop();
        c++;

        for (auto &i : g[tmp]){
            if(visited[i] == -1 && gv[i] == -1){
                dist[i] = c;
                visited[i] = 1;
                q.push(i);
            }
        }
    }

    int sum = 0;
    for (int i = 0; i < dist.size(); ++i) {
        sum += dist[i];
    }

    return sum;
}

int main(){
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> strings(n);
    std::vector<std::vector<int>> graph(n);


    for (int i = 0; i < n; ++i) {
        std::cin >> strings[i];
    }


    std::string s1, s2;
    int tmp1, tmp2;
    for (int i = 0; i < m; ++i) {
        std::cin >> s1 >> s2;
        tmp1 = find_string(strings, s1);
        tmp2 = find_string(strings, s2);
        graph[tmp1].push_back(tmp2);
        graph[tmp2].push_back(tmp1);
    }

    in.assign(n, -1);
    up.assign(n, -1);
    std::vector<std::pair<int, int>> ans;

    Find_Bridges(graph, ans);
    std::sort(ans.begin(), ans.end());

    std::vector<std::vector<int>> graph_v2(n);

    for (int i = 0; i < ans.size(); ++i) {
        graph_v2[ans[i].first].push_back(ans[i].second);
        graph_v2[ans[i].second].push_back(ans[i].first);
    }

    int sum = 0;
    std::vector<int> global_vis(n, -1);
    for (int i = 0; i < n; ++i) {
        if (graph_v2[i].empty()){
            continue;
        }
        sum += BFS(graph_v2, i, global_vis);
    }

    std::cout << sum;

    return 0;
}