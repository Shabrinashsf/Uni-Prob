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

        adjList.resize(vertexCount);
    }

    void add_edge(long vertex1, long vertex2, long weight)
    {
        adjList[vertex1].push_back(make_pair(vertex2, weight));
        edgeCount++;
    }

    void dijkstra(vector<long> &result, vector<long> &predecessor, long start)
    {
        vector<bool> visited(vertexCount, false);
        priority_queue<pair<long, long>, vector<pair<long, long>>, greater<pair<long, long>>>
            pq;
        result = vector<long>(vertexCount, LONG_MAX);
        predecessor = vector<long>(vertexCount, -1); // predecessor is a vector to store the predecessor (pendahulu) of each node

        pq.push(make_pair(0, start));
        result[start] = 0;

        while (!pq.empty())
        {
            auto temp = pq.top();
            pq.pop();

            long u = temp.second;
            if (visited[u])
                continue;
            visited[u] = true;

            for (auto vertex : adjList[u])
            {
                long nextVertex = vertex.first;
                long weight = vertex.second;

                if (!visited[nextVertex] && result[u] + weight < result[nextVertex])
                {
                    result[nextVertex] = result[u] + weight;
                    pq.push(make_pair(result[nextVertex], nextVertex));
                    predecessor[nextVertex] = u; // store the predecessor of nextVertex
                }
            }
        }
    }

    vector<long> trace_path(long start, long end, const vector<long> &predecessor)
    {
        vector<long> path;
        // loop from end to start using predecessor
        for (long at = end; at != -1; at = predecessor[at])
        {
            path.push_back(at);
        }
        // reverse the path to get it from start to end
        reverse(path.begin(), path.end());
        if (path.front() == start)
        {
            // if the path starts with the start node, return the path
            return path;
        }
        return {}; // return an empty path if there is no path from start to end
    }
};

int main()
{
    graph g;

    long v, n;
    long v1, v2, w;
    long start;
    long end;
    cin >> v >> n;

    g.init(v);
    for (long i = 0; i < n; i++)
    {
        cin >> v1 >> v2 >> w;
        g.add_edge(v1, v2, w);
    }

    vector<long> dijkstra_result;
    vector<long> predecessor;

    cin >> start;
    cin >> end;

    g.dijkstra(dijkstra_result, predecessor, start);

    vector<long> path = g.trace_path(start, end, predecessor);

    if (!path.empty())
    {
        cout << "Path found with cost " << dijkstra_result[end] << ": ";
        for (auto node : path)
        {
            cout << node << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "Impossible to find the path\n";
    }
    return 0;
}

/*
Sample Input 0
3 3
0 1 5
1 2 7
2 0 3
0
2
Sample Output 0
Path found with cost 12: 0 1 2

Sample Input 1
5 5
0 1 5
1 2 7
0 2 3
2 3 4
1 3 2
3
1
Sample Output 1
Impossible to find the path
*/