#include <algorithm>
#include "iostream"
#include "vector"

struct Vertis{
    int number;
    std::vector<int> connected;
    int color;
    Vertis* parent;

    Vertis(){
        connected = std::vector<int>();
        color = -1;
        number = -1;
        parent = nullptr;
    };

    Vertis(int a){
        connected = std::vector<int>();
        color = -1;
        number = a;
        parent = nullptr;
    };
};

void DFS(std::vector<Vertis> &p, long start, std::vector<int> &ans){
    if (p[start].color == -1) {
        p[start].color = 0;
        for (long j = 0; j < p[start].connected.size(); ++j){
            Vertis tmp = p[p[start].connected[j]];
            if (tmp.color == -1){
                DFS(p, p[start].connected[j], ans);
            }
        }
        ans.push_back(start);
    }
}

void Top_sort(std::vector<Vertis> &p, std::vector<int> &ans){
    for (int i = 1; i < p.size(); ++i){
            DFS(p, i, ans);
    }
    std::reverse(ans.begin(), ans.end());
}

int main(){
    int N, M;
    std::cin >> N >> M;

    std::vector<Vertis> graph;
    graph.push_back(Vertis(-99));
    for (int i = 0; i < N; ++i){
        graph.push_back(Vertis(i+1));
    }
    std::vector<int> ans;
    int start, end;
    for (int i = 0; i < M; ++i){
        std::cin >> start >> end;
        graph[start].connected.push_back(end);
    }
    Top_sort(graph, ans);
    std::vector<std::pair<int, int>> ans_2;

    int c = 1;
    for (auto i : ans){
        ans_2.push_back(std::pair(i, c));
        ++c;
    }

    std::sort(ans_2.begin(), ans_2.end());

    for (auto i : ans_2){
        std::cout << i.second << " ";
    }

    return 0;
}