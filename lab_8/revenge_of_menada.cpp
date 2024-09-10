#include <vector>
#include "iostream"


struct Vertis{
    int number;
    std::vector<int> connected;
    int color;

    Vertis(){
        connected = std::vector<int>();
        color = -1;
        number = -1;
    };

    Vertis(int a){
        connected = std::vector<int>();
        color = -1;
        number = a;
    };
};

bool DFS(std::vector<Vertis> &p, long start, long end){
    if (p[start].color == -1) {
        p[start].color = 0;
        bool tmp = false;
        if (p[start].number == end) {
            p[start].color = -1;
            return true;
        }
        for (long j = 0; j < p[start].connected.size(); ++j) {
            if (p[p[start].connected[j]].color == -1) {
                tmp = DFS(p, p[start].connected[j], end);
                if (tmp){
                    break;
                }
            }
        }
        p[start].color = 1;
        return tmp;
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, q;
    std::cin >> n >> m >> q;

    int start, end;
    std::vector<Vertis> graph;
    graph.push_back(Vertis(-99));
    for (int i = 0; i < n; ++i){
        graph.push_back(Vertis(i+1));
    }
    for (int i = 0; i < m; ++i){
        std::cin >> start >> end;
        graph[start].connected.push_back(end);
    }

    bool c1, c2;
    for (int i = 0; i < q; ++i){
        std::cin >> start >> end;
        c1 = DFS(graph, start, end);
        for (int h = 1; h < n+1; ++h){
            graph[h].color = -1;
        }        c2 = DFS(graph, end, start);
        for (int h = 1; h < n+1; ++h){
            graph[h].color = -1;
        }
        std::cout << ((c1 & c2) ? "YES" : "NO") << "\n";
    }

    return 0;
}