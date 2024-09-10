#include <vector>
#include "iostream"

int N, M;

bool possible(std::vector<int>& pref_1, std::vector<int>& pref_2, int len) {
    for(int i = len; i <= N; i++) {
        int sum1 = pref_1[i] - pref_1[i - len];
        for(int j = len; j <= M; j++) {
            int sum2 = pref_2[j] - pref_2[j - len];
            if(sum1 == sum2)
                return true;
        }
    }
    return false;
}

int main() {
    std::cin >> N;

    std::vector<int> string_1(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> string_1[i];
    }

    std::cin >> M;

    std::vector<int> string_2(M);
    for (int i = 0; i < M; ++i) {
        std::cin >> string_2[i];
    }

    std::vector<int> pref_1(N+1, 0);
    std::vector<int> pref_2(M+1, 0);

    for (int i = 0; i < N; ++i) {
        pref_1[i+1] = pref_1[i] + string_1[i];
    }

    for (int i = 0; i < M; ++i) {
        pref_2[i+1] = pref_2[i] + string_2[i];
    }

    int left = 1, right = N + 1;
    while(left < right) {
        int mid = (left + right) / 2;
        if(possible(pref_1, pref_2, mid))
            left = mid + 1;
        else
            right = mid;
    }

    std::cout << (left - 1);

    return 0;
}
/*
4
1 2 3 4
4
2 4 1 3
*/