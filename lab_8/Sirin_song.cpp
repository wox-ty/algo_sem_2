#include <vector>
#include <stack>
#include "algorithm"
#include "iostream"

void dfs(int start_node, const std::vector<std::vector<int>>& connected, std::vector<bool>& visited, std::stack<int>& stk, std::vector<int> &components) {
    stk.push(start_node);
    components.push_back(start_node);
    while (!stk.empty()) {
        int current_node = stk.top();
        stk.pop();

        if (!visited[current_node]) {
            visited[current_node] = true;

            for (int cur : connected[current_node]) {
                if (!visited[cur]) {
                    stk.push(cur);
                    components.push_back(cur);
                }
            }
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

std::vector<int> TopSort(std::vector<std::vector<int>>& adj_list, int num_nodes, std::vector<bool> &visited, std::stack<int> &stk) {

    for (int i = 1; i < num_nodes; ++i) {
        if (!visited[i]) {
            dfs_top(i, adj_list, visited, stk);
        }
    }

    std::vector<int> result;
    while (!stk.empty()) {
        result.push_back(stk.top());
        stk.pop();
    }
    return result;
}

int main() {
    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> graph(N + 1, std::vector<int>());
    std::vector<std::vector<int>> inverted_graph(N + 1, std::vector<int>());


    int a, b;
    for (int i = 0; i < M; ++i) {
        std::cin >> a >> b;
        graph[a].push_back(b);
        inverted_graph[b].push_back(a);
    }
    std::vector<int> ans;
    std::vector<bool> visited(N+1, false);
    std::stack<int> stk;
    ans = TopSort(inverted_graph, N+1, visited, stk);

    for (auto i : visited){
        i = false;
    }

    std::vector<int> cur_components;
    int cur_group;
    int group_counter = 0;
    std::vector<int> group(N+1, -1);
    for (int i = 0; i < N; ++i) {
        if (visited[ans[i]] == false) {
            dfs(ans[i], graph, visited, stk, cur_components);


            cur_group = *std::min_element(cur_components.begin(), cur_components.end());
            for (auto k: cur_components) {
                group[k] = cur_group;
            }
            group_counter++;
            cur_components.clear();
            cur_group = -1;
        }
    }

    std::vector<std::pair<int, int>> ways;

    int second_group;
    for (int i = 1; i < N+1; ++i) {
        cur_group = group[i];
        for (auto j : graph[i]) {
            second_group = group[j];
            if (cur_group != second_group){
                ways.emplace_back(cur_group, second_group);
            }
        }
    }

    std::sort(ways.begin(), ways.end());



    int counter = 0;
    int size = ways.size();
    for (int i = size; i > 0; --i) {
        if (ways[i-1] == ways[i]){
            ways.erase(ways.end() - counter);
        }
        else{
            ++counter;
        }
    }

    std::cout << group_counter << " " << ways.size() << "\n";
    for (auto i : ways){
        std::cout << i.first << " " << i.second << "\n";
    }


    return 0;
}
/*
7 7
1 7
2 3
3 1
1 4
1 2
4 5
5 6

5 8
1 4
1 5
2 3
3 2
4 3
5 1
5 4
4 2

3 1
1 2

4 4
1 4
1 3
2 3
3 2

4 3
1 4
2 3
3 2

12 19
1 8
7 1
8 2
7 2
2 10
7 5
10 5
8 7
11 9
12 10
3 10
12 6
5 3
4 9
3 11
12 3
6 11
6 4
9 6

22 37
10 7
8 4
3 8
13 19
3 14
13 12
12 16
16 17
12 18
1 10
10 1
1 2
2 1
9 2
2 9
7 11
11 7
8 5
5 8
9 5
5 9
3 15
15 3
15 22
22 15
20 21
21 20
9 6
6 9
16 20
20 16
11 6
6 11
19 15
15 19
11 19
19 11
*/