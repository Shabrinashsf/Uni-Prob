// BELUM AC

#include <bits/stdc++.h>
using namespace std;

struct graph
{
    long vertexCount, edgeCount;
    vector<vector<pair<long, long>>> adjList;

    void init(long v)
    {
        vertexCount = v;
        edgeCount = 0;

        for (int i = 0; i < vertexCount; i++)
        {
            adjList.push_back({});
        }
    }

    void add_edge(long vertex1, long vertex2, long weight)
    {
        adjList[vertex1].push_back(make_pair(vertex2, weight));
        adjList[vertex2].push_back(make_pair(vertex1, weight));
        edgeCount++;
    }

    void dfs(vector<long> &result, long start)
    {
        vector<bool> visited(vertexCount, false);
        stack<long> st;

        st.push(start);
        visited[start] = true;
        result.push_back(start);

        while (!st.empty())
        {
            long temp = st.top();
            st.pop();

            if (!visited[temp])
            {
                result.push_back(temp);
                visited[temp] = true;
            }

            for (auto vertex : adjList[temp])
            {
                if (!visited[vertex.first])
                    st.push(vertex.first);
            }
        }
    }

    void bfs(vector<long> &result, long start)
    {
        vector<bool> visited(vertexCount, false);
        queue<long> q;

        q.push(start);
        visited[start] = true;
        result.push_back(start);

        while (!q.empty())
        {
            long temp = q.front();
            q.pop();

            for (auto vertex : adjList[temp])
            {
                if (!visited[vertex.first])
                {
                    q.push(vertex.first);
                    visited[vertex.first] = true;
                    result.push_back(vertex.first);
                }
            }
        }
    }

    void dijkstra(vector<long> &result, vector<long> &pathLength, long start)
    {
        vector<bool> visited(vertexCount, false);
        priority_queue<pair<long, long>, vector<pair<long, long>>, greater<pair<long, long>>> pq;
        result = vector<long>(vertexCount, LONG_MAX);
        pathLength = vector<long>(vertexCount, 0);

        pq.push(make_pair(0, start));
        result[start] = 0;
        pathLength[start] = 1;

        while (!pq.empty())
        {
            auto temp = pq.top();
            pq.pop();

            long current = temp.second;

            if (visited[current])
                continue;
            visited[current] = true;

            for (auto vertex : adjList[current])
            {
                long nextVertex = vertex.first;
                long weight = vertex.second;

                if (!visited[nextVertex])
                {
                    if (temp.first + weight < result[nextVertex])
                    {
                        result[nextVertex] = temp.first + weight;
                        pathLength[nextVertex] = pathLength[current] + 1;
                        pq.push(make_pair(result[nextVertex], nextVertex));
                    }
                    else if (temp.first + weight == result[nextVertex])
                    {
                        // Take the shorter vertex count if same distance
                        pathLength[nextVertex] = min(pathLength[nextVertex], pathLength[current] + 1);
                    }
                }
            }
        }
    }

    void print_path(long end, vector<long> &parent)
    {
        if (end == -1)
            return;
        print_path(parent[end], parent);
        cout << end << " ";
    }
};

int main()
{
    graph g;
    long n, m, start, end;
    cin >> n >> m >> start >> end;
    long v1, v2, w;
    int totalPath = 0;

    g.init(n + 1);
    while (m--)
    {
        cin >> v1 >> v2 >> w;
        g.add_edge(v1, v2, w);
    }

    vector<long> dijkstra_result;
    vector<long> parent;

    vector<long> result, pathLength;
    g.dijkstra(result, pathLength, start);

    long res = result[end];
    long path = pathLength[end];

    if (path >= n / 2)
    {
        res = res / 2;
    }

    cout << res;

    return 0;
}

/*
Sample Input 1
4 5 1 3
1 2 3
2 3 1
1 3 7
2 4 4
4 3 2
Sample Output 1
2

Sample Input 2
3 3 1 3
1 2 3
2 3 4
1 3 8
Sample Output 2
4

Sample Input 3
4 4 1 4
1 2 1
2 3 1
3 4 1
1 4 10
Sample Output 3
2
*/