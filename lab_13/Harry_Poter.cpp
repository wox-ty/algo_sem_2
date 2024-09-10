#include <vector>
#include "iostream"
#include "string"

void find_prefix(std::vector<int> &prefix, std::string &T){
    for (int i = 1; i < T.size(); ++i) {
        int k = prefix[i - 1];
        if (T[i] == T[k]) {
            prefix[i] = k + 1;
        } else {
            while (T[i] != T[k] && k > 0) {
                k = prefix[k - 1];
            }
            if (T[i] == T[k]) {
                prefix[i] = k + 1;
            }
        }
    }
}

int main() {
    std::string T;
    std::cin >> T;

    std::vector<int> prefix(T.size(), 0);
    find_prefix(prefix, T);

    for (auto i: prefix) {
        std::cout << i << ' ';
    }

    return 0;
}