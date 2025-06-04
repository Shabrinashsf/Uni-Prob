#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool dfs(int node, int par, const vector<vector<int>> &adjList, vector<int> &visited, vector<int> &parent, int &startCycle, int &endCycle)
{
    visited[node] = 1;

    for (int neighbor : adjList[node])
    {
        if (neighbor == par)
            continue;

        if (visited[neighbor] == 0)
        {
            parent[neighbor] = node;
            if (dfs(neighbor, node, adjList, visited, parent, startCycle, endCycle))
                return true;
        }
        else if (visited[neighbor] == 1)
        {
            startCycle = neighbor;
            endCycle = node;
            return true;
        }
    }

    visited[node] = 2;
    return false;
}

vector<int> getCyclePath(int startCycle, int endCycle, const vector<int> &parent)
{
    vector<int> cyclePath;
    int current = endCycle;
    cyclePath.push_back(current);

    while (current != startCycle)
    {
        current = parent[current];
        cyclePath.push_back(current);
    }

    sort(cyclePath.begin(), cyclePath.end());
    return cyclePath;
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int vertex, edge;
        cin >> vertex >> edge;

        vector<vector<int>> adjList(vertex);
        vector<int> visited(vertex, 0);
        vector<int> parent(vertex, -1);
        int startCycle = -1, endCycle = -1;

        for (int i = 0; i < edge; i++)
        {
            int v1, v2;
            cin >> v1 >> v2;
            adjList[v1].push_back(v2);
            adjList[v2].push_back(v1);
        }

        bool foundCycle = false;

        for (int i = 0; i < vertex; i++)
        {
            if (visited[i] == 0)
            {
                if (dfs(i, -1, adjList, visited, parent, startCycle, endCycle))
                {
                    foundCycle = true;
                    break;
                }
            }
        }

        if (foundCycle)
        {
            vector<int> result = getCyclePath(startCycle, endCycle, parent);
            cout << "VOCALOID CYCLE PROGRAM (VCP) : CYCLE DETECTED";
            for (int node : result)
            {
                cout << " " << node;
            }
            cout << endl;
        }
        else
        {
            cout << "VOCALOID CYCLE PROGRAM (VCP) : NO CYCLE DETECTED" << endl;
        }
    }

    return 0;
}
