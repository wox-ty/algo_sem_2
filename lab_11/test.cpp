#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<int>> adj, revAdj;
vector<bool> visited;
vector<int> component;
stack<int> order;

void dfs1(int v) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u])
            dfs1(u);
    }
    order.push(v);
}

void dfs2(int v, int comp) {
    visited[v] = true;
    component[v] = comp;
    for (int u : revAdj[v]) {
        if (!visited[u])
            dfs2(u, comp);
    }
}

int findSafeSections(int n) {
    visited.assign(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs1(i);
    }

    visited.assign(n, false);
    int numComponents = 0;

    while (!order.empty()) {
        int v = order.top();
        order.pop();
        if (!visited[v]) {
            dfs2(v, numComponents);
            numComponents++;
        }
    }

    return numComponents;
}

int main() {
    int n, m;
    cin >> n >> m;

    adj.resize(n);
    revAdj.resize(n);
    component.resize(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        adj[u].push_back(v);
        revAdj[v].push_back(u);
    }

    int numSafeSections = findSafeSections(n);
    cout << numSafeSections << endl;

    return 0;
}
