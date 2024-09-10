#include <vector>
#include <queue>
#include "iostream"

struct point {
    int x;
    int y;
    int z;

    point() {
        x = -1;
        y = -1;
        z = -1;
    }

    point(int a, int b, int c) {
        x = a;
        y = b;
        z = c;
    }
};

bool bfs(point start, point finish, std::vector<std::vector<std::vector<int>>> &visited,
         std::vector<std::vector<std::vector<bool>>> &seen) {
    std::queue<point> q;

    visited[start.x][start.y][start.z] = 0;
    q.push(start);

    while (!q.empty()) {
        point current = q.front();
        q.pop();

        int x = current.x;
        int y = current.y;
        int z = current.z;

        seen[x][y][z] = true;

        if (current.x == finish.x && current.y == finish.y && current.z == finish.z) {
            std::cout << visited[finish.x][finish.y][finish.z];
            return true;
        }

        for (int i = -1; i <= 1; ++i) {
            if (x + i >= 0 && x + i < 101 /*&& y + j >= 0 && y + j < 100 && z + k >= 0 && z + k < 100*/) {
                if (visited[x + i][y][z] == 0 && x + i != x && !seen[x + i][y][z]) {
                    visited[x + i][y][z] = visited[x][y][z] + 1;
                    q.push(point(x + i, y, z));
                }
            }
        }
        for (int j = -1; j <= 1; ++j) {
            if (y + j >= 0 && y + j < 101) {
                if (visited[x][y + j][z] == 0 && y + j != y && !seen[x][y + j][z]) {
                    visited[x][y + j][z] = visited[x][y][z] + 1;
                    q.push(point(x, y + j, z));
                }
            }
        }

        for (int k = -1; k <= 1; ++k) {
            if (z + k >= 0 && z + k < 101) {
                if (visited[x][y][z + k] == 0 && z + k != z && !seen[x][y][z + k]) {
                    visited[x][y][z + k] = visited[x][y][z] + 1;
                    q.push(point(x, y, z + k));
                }
            }
        }
    }
    return false;
}


int main() {
    int K, E;
    std::cin >> K >> E;

    int x, y, z, h;
    std::cin >> x >> y >> z;
    point start(x, y, z);
    std::cin >> x >> y >> z;
    point finish(x, y, z);

    std::vector<std::vector<std::vector<int>>> visited(101,
                                                       std::vector<std::vector<int>>(101, std::vector<int>(101, 0)));
    std::vector<std::vector<std::vector<bool>>> seen(101, std::vector<std::vector<bool>>(101, std::vector<bool>(101,
                                                                                                                false)));

    for (int i = 0; i < K; ++i) {
        std::cin >> x >> y >> z >> h;
        for (int j = 0; j < h; ++j) {
            if (z + j > 101) {
                break;
            }
            seen[x][y][z + j] = true;
        }
    }

    if (bfs(start, finish, visited, seen)) {
        return 0;
    }


    std::cout << -1;
    return 0;
}
/*
0 474616
100 32 80
59 58 30


*/