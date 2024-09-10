#include <vector>
#include "algorithm"
#include <iostream>

size_t p = 3;
size_t mod = 1000000007;

std::vector<std::vector<size_t>> prefix_hashes;
std::vector<size_t> power;

void pre_hashing(std::vector<std::vector<int>> &bm, int N, int M) {
    prefix_hashes.assign(N, std::vector<size_t>(M, 0));
    power.assign(M + 1, 1);

    for (int i = 1; i <= M; ++i) {
        power[i] = (power[i - 1] * p) % mod;
    }

    for (int i = 0; i < N; ++i) {
        prefix_hashes[i][0] = bm[i][0];
        for (int j = 1; j < M; ++j) {
            prefix_hashes[i][j] = (prefix_hashes[i][j - 1] * p + bm[i][j]) % mod;
        }
    }
}

size_t get_segment_hash(int row, int x1, int x2) {
    size_t r = prefix_hashes[row][x2];
    if (x1 == 0) {
        return r;
    }
    size_t l = prefix_hashes[row][x1 - 1] * power[x2 - (x1 - 1)] % mod;
    size_t hash = (r - l + mod) % mod;
    return hash;
}

bool compare(int x1, int y1, int x2, int y2, int x3, int y3, int x4,
             int y4) {
    int diff = std::abs(y2 - y1);
    int diff2 = std::abs(y4 - y3);
    int diff3 = std::abs(x1 - x2);
    int diff4 = std::abs(x3 - x4);

    if (diff != diff2 || diff3 != diff4) {
        return false;
    }

    for (int x = x1, _x = x3; x <= x2; ++x, ++_x) {
        size_t hash1 = get_segment_hash(x, y1, y2);
        size_t hash2 = get_segment_hash(_x, y3, y4);
        if (hash1 != hash2) {
            return false;
        }
    }

    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> big_matrix(N, std::vector<int>(M));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            std::cin >> big_matrix[i][j];
        }
    }

    pre_hashing(big_matrix, N, M);

    int Q;
    std::cin >> Q;

    int x1, y1, x2, y2, x3, y3, x4, y4;
    for (int i = 0; i < Q; ++i) {
        std::cin >> x1 >> y1 >> x2 >> y2;
        std::cin >> x3 >> y3 >> x4 >> y4;

        --x1;
        --y1;
        --x2;
        --y2;
        --x3;
        --y3;
        --x4;
        --y4;

        if (compare(x1, y1, x2, y2, x3, y3, x4, y4)) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}
/*
3 2
1 1
1 1
1 1
1
1 1 1 1
1 2 1 2

3 3
3 4 5
6 4 9
3 4 9
*/