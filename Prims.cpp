#include <iostream>
#include <vector>
#include <queue>
#include <climits>

struct Edge
{
    char src, dest;
    int weight;
};

struct CompareEdges
{
    bool operator()(const Edge &a, const Edge &b) const
    {
        return a.weight > b.weight;
    }
};

void kruskalMST(std::vector<Edge> graph[], int maxNodes)
{

    // uses priority queue to manage the heap, using CompareEdge()
    // to automatically sort on the basis of weight of nodes
    std::priority_queue<Edge, std::vector<Edge>, CompareEdges> minHeap;

    std::vector<bool> inMST(maxNodes, false);
    std::vector<Edge> result;

    // Start from vertex 'A' (calculates best node below)
    char startVertex = '1';
    int currMinCost = INT_MAX;
    for (int i = 0; i < maxNodes; i++)
    {
        for (const Edge &edge : graph[i])
        {
            if (edge.weight < currMinCost)
            {
                currMinCost = edge.weight;
                startVertex = edge.src;
            }
        }
    }

    inMST[startVertex - '1'] = true; // include it in MST

    // Add all edges from the starting vertex to the minHeap
    for (const Edge &edge : graph[startVertex - '1'])
    {
        minHeap.push(edge); // create the min heap (priority queue)
    }

    // Prims methods of selections.
    while (!minHeap.empty())
    {
        Edge currentEdge = minHeap.top();
        minHeap.pop();

        char currentVertex = currentEdge.dest;

        // Skip if the vertex is already in MST
        if (inMST[currentVertex - '1'])
            continue;

        // Include the current edge in the MST
        result.push_back(currentEdge);
        inMST[currentVertex - '1'] = true;

        // Add all adjacent edges of the current vertex to the minHeap
        for (const Edge &adjEdge : graph[currentVertex - '1'])
        {
            if (!inMST[adjEdge.dest - '1'])
            {
                minHeap.push(adjEdge);
            }
        }
    }

    std::cout << "Prim's Algorithm" <<std::endl;
    // Print the Minimum Spanning Tree
    for (const Edge &edge : result)
    {
        std::cout << edge.src << " <--" << edge.weight << "--> " << edge.dest << std::endl;
    }
}

int main()
{
    int V = 5;
    std::vector<Edge> graph[V];

    // Add edges to the graph (suitable for Directed graph)
    graph[0].push_back({'1', '2', 1});
    graph[1].push_back({'2', '1', 1});
    graph[0].push_back({'1', '3', 2});
    graph[2].push_back({'3', '1', 2});
    graph[1].push_back({'2', '4', 3});
    graph[3].push_back({'4', '2', 3});
    graph[2].push_back({'3', '4', 6});
    graph[3].push_back({'4', '3', 6});
    graph[2].push_back({'3', '5', 5});
    graph[4].push_back({'5', '3', 5});
    graph[3].push_back({'4', '5', 4});
    graph[4].push_back({'5', '4', 4});

    kruskalMST(graph, V);

    return 0;
}
