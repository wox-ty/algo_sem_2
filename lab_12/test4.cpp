#include <vector>
#include "iostream"

int N, M;

int main(){
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

    std::vector<int> pref_1(N+1);
    std::vector<int> pref_2(M+1);

    pref_1[0] = 0;
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        sum = sum + string_1[i];
        pref_1[i+1] = sum;
    }

    pref_2[0] = 0;
    sum = 0;
    for (int i = 0; i < M; ++i) {
        sum = sum + string_2[i];
        pref_2[i+1] = sum;
    }

    for (int i = 0; i < N+1; ++i) {
        std::cout << pref_1[i] << ' ';
    }
    std::cout << "\n";
    for (int i = 0; i < M+1; ++i) {
        std::cout << pref_2[i] << ' ';
    }

    return 0;
}
