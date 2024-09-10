#include "string"
#include "iostream"

std::string sub_string(std::string &s, int pos, int len){
    std::string res;
    if (len == -1){
        len = s.size()-pos;
    }
    for (int i = pos; i < pos+len; ++i) {
        res = res + s[i];
    }

    return res;
}

int main() {
    int N, M;
    std::cin >> N >> M;

    std::string song;
    std::cin >> song;

    int res = 0;

    int start_1, start_2, len;
    for (int i = 0; i < M; ++i) {
        std::cin >> start_1 >> start_2 >> len;
        start_1--;
        start_2--;

        if (sub_string(song, start_1, len) == sub_string(song, start_2, len)){
            res++;
        }
//        std::cout << sub_string(song, start_1, len) << '\n';
//        std::cout << sub_string(song, start_2, len) << '\n';
    }

    std::cout << res;

    return 0;
}
/*
индексация с 1

aaaaabaaaa
1 3 3   aaa  |  aaa
1 3 4   aaaa  |  aaab
1 1 1   a  |  a
7 4 1   a  |  a

10 2
abaaabaaab
2 3 3
3 7 3
*/