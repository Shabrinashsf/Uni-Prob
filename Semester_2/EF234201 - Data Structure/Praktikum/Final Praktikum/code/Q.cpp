#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

long find_parent(vector<long> &parent, long v)
{
    if (v == parent[v])
        return v;

    return find_parent(parent, parent[v]);
}

void union_set(vector<long> &parent, long vertex1, long vertex2)
{
    int parent1 = find_parent(parent, vertex1);
    int parent2 = find_parent(parent, vertex2);

    if (parent1 != parent2)
        parent[parent2] = parent1;
}

void kruskal(vector<pair<long, pair<long, long>>> &result)
{
    vector<long> parent;
    for (int i = 0; i < vertexCount; i++)
        parent.push_back(i);

    sort(edgeList.begin(), edgeList.end());
    /*
    Penulis sengaja meletakkan weight dari edge pada bagian awal pair,
    sehingga edge list akan disort berdasarkan weight dari edge
    */

    for (auto edge : edgeList)
    {
        long vertex1 = edge.second.first;
        long vertex2 = edge.second.second;
        if (find_parent(parent, vertex1) != find_parent(parent, vertex2))
        {
            result.push_back(edge);
            union_set(parent, vertex1, vertex2);
            if (result.size() == vertexCount - 1)
                return;
        }
    }
}

int main()
{
    map<string, vector<string>> adjList;

    auto addEdge = [&](const std::string &u, const std::string &v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    };

    auto printGraph = [&]()
    {
        for (const auto &pair : adjList)
        {
            std::cout << pair.first << " : ";
            for (const std::string &neighbor : pair.second)
            {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
    };

    // Add edges
    addEdge("Delhi", "Mumbai");
    addEdge("Delhi", "Kolkata");
    addEdge("Mumbai", "Bangalore");
    addEdge("Kolkata", "Chennai");

    // Print the graph
    printGraph();

    return 0;
}