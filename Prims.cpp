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

void primsMST(std::vector<Edge> graph[], int maxNodes)
{

    // uses priority queue to manage the heap, using CompareEdge()
    // to automatically sort on the basis of weight of nodes
    std::priority_queue<Edge, std::vector<Edge>, CompareEdges> minHeap;

    std::vector<bool> inMST(maxNodes, false);
    std::vector<Edge> result;

    // Start from vertex 'A' (calculates best node below)
    char startVertex = 'A';
    int currMinCost = INT_MAX;
    for (int i = 0; i < maxNodes; i++)
    {
        for (const Edge &edge : graph[i])
        {
            if(edge.weight < currMinCost){
                currMinCost = edge.weight;
                startVertex = edge.src;
            }
        }
    }

    inMST[startVertex - 'A'] = true; // include it in MST

    // Add all edges from the starting vertex to the minHeap
    for (const Edge &edge : graph[startVertex - 'A'])
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
        if (inMST[currentVertex - 'A'])
            continue;

        // Include the current edge in the MST
        result.push_back(currentEdge);
        inMST[currentVertex - 'A'] = true;

        // Add all adjacent edges of the current vertex to the minHeap
        for (const Edge &adjEdge : graph[currentVertex - 'A'])
        {
            if (!inMST[adjEdge.dest - 'A'])
            {
                minHeap.push(adjEdge);
            }
        }
    }

    // Print the Minimum Spanning Tree
    for (const Edge &edge : result)
    {
        std::cout << "Edge: " << edge.src << " - " << edge.dest << " Weight: " << edge.weight << std::endl;
    }
}

int main()
{
    int V = 6;
    std::vector<Edge> graph[V];

    // Add edges to the graph (suitable for Directed graph)
    graph[0].push_back({'A', 'B', 4});
    graph[0].push_back({'A', 'C', 4});

    graph[1].push_back({'B', 'A', 4});
    graph[1].push_back({'B', 'C', 2});

    graph[2].push_back({'C', 'A', 4});
    graph[2].push_back({'C', 'B', 2});
    graph[2].push_back({'C', 'D', 3});
    graph[2].push_back({'C', 'E', 2});
    graph[2].push_back({'C', 'F', 4});

    graph[3].push_back({'D', 'C', 3});
    graph[3].push_back({'D', 'F', 3});

    graph[4].push_back({'E', 'C', 2});
    graph[4].push_back({'E', 'F', 3});

    graph[5].push_back({'F', 'D', 3});
    graph[5].push_back({'F', 'E', 3});
    graph[5].push_back({'F', 'C', 4});

    primsMST(graph, V);

    return 0;
}
