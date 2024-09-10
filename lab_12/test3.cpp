#include <vector>
#include "iostream"

long long N, M;

bool possible(std::vector<long long> &pref_1, std::vector<long long> &pref_2, long long len) {
    for (long long i = len; i <= N; i++) {
        long long sum1 = pref_1[i] - pref_1[i - len];
        for (long long j = len; j <= M; j++) {
            long long sum2 = pref_2[j] - pref_2[j - len];
            if (sum1 == sum2)
                return true;
        }
    }
    return false;
}

long long hashing(long long data) {
    data = ((data >> 13) ^ data) * 0x1b873593;
    data = ((data >> 13) ^ data) * 0x1b873593;
    data = (data >> 13) ^ data;
    return data;
}


int main() {
    std::cin >> N;

    std::vector<long long> string_1(N);
    for (long long i = 0; i < N; ++i) {
        std::cin >> string_1[i];
    }

    std::cin >> M;

    std::vector<long long> string_2(M);
    for (long long i = 0; i < M; ++i) {
        std::cin >> string_2[i];
    }

    std::vector<long long> pref_1(N + 1, 0);
    std::vector<long long> pref_2(M + 1, 0);

    std::vector<long long> h1(N);
    std::vector<long long> h2(M);

    for (long long i = 0; i < N; ++i) {
        long long a = hashing(string_1[i]);
        pref_1[i + 1] = a + pref_1[i];
        h1[i] = a;
    }
    for (long long i = 0; i < M; ++i) {
        long long a = hashing(string_2[i]);
        pref_2[i + 1] = a + pref_2[i];
        h2[i] = a;
    }

    long long max_len = 0;
    for (long long i = 0; i <= std::min(N, M); ++i) {
        if (possible(pref_1, pref_2, i)) {
            max_len = i;
        }
    }

    std::cout << max_len;

    return 0;
}
/*
3
1 2 3
7
6 7 3 1 8 9 2


3
15 5 20
6
6 8 10 10 20 3
ans: 3 а должен быть 1
*/