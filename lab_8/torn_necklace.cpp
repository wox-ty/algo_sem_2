#include "iostream"
#include "vector"
#include "algorithm"

struct Vertis{
    long number;
    std::vector<long> connected;
    long color;
    long group;

    Vertis(){
        connected = std::vector<long>();
        color = -1;
        group = -1;
        number = -1;
    };

    Vertis(long a){
        connected = std::vector<long>();
        color = -1;
        group = -1;
        number = a;
    };
};

void DFS(std::vector<Vertis> &p, long start, long c_g){
    if (p[start].color == -1) {
        p[start].color = 0;
        for (long j = 0; j < p[start].connected.size(); ++j){
            if (p[p[start].connected[j] - 1].color == -1){
                DFS(p, p[start].connected[j] - 1, c_g);
            }
        }
        p[start].color = 1;
        p[start].group = c_g;
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::vector<Vertis> a;
    long N, M;

    std::cin >> N >> M;

    long v1, v2;
    for (long i = 0; i < N; ++i){
        a.push_back(Vertis(i+1));
    }

    for (long i = 0; i < M; ++i){
        std::cin >> v1 >> v2;

        if (!(std::find(a[v1-1].connected.begin(), a[v1-1].connected.end(), v2) != a[v1-1].connected.end())){
            a[v1-1].connected.push_back(v2);
        }
        if (!(std::find(a[v2-1].connected.begin(), a[v2-1].connected.end(), v1) != a[v2-1].connected.end())){
            a[v2-1].connected.push_back(v1);
        }
    }

    long counter = 0;
    for (long i = 0; i < N; ++i) {
        if (a[i].color == -1){
            counter++;
        }
        DFS(a, i, counter);
    }

    std::cout << counter;
    return 0;
}