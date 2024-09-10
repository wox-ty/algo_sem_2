#include <vector>
#include <set>
#include "iostream"


int main() {
    int N, M;
    std::cin >> N >> M;

    std::vector<int> cards(N);
    for (int t = 0; t < N; ++t) {
        std::cin >> cards[t];
    }

    std::set<int> res;
    bool flag;
    int j = -1;
    int i = 0;
    while (j < N / 2) {
        flag = false;
        int cur_j = j;
        int cur_i = i;
        while (cur_j >= 0 && cur_i < cards.size()) {
            if (cards[cur_j] != cards[cur_i]) {
                flag = true;
                break;
            }
            --cur_j;
            ++cur_i;
        }
        ++j;
        ++i;
        if (flag) continue;
        res.insert(cards.size() - j);
    }

    for (auto possible: res) {
        std::cout << possible << ' ';
    }

    return 0;
}