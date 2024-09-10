#include <vector>
#include <set>
#include "list"
#include "algorithm"
#include "iostream"

void not_tsp(std::vector<std::vector<bool>> &g, std::list<int> &o){
    for (int i = 0; i < g.size(); ++i) {
        int tmp = o.front();
        int tmp2 = *std::next(o.begin(), 1);


        if (g[tmp][tmp2] && g[tmp2][tmp]){
            o.pop_front();
            o.push_back(tmp);
        }
        else{
            for (auto j = o.begin(); j != o.end(); ++j){
                if (*j == tmp || *j == tmp2){
                    continue;
                }
                if (g[tmp][*j]){
                    if (g[tmp2][*std::next(j, 1)]){
                        std::reverse(std::next(o.begin(), 1), std::next(j, 1));
                        break;
                    }
                }
            }

            o.pop_front();
            o.push_back(tmp);
        }
    }
}

int main(){
    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<bool>> graph(N, std::vector<bool>(N, false));
    std::list<int> order/* = {3, 2, 0, 1}*/;
//    for (int i = 0; i < N; ++i)
//        order.push_back(i);


    int a, b;
    for (int i = 0; i < M; ++i) {
        std::cin >> a >> b;

        graph[a][b] = true;
        graph[b][a] = true;
        if (!(std::find(order.begin(), order.end(), a) != order.end())){
            order.push_back(a);
        }
        if (!(std::find(order.begin(), order.end(), b) != order.end())){
            order.push_back(b);
        }
    }

    not_tsp(graph, order);
//    std::cout << graph[0].find_b(2);
    for (auto i : order){
        std::cout << i << " ";
    }

    return 0;
}
/*
4 4
0 1
1 2
2 3
3 0
*/