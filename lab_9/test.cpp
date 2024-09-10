#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
const int INF = 999999999;

void XSearcher(vector <vector<int>> &planet, int i, int j, int num, int R, int C) {
    queue <pair<int, int>> que;
    que.push(make_pair(i, j));
    planet[i][j] = num;
    while (!que.empty()) {
        pair<int, int> P = que.front();
        que.pop();
        if (P.first < R - 1 && planet[P.first + 1][P.second] == 0) {
            que.push(make_pair(P.first + 1, P.second));
            planet[P.first + 1][P.second] = num;
        }
        if (P.first > 0 && planet[P.first - 1][P.second] == 0) {
            que.push(make_pair(P.first - 1, P.second));
            planet[P.first - 1][P.second] = num;
        }
        if (P.second < C - 1 && planet[P.first][P.second + 1] == 0) {
            que.push(make_pair(P.first, P.second + 1));
            planet[P.first][P.second + 1] = num;
        }
        if (P.second > 0 && planet[P.first][P.second - 1] == 0) {
            que.push(make_pair(P.first, P.second - 1));
            planet[P.first][P.second - 1] = num;
        }
    }
}

void GrahpMaker(vector <vector<int>> planet, vector <vector<int>> &graph, int i, int j, int num2, int R, int C) {
    queue <pair<pair<int, int>, int>> que;
    que.push(make_pair(make_pair(i, j), 0));
    planet[i][j] = 0;
    while (!que.empty()) {
        pair<pair<int, int>, int> P = que.front();
        que.pop();
        if (P.first.first < R - 1 && planet[P.first.first + 1][P.first.second] == -1) {//вниз
            que.push(make_pair(make_pair(P.first.first + 1, P.first.second), P.second + 1));
            planet[P.first.first + 1][P.first.second] = 0;
        }
        if (P.first.first < R - 1 && planet[P.first.first + 1][P.first.second] > 0 &&
            planet[P.first.first + 1][P.first.second] != num2) {
            int number_of_hill = planet[P.first.first + 1][P.first.second] - 1;
            bool flag = false;
            if (graph[num2 - 1][number_of_hill] != 333) {
                if (graph[num2 - 1][number_of_hill] > P.second) {
                    graph[num2 - 1][number_of_hill] = P.second;
                    graph[number_of_hill][num2 - 1] = P.second;
                }
                flag = true;
            }
            if (!flag) {
                graph[num2 - 1][number_of_hill] = P.second;
                graph[number_of_hill][num2 - 1] = P.second;
            }
        }
        if (P.first.first > 0 && planet[P.first.first - 1][P.first.second] == -1) {//вверх
            que.push(make_pair(make_pair(P.first.first - 1, P.first.second), P.second + 1));
            planet[P.first.first - 1][P.first.second] = 0;
        }
        if (P.first.first > 0 && planet[P.first.first - 1][P.first.second] > 0 &&
            planet[P.first.first - 1][P.first.second] != num2) {
            int number_of_hill = planet[P.first.first - 1][P.first.second] - 1;
            bool flag = false;
            if (graph[num2 - 1][number_of_hill] != 333) {
                if (graph[num2 - 1][number_of_hill] > P.second) {
                    graph[num2 - 1][number_of_hill] = P.second;
                    graph[number_of_hill][num2 - 1] = P.second;
                }
                flag = true;
            }
            if (!flag) {
                graph[num2 - 1][number_of_hill] = P.second;
                graph[number_of_hill][num2 - 1] = P.second;
            }
        }
        if (P.first.second < C - 1 && planet[P.first.first][P.first.second + 1] ==
                                      -1) {//вправо            que.push(make_pair(make_pair(P.first.first,P.first.second+1), P.second+1));
            planet[P.first.first][P.first.second + 1] = 0;
        }
        if (P.first.second < C - 1 && planet[P.first.first][P.first.second + 1] > 0 &&
            planet[P.first.first][P.first.second + 1] != num2) {
            int number_of_hill = planet[P.first.first][P.first.second + 1] - 1;
            bool flag = false;
            if (graph[num2 - 1][number_of_hill] != 333) {
                if (graph[num2 - 1][number_of_hill] > P.second) {
                    graph[num2 - 1][number_of_hill] = P.second;
                    graph[number_of_hill][num2 - 1] = P.second;
                }
                flag = true;
            }
            if (!flag) {