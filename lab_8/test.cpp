#include <vector>
#include <queue>
#include "algorithm"
#include "iostream"

int end_t;

bool BFS(int start, std::vector<std::vector<int>> &g, int h, std::vector<std::vector<std::pair<int, int>>> &con_cor,
         std::vector<std::pair<int, int>> &cs, int cur_cor) {
    std::vector<int> visited(g.size(), -1);
    std::queue<int> q;
    q.push(start);
    visited[start] = 1;

    while (!q.empty()) {
        int tmp = q.front();
        q.pop();
        if (tmp == end_t) {
            return true;
        }

        for (auto &i: g[tmp]) {
            if (tmp == start) {
                if (visited[i] == -1) {
                    for (auto &k: con_cor[i]) {
                        if (k.second == tmp && k.first == cur_cor) {
                            if (cs[k.first].first <= h && h <= cs[k.first].second) {
                                visited[i] = 1;
                                q.push(i);
                            }
                        }
                    }
                }
            } else {
                if (visited[i] == -1) {
                    for (auto &k: con_cor[i]) {
                        if (k.second == tmp) {
                            if (cs[k.first].first <= h && h <= cs[k.first].second) {
                                visited[i] = 1;
                                q.push(i);
                            }
                        }
                    }
                }
            }
        }

    }


    return false;
}

int BSA(int max_r, int ml, std::vector<std::vector<int>> &graph, std::vector<std::vector<std::pair<int, int>>> &con_cor,
        std::vector<std::pair<int, int>> &cs, int cur_cor) {
    int l = ml;
    int r = max_r;
    int mid;
    bool c = false;
    while (l <= r) {
        mid = l + (r - l) / 2;
        if (BFS(1, graph, mid, con_cor, cs, cur_cor)) {
            l = mid + 1;
            c = true;
        } else {
            r = mid - 1;
        }
    }

    if (!c) {
        return -10000;
    }
    return r;
}

bool BFS2(int start, std::vector<std::vector<int>> &g, int h, std::vector<std::vector<std::pair<int, int>>> &con_cor,
          std::vector<std::pair<int, int>> &cs, int cur_cor, int r) {
    std::vector<int> visited(g.size(), -1);
    std::queue<int> q;
    q.push(start);
    visited[start] = 1;

    while (!q.empty()) {
        int tmp = q.front();
        q.pop();
        if (tmp == end_t) {
            return true;
        }

        for (auto &i: g[tmp]) {
            if (tmp == start) {
                if (visited[i] == -1) {
                    for (auto &k: con_cor[i]) {
                        if (k.second == tmp && k.first == cur_cor) {
                            if (cs[k.first].first <= h && h <= cs[k.first].second) {
                                visited[i] = 1;
                                q.push(i);
                            }
                        }
                    }
                }
            } else {
                if (visited[i] == -1) {
                    for (auto &k: con_cor[i]) {
                        if (k.second == tmp) {
                            if (cs[k.first].first <= h && h <= cs[k.first].second && cs[k.first].first <= r &&
                                r <= cs[k.first].second) {
                                visited[i] = 1;
                                q.push(i);
                            }
                        }
                    }
                }
            }
        }

    }


    return false;
}

int
rev_BSA(int max_r, int ml, std::vector<std::vector<int>> &graph, std::vector<std::vector<std::pair<int, int>>> &con_cor,
        std::vector<std::pair<int, int>> &cs, int cur_cor, int rbd) {
    int l = ml;
    int r = max_r;
    int mid;
    bool c = false;
    while (l <= r) {
        mid = l + (r - l) / 2;
        if (BFS2(1, graph, mid, con_cor, cs, cur_cor, rbd)) {
            r = mid - 1;
            c = true;
        } else {
            l = mid + 1;
        }
    }

    if (!c) {
        return -10000;
    }
    return l;
}

void DFS(std::vector<std::vector<int>> &graph, std::vector<int> &vis, int start, int BS, int cur_cor, int h,
         std::vector<std::vector<std::pair<int, int>>> &con_cor,
         std::vector<std::pair<int, int>> &cs, std::vector<int> &ans, int end, bool &state) {
    if (start == end) {
        state = true;
        return;
    }
    if (vis[start] == -1) {
        vis[start] = 1;
        int tmp;

        for (auto &i: graph[start]) {
            if (vis[i] == -1) {
                if (start == BS) {
                    for (auto &k: con_cor[i]) {
                        if (k.first == cur_cor && k.second == start) {
                            if (cs[k.first].first <= h && h <= cs[k.first].second) {
                                DFS(graph, vis, i, BS, cur_cor, h, con_cor, cs, ans, end, state);
                                tmp = cs[k.first].first;
                                if (state) {
                                    ans.push_back(tmp);
                                    return;
                                }
                            }
                        }
                    }
                } else {
                    for (auto &k: con_cor[i]) {
                        if (k.second == start) {
                            if (cs[k.first].first <= h && h <= cs[k.first].second) {
                                DFS(graph, vis, i, BS, cur_cor, h, con_cor, cs, ans, end, state);
                                tmp = cs[k.first].first;
                                if (state) {
                                    ans.push_back(tmp);
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (!ans.empty()) {
            ans.pop_back();
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    end_t = n;

    int u, v;
    std::vector<std::vector<int>> graph(n + 1);
    std::vector<std::vector<std::pair<int, int>>> con_cor(n + 1);
    int counter = 1;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        if (std::find(graph[u].begin(), graph[u].end(), v) == graph[u].end()) {
            graph[u].push_back(v);
        }
        if (std::find(graph[v].begin(), graph[v].end(), u) == graph[v].end()) {
            graph[v].push_back(u);
        }
        con_cor[u].emplace_back(counter, v);
        con_cor[v].emplace_back(counter, u);
        counter++;
    }

    int l, r;
    int max_r = -1;
    std::vector<std::pair<int, int>> cors(m + 1);
    for (int i = 0; i < m; ++i) {
        std::cin >> l >> r;
        cors[i + 1] = std::make_pair(l, r);
        max_r = std::max(max_r, r);
    }

    max_r *= 2;

    int tmp;
    int ans = -1;
    std::vector<int> ls;
    std::vector<int> vis(n + 1, -1);
    int maxi = -1;
    int prev;
    int cur_l;
    int bsans;
    for (auto &i: con_cor[1]) {
        tmp = -1;
        cur_l = 0;
        for (auto &k: cors) {
            if (k.first != 0 && k.second != 0) {
                prev = tmp;
                bsans = BSA(max_r, k.first, graph, con_cor, cors, i.first);
                tmp = std::max(bsans, tmp);
                if (bsans > prev) {
                    cur_l = rev_BSA(tmp, k.first, graph, con_cor, cors, i.first, tmp);
                }
            }
        }
        if (tmp == -1) {
            tmp = -10000;
        }
//        if (tmp != -10000) {
//            DFS(graph, vis, 1, 1, i.first, tmp, con_cor, cors, ls, end_t, state);
//            for (auto &k: ls) {
//                maxi = std::max(maxi, k);
//            }
//        }
        ans = std::max(tmp - cur_l + 1, ans);
        std::fill(vis.begin(), vis.end(), -1);
        ls.clear();
        maxi = -1;
    }

    std::cout << ans;

    return 0;
}