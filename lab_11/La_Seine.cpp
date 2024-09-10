#include <iostream>
#include <vector>
#include <queue>
#include <climits>

const int INF = INT_MAX;

int global_n;
std::vector<std::vector<int>> g;
std::vector<int> visited;
std::vector<std::vector<int>> graph_ls;
std::vector<int> dist;
std::vector<int> pairN, pairK;

int search(std::vector<int> &vec, int target)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == target)
        {
            return i;
        }
    }
    return -1;
}

void dfs_res(int start)
{
    if (visited[start])
        return;
    visited[start] = true;
    for (auto i : g[start])
    {
        dfs_res(i);
    }
}

bool dfs(int n)
{
    if (n != NULL)
    {
        for (int k : graph_ls[n])
        {
            if (dist[pairK[k]] == dist[n] + 1 && dfs(pairK[k]))
            {
                pairK[k] = n;
                pairN[n] = k;
                return true;
            }
        }
        dist[n] = INF;
        return false;
    }
    return true;
}

bool bfs()
{
    std::queue<int> q;
    for (int n = 1; n < pairN.size(); ++n)
    {
        if (pairN[n] == NULL)
        {
            dist[n] = 0;
            q.push(n);
        }
        else
        {
            dist[n] = INF;
        }
    }
    dist[NULL] = INF;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (dist[u] < dist[NULL])
        {
            for (int k : graph_ls[u])
            {
                if (dist[pairK[k]] == INF)
                {
                    dist[pairK[k]] = dist[u] + 1;
                    q.push(pairK[k]);
                }
            }
        }
    }
    return (dist[NULL] != INF);
}

void hopcroftKarp()
{
    while (bfs())
    {
        for (int n = 1; n < pairN.size(); ++n)
        {
            if (pairN[n] == NULL && dfs(n))
            {
            }
        }
    }

    for (int i = 0; i < pairN.size(); ++i)
    {
        if (pairN[i] != NULL)
        {
            g[i - 1].erase(g[i - 1].begin() + search(g[i - 1], pairN[i] + global_n - 1));
        }
    }

    for (int i = 0; i < pairK.size(); ++i)
    {
        if (pairK[i] != NULL)
        {
            g[i + global_n - 1].push_back(pairK[i] - 1);
        }
    }

    for (int i = 1; i < pairN.size(); ++i)
    {
        if (pairN[i] == NULL)
        {
            dfs_res(i - 1);
        }
    }
}

int main()
{
    int N, K, M;
    std::cin >> N >> K >> M;

    graph_ls.resize(N + 1);
    dist.resize(N + 1);
    pairN.resize(N + 1);
    pairK.resize(K + 1);

    visited.assign(N + K, false);
    g.resize(N + K);

    global_n = N;

    for (int i = 0; i < M; ++i)
    {
        int n, k;
        std::cin >> n >> k;
        g[n - 1].push_back(k + N - 1);
        graph_ls[n].push_back(k);
    }

    hopcroftKarp();

    int rl = 0;
    int rm = 0;
    for (int i = 0; i < N; ++i)
    {
        if (!visited[i])
        {
            rl++;
        }
    }
    for (int i = 0; i < K; ++i)
    {
        if (visited[N + i])
        {
            rm++;
        }
    }

    std::cout << rl << '\n';
    for (int i = 0; i < N; ++i)
    {
        if (!visited[i])
        {
            std::cout << i + 1 << ' ';
        }
    }
    std::cout << '\n';
    std::cout << rm << '\n';
    for (int i = 0; i < K; ++i)
    {
        if (visited[N + i])
        {
            std::cout << i + 1 << ' ';
        }
    }

    return 0;
}