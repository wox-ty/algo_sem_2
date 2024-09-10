#include "iostream"
#include "string"
#include "vector"

std::vector<int> res;

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

void KMP(std::string &s, int start, std::vector<int> &prefix){
    int len = start - 1;
    for (int i = start; i < s.size(); ++i) {
        if (prefix[i] == len){
            res.push_back(i - start + 1 - len);
        }
    }
}

int main(){
    std::string T;
    std::string S;

    std::cin >> T >> S;

    std::string combined;
    combined = S + '~' + T;

    std::vector<int> prefix(combined.size(), 0);
    find_prefix(prefix, combined);

    KMP(combined, S.size()+1,prefix);

    std::cout << res.size() << "\n";
    for (auto &i : res){
        std::cout << i << ' ';
    }

    return 0;
}