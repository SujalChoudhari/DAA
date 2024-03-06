#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

struct Edge
{
    char src, dest;
    int weight;
};

void kruskalMST(std::vector<Edge> graph, int maxNodes)
{
    std::sort(graph.begin(), graph.end(), [](const Edge &a, const Edge &b)
              { return a.weight > b.weight; });

    std::vector<char> added = std::vector<char>();
    std::vector<Edge> mst = std::vector<Edge>();

    while (added.size() < maxNodes)
    {
        Edge currentEdge = graph.back();
        graph.pop_back();

        // check loop [check if source exists and dest exist if yes then forms loop]
        if (
            std::find(added.begin(), added.end(), currentEdge.src) == added.end() || std::find(added.begin(), added.end(), currentEdge.dest) == added.end())
        {
            // no loop formation
            mst.push_back(currentEdge);
            if (std::find(added.begin(), added.end(), currentEdge.src) == added.end())
                added.push_back(currentEdge.src);
            if (std::find(added.begin(), added.end(), currentEdge.dest) == added.end())
                added.push_back(currentEdge.dest);
        }
    }

    std::cout << "Kruskal Algorithm" << std::endl;
    for (const Edge &edge : mst)
    {
        std::cout << edge.src << " <--" << edge.weight << "--> " << edge.dest << std::endl;
    }
}

int main()
{
    int V = 5;
    std::vector<Edge> graph = std::vector<Edge>();

    // Add edges to the graph (suitable for Directed graph)
    graph.push_back({'1', '2', 1});
    graph.push_back({'1', '3', 2});
    graph.push_back({'2', '4', 3});
    graph.push_back({'3', '4', 6});
    graph.push_back({'3', '5', 5});
    graph.push_back({'4', '5', 4});
    kruskalMST(graph, V);

    return 0;
}