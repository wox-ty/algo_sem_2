#include <iostream>
#include <vector>
#include <string>

size_t p = 53;
size_t mod = 1000000009;
size_t n;

std::vector<size_t> power, pre_hash;

void pre_hashing(std::string &song) {
    power.resize(n + 1, 1);
    pre_hash.resize(n + 1, 0);

    for (size_t i = 1; i <= n; ++i)
        power[i] = (power[i - 1] * p) % mod;

    for (size_t i = 0; i < n; ++i) {
        pre_hash[i + 1] = (pre_hash[i] + (song[i] - 'a' + 1) * power[i]) % mod;
    }
}


size_t get_hash(int l, int r) {
    size_t r_hash = pre_hash[r + 1];
    size_t l_hash = pre_hash[l];
    size_t hash = (r_hash + mod - (l_hash * power[r - l + 1] % mod)) % mod;
    return hash;
}


int main() {
    int N, M;
    std::cin >> N >> M;

    std::string song;
    std::cin >> song;
    n = song.size();

    pre_hashing(song);

    int res = 0;

    int start1, start2, len;
    for (int i = 0; i < M; ++i) {
        std::cin >> start1 >> start2 >> len;
        start1--;
        start2--;

        size_t h1 = get_hash(start1, start1 + len - 1);
        size_t h2 = get_hash(start2, start2 + len - 1);

        if (h1 == h2) {
            res++;
        }
    }

    std::cout << res;
    return 0;
}
