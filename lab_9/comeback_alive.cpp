#include <vector>
#include "queue"
#include "climits"
#include "iostream"

const int BIG = INT_MAX;
int vis_all = -1;
std::vector<int> dy = {-1, 0, 1, 0};
std::vector<int> dx = {0, 1, 0, -1};
int H, W;


void Condensate_mountains(std::vector<std::vector<char>> &f, int sx, int sy, int cur_group,
                          std::vector<std::vector<int>> &g_f) {
    if (!(0 <= sy && sy < H && 0 <= sx && sx < W) || (f[sy][sx] != 'X') || (g_f[sy][sx] != -1)) {
        return;
    }
    g_f[sy][sx] = cur_group;
    for (int i = 0; i < dy.size(); ++i) {
        int tmp_y = sy + dy[i];
        int tmp_x = sx + dx[i];
        Condensate_mountains(f, tmp_x, tmp_y, cur_group, g_f);
    }
}

void make_graph(std::vector<std::vector<char>> &f, int sx, int sy, std::vector<std::vector<int>> &gr, int start,
                std::vector<std::pair<int, int>> &Mountains) {
    int h = f.size();
    int w = f[0].size();
    std::deque<std::pair<int, int>> q;
    q.emplace_back(sy, sx);
    std::vector<std::vector<int>> dist(h, std::vector<int>(w, BIG));
    dist[sy][sx] = 0;

    while (!q.empty()) {
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        q.pop_front();

        for (int i = 0; i < dy.size(); ++i) {
            int tmp_y = cur_y + dy[i];
            int tmp_x = cur_x + dx[i];

            if (0 <= tmp_y && tmp_y < h && 0 <= tmp_x && tmp_x < w) {
                if (f[tmp_y][tmp_x] == '.') {
                    continue;
                } else if (f[tmp_y][tmp_x] == 'X') {
                    if (dist[tmp_y][tmp_x] > dist[cur_y][cur_x]) {
                        dist[tmp_y][tmp_x] = dist[cur_y][cur_x];
                        q.emplace_front(tmp_y, tmp_x);
                    }
                } else if (f[tmp_y][tmp_x] == 'S') {
                    if (dist[tmp_y][tmp_x] > dist[cur_y][cur_x] + 1) {
                        dist[tmp_y][tmp_x] = dist[cur_y][cur_x] + 1;
                        q.emplace_back(tmp_y, tmp_x);
                    }
                }
            }
        }
    }

    for (int i = 0; i < Mountains.size(); ++i) {
        gr[start][i] = dist[Mountains[i].first][Mountains[i].second];
    }
}


void tsp(std::vector<std::vector<int>> &g, int **dp) {
    int size = g.size();

    int tmp;
    for (int mask = 1; mask < (1 << size); ++mask) {
        for (int i = 0; i < size; ++i) {
            tmp = mask;
            if ((tmp >> i) & 1) {
                for (int j = 0; j < size; ++j) {
                    tmp = mask;
                    if (i != j && ((tmp >> j) & 1)) {
                        dp[mask][i] = std::min(dp[mask][i], dp[mask ^ (1 << i)][j] + g[j][i]);
                    }
                }
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int R, C;
    std::cin >> R >> C;
    H = R;
    W = C;
    std::vector<std::vector<char>> field(R, std::vector<char>(C));

    std::vector<std::pair<int, int>> Mountains;

    std::vector<std::vector<int>> group_field(R, std::vector<int>(C, -1));

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            std::cin >> field[i][j];
            if (field[i][j] == 'X') {
                Mountains.emplace_back(i, j);
            }
        }
    }


    int cg = -1;
    int sx, sy;
    for (int i = 0; i < Mountains.size(); ++i) {
        sx = Mountains[i].second;
        sy = Mountains[i].first;
        if (group_field[sy][sx] == -1) {
            ++cg;
            Condensate_mountains(field, sx, sy, cg, group_field);
        }
    }

    cg++;

    std::vector<std::pair<int, int>> tmp_graph;

    for (int i = 0; i < cg; ++i) {
        for (int j = 0; j < Mountains.size(); ++j) {
            if (group_field[Mountains[j].first][Mountains[j].second] == i) {
                tmp_graph.emplace_back(Mountains[j].first, Mountains[j].second);
                break;
            }
        }
    }


    vis_all = (1 << cg) - 1;


    std::vector<std::vector<int>> graph_V2(cg, std::vector<int>(cg, BIG));

    for (int i = 0; i < cg; ++i) {
        sx = tmp_graph[i].second;
        sy = tmp_graph[i].first;
        make_graph(field, sx, sy, graph_V2, i, tmp_graph);
    }

    int **dp = new int *[(1 << cg)];
    for (int i = 0; i < (1 << cg); i++) {
        dp[i] = new int[cg];
    }

    for (int i = 0; i < (1 << cg); ++i) {
        for (int j = 0; j < cg; ++j) {
            dp[i][j] = BIG;
        }
    }

    for (int i = 0; i < cg; ++i) {
        dp[1 << i][i] = 0;
    }


    tsp(graph_V2, dp);
    int ans = BIG;
    for (int i = 0; i < cg; ++i) {
        ans = std::min(ans, dp[(1 << cg) - 1][i]);
    }
    std::cout << ans;

    return 0;
}