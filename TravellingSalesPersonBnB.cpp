#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max(); // Define infinity as the maximum integer value

// Define the size of the graph
const int N = 4;

// Define the graph as an adjacency matrix
int graph[N][N] = {
    {0, 10, 15, 20},  // Node 0 to Node 0 has cost 0, Node 0 to Node 1 has cost 10, and so on
    {10, 0, 35, 25},
    {15, 35, 0, 30},
    {20, 25, 30, 0}
};

int minCost = INF; // Initialize the minimum cost to infinity

// Bounding function to find the lower bound of the partial solution
int bound(vector<int>& path) {
    int cost = 0; // Initialize the cost to 0
    bool visited[N] = { false }; // Initialize an array to keep track of visited nodes
    for (int i = 0; i < path.size() - 1; ++i)
        cost += graph[path[i]][path[i + 1]]; // Add the cost of the edges in the current path
    int last = path.back(); // Get the last node in the path
    for (int i = 0; i < N; ++i) {
        if (!visited[i])
            cost += *min_element(graph[last], graph[last] + N); // Add the minimum cost edge from the last node to any unvisited node
    }
    return cost; // Return the lower bound
}

// Branch and Bound algorithm
void tspBB(int level, int cost, vector<int>& path) {
    if (level == N) { // If all nodes have been visited
        // Add the cost of returning to the starting node and update the minimum cost if necessary
        minCost = min(minCost, cost + graph[path.back()][path[0]]);
        return;
    }
    for (int i = 0; i < N; ++i) { // Iterate over all nodes
        if (find(path.begin(), path.end(), i) == path.end()) { // If node i is not already visited
            int newCost = cost + graph[path.back()][i]; // Calculate the new cost by adding the cost of the edge from the last node to node i
            if (newCost + bound(path) < minCost) { // If the new cost plus the lower bound is less than the current minimum cost
                path.push_back(i); // Add node i to the current path
                tspBB(level + 1, newCost, path); // Recur for the next level
                path.pop_back(); // Backtrack - remove node i from the current path
            }
        }
    }
}
//
//int main() {
//    vector<int> path = { 0 }; // Start from node 0
//    tspBB(1, 0, path); // Start the Branch and Bound algorithm from level 1, with cost 0 and the initial path
//    cout << "Minimum cost: " << minCost << endl; // Output the minimum cost
//    return 0;
//}
