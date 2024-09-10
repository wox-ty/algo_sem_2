//void Condensate_mountains(std::vector<std::vector<char>> &f, int sx, int sy, int cur_group,
//                          std::vector<std::vector<int>> &g_f) {
//    int h = f.size();
//    int w = f[0].size();
//
//    std::queue<std::pair<int, int>> q;
//    q.emplace(sy, sx);
//
//    g_f[sy][sx] = cur_group;
//
//    std::vector<int> dy = {-1, 0, 1, 0};
//    std::vector<int> dx = {0, 1, 0, -1};
//
//    while (!q.empty()) {
//        int cur_y = q.front().first;
//        int cur_x = q.front().second;
//        q.pop();
//
//        for (int i = 0; i < dy.size(); ++i) {
//            int tmp_y = cur_y + dy[i];
//            int tmp_x = cur_x + dx[i];
//
//            if (0 <= tmp_y && tmp_y < h && 0 <= tmp_x && tmp_x < w) {
//                if (f[tmp_y][tmp_x] == 'X') {
//                    if (g_f[tmp_y][tmp_x] == -1) {
//                        g_f[tmp_y][tmp_x] = cur_group;
//                        q.emplace(tmp_y, tmp_x);
//                    }
//                }
//            }
//        }
//    }
//}