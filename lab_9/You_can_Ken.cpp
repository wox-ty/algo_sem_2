#include <vector>
#include "iostream"

const unsigned long long BIG = 18446744073709551615;

std::vector<unsigned long long> DXTR(std::vector<std::vector<std::pair<unsigned long long, unsigned long long>>> &g, unsigned long long start) {
    std::vector<unsigned long long> dist(g.size(), BIG);
    dist[start] = 0;
    std::vector<unsigned long long> visited(g.size(), -1);

    unsigned long long unseen;
    for (unsigned long long i = 1; i < g.size(); ++i) {
        unseen = -1;
        for (unsigned long long j = 1; j < g.size(); ++j) {
            if (visited[j] == -1 && (unseen == -1 || dist[unseen] > dist[j])) {
                unseen = j;
            }
        }

        if (dist[unseen] == BIG || unseen == -1) {
            return std::vector<unsigned long long>(0);
        }

        visited[unseen] = 1;

        for (auto &[near, time]: g[unseen]) {
            if (dist[near] > dist[unseen] + time) {
                dist[near] = dist[unseen] + time;
            }
        }
    }
    return dist;
}

unsigned long long Sum(std::vector<unsigned long long> &a) {
    unsigned long long sum = 0;
    for (unsigned long long i = 1; i < a.size(); ++i) {
        sum += a[i];
    }
    return sum;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    unsigned long long n, m;
    std::cin >> n >> m;


    std::vector<std::vector<std::pair<unsigned long long, unsigned long long>>> graph(n + 1);
    unsigned long long x, y, l;
    for (unsigned long long i = 0; i < m; ++i) {
        std::cin >> x >> y >> l;

        graph[x].emplace_back(y, l);
        graph[y].emplace_back(x, l);
    }

    std::vector<std::vector<unsigned long long>> dist(n + 1);

    for (unsigned long long i = 1; i < n + 1; ++i) {
        dist[i] = DXTR(graph, i);
    }

    unsigned long long cur = -1;
    unsigned long long ans = -1;

    for (unsigned long long i = 1; i < n+1; ++i){
        if (cur == -1){
            cur = Sum(dist[i]);
            ans = i;
        }
        else if (cur > Sum(dist[i])){
            ans = i;
            cur = Sum(dist[i]);
        }
    }

    std::cout << ans;

    return 0;
}