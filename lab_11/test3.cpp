#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool myComp(pair<int, pair<int, int>> &a, pair<int, pair<int, int>> &b) {
    return a.first > b.first;
}

int find(int v, vector<int> &id) {
    while (v != id[v])
        v = id[v];
    return v;
}

void merge(int a, int b, vector<int> &id, vector<int> &rank) {
    a = find(a, id);
    b = find(b, id);
    if (a != b) {
        id[b] = a;

    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> id(n + 1);
    vector<int> rank(n + 1, 0);
    vector<pair<int, pair<int, int>>> g(m);
    for (int i = 0; i < m; ++i) {
        int a, b, h;
        cin >> a >> b >> h;
        g[i] = {h, {a, b}};
    }

    sort(g.begin(), g.end(), myComp);

    for (int i = 1; i <= n; ++i)
        id[i] = i;

    long long res = 0;
    for (int i = 0; i < m; ++i) {
        int a = g[i].second.first;
        int b = g[i].second.second;
        int h = g[i].first;

        if (find(a, id) != find(b, id)) {
            res += h;
            merge(a, b, id, rank);
        }
    }
    cout << res;
}