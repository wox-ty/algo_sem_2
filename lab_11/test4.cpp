#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<int>> adj, revAdj;
vector<bool> visited;
vector<int> color1, color2;

void dfs(int v, int c_color) {
    visited[v] = true;
    color1[v] = c_color;
    for (int u : adj[v]) {
        if (!visited[u])
            dfs(u, c_color);
    }
}

void dfs_banned(int v, int ban, int new_color) {
    visited[v] = true;
    color2[v] = new_color;
    for (int u : adj[v]) {
        if (!visited[u] && u != ban)
            dfs_banned(u, ban, new_color);
    }
}

bool in(std::vector<int> &vec, int target){
    for (int i : vec) {
        if (i == target){
            return true;
        }
    }
    return false;
}


int main() {
    int n, m;
    cin >> n >> m;

    adj.resize(n);
    visited.assign(n, false);
    color1.resize(n);
    color2.resize(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int c=0;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]){
            dfs(i, c);
            c++;
        }
    }

    std::fill(visited.begin(), visited.end(), false);

    int c2=0;
    for (int i = 0; i < n; ++i) {
        if (color1[i] == c2){
            dfs_banned(i, i, c2);
        }
        else{
            c2++;
        }
    }

    int ans = 0;
    std::vector<int> used;
    for (int i = 0; i < n; ++i) {
        if (color1[i] == color2[i] && !in(used, color1[i])){
            used.push_back(color1[i]);
        }
    }

    std::cout << used.size();

    return 0;
}
