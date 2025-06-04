#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int vertex;
vector<vector<pair<int, int>>> adjList;

void bfs(vector<long> &result, long start)
{
    vector<bool> visited(vertex, false);
    queue<long> q;

    result.resize(vertex, -1);
    q.push(start);
    visited[start] = true;
    result[start] = 0;

    while (!q.empty())
    {
        long temp = q.front();
        q.pop();

        for (auto it : adjList[temp])
        {
            if (!visited[it.first])
            {
                q.push(it.first);
                visited[it.first] = true;
                result[it.first] = result[temp] + 1;
            }
        }
    }
}

int main()
{
    int n, m, l;
    long s;
    int v1, v2;
    int found = 0;

    cin >> n >> m >> l;
    cin >> s;

    vertex = n;
    adjList.assign(vertex, vector<pair<int, int>>());

    for (int i = 0; i < m; i++)
    {
        cin >> v1 >> v2;
        adjList[v1].push_back({v2, 1});
        adjList[v2].push_back({v1, 1});
    }

    for (long i = 0; i < n; i++)
    {
        sort(adjList[i].begin(), adjList[i].end());
    }

    vector<long> bfsResult;
    bfs(bfsResult, s);

    for (long i = 0; i < n; i++)
    {
        if (bfsResult[i] == l)
        {
            cout << i << " ";
            found = 1;
        }
    }

    if (found == 0)
    {
        cout << "Not Found" << endl;
    }

    return 0;
}

/*
Sample Input 0
6 5 2
0
0 1
1 2
2 3
3 4
4 5
Sample Output 0
2

Sample Input 1
4 2 2
0
1 2
2 3
Sample Output 1
Not Found
*/