#include <vector>
#include <queue>
#include <stack>
#include "iostream"
#include "string"

//bool find_by_BFS(std::vector<std::vector<int>> &g, int start, int end){
//    std::vector<bool> vis(g.size(), false);
//    std::queue<std::vector<int>> q;
//    q.push(g[start]);
//    std::vector<int> tmp;
//    vis[start] = true;
//    while (!q.empty()){
//        tmp = q.front();
//        q.pop();
//
//        for (auto i : tmp){
//            if (!vis[i]){
//                q.push(g[i]);
//                vis[i] = true;
//                if (i == end){
//                    return true;
//                }
//            }
//        }
//    }
//    return false;
//}

void DFS(std::vector<std::vector<int>> &g, int start, int num, std::vector<int> &f){
    f[start] = num;
    for (auto i : g[start]){
        if (f[i] == -1){
            DFS(g, i, num, f);
        }
    }
}

void dfs_top(int node, std::vector<std::vector<int>>& connected, std::vector<bool>& visited, std::stack<int>& stk) {
    visited[node] = true;

    for (int cur : connected[node]) {
        if (!visited[cur]) {
            dfs_top(cur, connected, visited, stk);
        }
    }

    stk.push(node);
}

std::vector<int> TopSort(std::vector<std::vector<int>>& connected, int size, std::vector<bool> &visited, std::stack<int> &stk) {

    for (int i = 1; i < size; ++i) {
        if (!visited[i]) {
            dfs_top(i, connected, visited, stk);
        }
    }

    std::vector<int> result;
    while (!stk.empty()) {
        result.push_back(stk.top());
        stk.pop();
    }
    return result;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    std::string input, oper;
    int tmp, space1, space2, i1, i2;
    std::vector<std::vector<int>> graph (n*2 + 1);
    std::vector<std::vector<int>> inv_graph (n*2 + 1);
    std::cin.ignore();
    for (int i = 0; i < k; ++i) {
        std::getline(std::cin, input);
        if (input[0] == '!'){
//          A -> !A
            tmp = std::stoi(input.substr(1));
            graph[tmp].push_back(tmp+n);
            inv_graph[tmp+n].push_back(tmp);
        }
        else{
            space1 = input.find(' ', 0);
            space2 = input.find(' ', space1+1);
            oper = input.substr(space1+1, space2-space1-1);
            i1 = std::stoi(input.substr(0, space1));
            i2 = std::stoi(input.substr(space2));
            if (oper == "||"){
//              !A -> B и !B -> A
                graph[i1 + n].push_back(i2);
                graph[i2 + n].push_back(i1);
                inv_graph[i2].push_back(i1 + n);
                inv_graph[i1].push_back(i2 + n);
            }
            else if (oper == "->"){
//              A -> B и !B -> !A
                graph[i1].push_back(i2);
                graph[i2 + n].push_back(i1 + n);
                inv_graph[i2].push_back(i1);
                inv_graph[i1 + n].push_back(i2 + n);
            }
            else if (oper == "&"){
//              !A -> A и !B -> B
                graph[i1 + n].push_back(i1);
                graph[i2 + n].push_back(i2);
                inv_graph[i1].push_back(i1 + n);
                inv_graph[i2].push_back(i2 + n);
            }
            else if (oper == "^"){
//              !A -> B и !B -> A  ?*?  A -> !B и B -> !A
                graph[i1 + n].push_back(i2);
                graph[i2 + n].push_back(i1);
                graph[i1].push_back(i2 + n);
                graph[i2].push_back(i1 + n);
                inv_graph[i2].push_back(i1 + n);
                inv_graph[i1].push_back(i2 + n);
                inv_graph[i2 + n].push_back(i1);
                inv_graph[i1 + n].push_back(i2);
            }
        }
    }

    std::vector<bool> vis(n*2+1, false);
    std::vector<int> ans_top;
    std::stack<int> stack;
    ans_top = TopSort(inv_graph, n*2+1, vis, stack);

    int c = 0;
    std::vector<int> f(n*2+1, -1);
    for (auto i : ans_top) {
        if (f[i] == -1){
            DFS(graph, i, c, f);
            c++;
        }
    }

    for (int i = 1; i < n; ++i) {
        if (f[i] == f[(i+n)]){
            std::cout << "NO";
            return 0;
        }
    }
    std::cout << "YES";
    return 0;
}
/*
3 2
1 || 2
2412 -> 3312

2 3
!1
!2
11244 ^ 2412
*/

/*
A || B = !A -> B и !B -> A
A -> B = !A || B = A -> B и !B -> !A
A & B = !A -> A и !B -> B
A ^ B = (A || B)(!A || !B) = (!A -> B и !B -> A)(A -> !B и B -> !A)
!A = A -> !A
*/