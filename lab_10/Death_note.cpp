#include <vector>
#include <stack>
#include <algorithm>
#include <list>
#include "iostream"

bool state;
int val;


void dfs(std::vector<std::list<int>> &g, std::vector<int> &vis, int start, int color) {
    vis[start] = color;
    for (auto i: g[start]) {
        if (vis[i] == -1) {
            vis[i] = color;
            dfs(g, vis, i, color);
        }
    }
}

bool check_euler(std::vector<std::list<int>> &g) {
    int odd = 0;
    for (auto &i: g) {
        if (i.size() % 2 != 0) {
            ++odd;
        }
    }
    if (odd > 0) {
        return false;
    }

    std::vector<int> vis(g.size(), -1);
    int color = 1;
    for (int i = 0; i < g.size(); ++i) {
        if (vis[i] == -1) {
            dfs(g, vis, i, color);
            break;
        }
    }
    for (int i = 0; i < g.size(); ++i) {
        if (!g[i].empty() && vis[i] == -1) {
            return false;
        }
    }

    return true;
}

bool rem_one(int &a) {
    if (state && a == val) {
        state = false;
        return true;
    }
    return false;
}

std::vector<int> find_path(std::vector<std::list<int>> &g) {
    std::vector<int> res;
    std::stack<int> s;
    s.emplace(0);
    while (!s.empty()) {
        int tmp = s.top();
        bool check = false;
        if (!g[tmp].empty()) {
            int u = g[tmp].front();
            s.push(u);
            state = true;
            val = u;
            g[tmp].remove_if(rem_one);
            state = true;
            val = tmp;
            g[u].remove_if(rem_one);
            check = true;
        }

        if (!check) {
            res.push_back(tmp);
            s.pop();
        }
    }
    return res;
}


int main() {
    int N, M;
    std::cin >> N >> M;

    std::vector<std::list<int>> graph(N);

    int a, b;

    for (int i = 0; i < M; ++i) {
        std::cin >> a >> b;
        --a;
        --b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }


    if (!check_euler(graph)) {
        std::cout << ":(";
        return 0;
    }

    std::vector<int> ans;

    ans = find_path(graph);

    std::reverse(ans.begin(), ans.end());

    for (auto city: ans) {
        std::cout << city + 1 << " ";
    }

    return 0;
}
/*
6 11
1 2
2 4
2 5
2 3
3 4
5 4
3 5
6 4
5 6
3 6
6 1


10 11
1 2
2 5
3 1
3 4
5 4
6 4
6 7
4 9
7 10
9 8
8 10


10 11
1 2
2 5
3 1
6 4
5 4
3 4
6 7
4 9
7 10
9 8
8 10


10 14
1 2
2 5
3 5
3 4
5 4
5 9
6 4
1 3
6 7
4 9
4 10
7 10
9 8
8 10

3 6
1 2
2 3
3 1
1 2
2 3
3 1

3 6
3 2
2 3
1 2
3 2
2 3
1 2
*/