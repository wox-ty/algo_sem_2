#include "iostream"
#include "vector"
#include "algorithm"
#include "queue"

int search(std::vector<int> &vec, int target){
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == target){
            return i;
        }
    }
    return -1;
}

std::vector<int> Gay_shep(int n, std::vector<std::vector<int>> &cats, std::vector<std::vector<int>> &mans) {
    std::vector<int> cat_pair(n, -1);
    std::vector<int> man_pair(n, -1);

    std::priority_queue<int, std::vector<int>, std::greater<>> pq;

    for (int i = 0; i < n; ++i) {
        pq.push(i);
    }

    while (!pq.empty()) {
        int c;
        c = pq.top();
        pq.pop();

        for (auto m: cats[c]) {
            if (man_pair[m] == -1) {
                man_pair[m] = c;
                cat_pair[c] = m;
                break;
            } else {
                int _new;
                _new = search(mans[m], c);

                int prev;
                prev = search(mans[m], man_pair[m]);

                if (_new < prev) {
                    pq.push(man_pair[m]);
                    man_pair[m] = c;
                    cat_pair[c] = m;
                    break;
                }
            }
        }
    }

    return cat_pair;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> cats(n);
    std::vector<std::vector<int>> mans(n);

    int a;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a;
            cats[i].push_back(a);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a;
            mans[i].push_back(a);
        }
    }

    std::vector<int> ans;
    ans = Gay_shep(n, cats, mans);

    for (int i = 0; i < ans.size(); ++i) {
        std::cout << i << ' ' << ans[i] << '\n';
    }

    return 0;
}
