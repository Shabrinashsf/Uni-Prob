#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

int targetWeight;
map<pair<int, int>, bool> visitedEdge;
vector<vector<pair<int, int>>> adjList;
bool found;

void dfs(int node, int currentWeight)
{
    if (currentWeight > targetWeight || found)
        return;

    if (currentWeight == targetWeight)
    {
        found = true;
        return;
    }

    for (auto neighbor : adjList[node])
    {
        int nextNode = neighbor.first;
        int weight = neighbor.second;

        pair<int, int> edge1 = {node, nextNode};
        pair<int, int> edge2 = {nextNode, node};

        if (!visitedEdge[edge1] && !visitedEdge[edge2])
        {
            visitedEdge[edge1] = true;
            visitedEdge[edge2] = true;

            dfs(nextNode, currentWeight + weight);

            // backtrack edge
            visitedEdge[edge1] = false;
            visitedEdge[edge2] = false;
        }
    }
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        adjList.clear();
        visitedEdge.clear();
        found = false;

        int u, v, w;
        int maxNode = 0;

        while (true)
        {
            cin >> u >> v >> w;
            if (u == 0 && v == 0 && w == 0)
            {
                break;
            }
            maxNode = max(maxNode, max(u, v));
            if (adjList.size() <= maxNode)
                adjList.resize(maxNode + 1);

            adjList[u].push_back({v, w});
            adjList[v].push_back({u, w});
        }

        cin >> targetWeight;

        // dfs dari semua node (karena kita gak tahu node mana yang jadi start)
        for (int i = 0; i <= maxNode; i++)
        {
            dfs(i, 0);
            if (found)
                break;
        }

        cout << (found ? "YES" : "NO") << "\n";
    }

    return 0;
}

/*
1
1 2 5
1 3 8
2 4 4
4 5 11
2 3 13
3 6 4
5 6 2
0 0 0
22
*/