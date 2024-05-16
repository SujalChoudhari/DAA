#include <iostream>
#include <algorithm>
#include <vector>

struct Edge {
	int from;
	int to;
	int weight;
};

int find(std::vector<int>& parent, int node) { // Get the absolute parent of the given node
	// Path compression
	if (parent[node] != node) {
		parent[node] = find(parent, parent[node]);
	}
	return parent[node];
}

void union_sets(std::vector<int>& parent, std::vector<int>& rank, int a, int b) {
	// update the tree with the new nodes, change the parents and the ranks
	int rootA = find(parent, a);
	int rootB = find(parent, b);

	if (rootA != rootB) { // if nodes were disjoint
		// Union by rank
		if (rank[rootA] < rank[rootB]) { // B has more childrens
			parent[rootA] = rootB; // B is the new parent of A
		}
		else if (rank[rootA] > rank[rootB]) { // A has more childrens
			parent[rootB] = rootA; // A is the new parent of B
		}
		else { // they have the same rank
			parent[rootB] = rootA; // A is the new parent of B
			rank[rootA]++; // increase the rank
		}
	}
}

std::vector<Edge> kruskal(int node_count, int edge_count, const int edges[][3]) {
	std::vector<Edge> raw_edges(edge_count); // used for sorting
	std::vector<Edge> selected_edges; // solution edges
	std::vector<int> parent(node_count); // parent of each node, initially each node is its own parent
	std::vector<int> rank(node_count, 0); // the number of children of each node

	// Initialize parent
	for (int i = 0; i < node_count; i++) {
		parent[i] = i;
	}

	// Prepare edges
	for (int i = 0; i < edge_count; i++) {
		raw_edges[i] = { edges[i][0], edges[i][1], edges[i][2] };
	}

	// Sort edges by weight
	std::sort(raw_edges.begin(), raw_edges.end(), [](const Edge& a, const Edge& b) {
		return a.weight < b.weight;
		});

	// Select edges
	for (int i = 0; i < edge_count; i++) {
		int from = raw_edges[i].from;
		int to = raw_edges[i].to;

		if (find(parent, from) != find(parent, to)) {
			selected_edges.push_back(raw_edges[i]);
			union_sets(parent, rank, from, to);
		}
	}

	return selected_edges;
}

void run_kruskal() {
	int node_count = 5;
	int edge_count = 10;
	int edges[][3] = {
		{ 0, 1, 2 },
		{ 0, 2, 3 },
		{ 0, 3, 6 },
		{ 0, 4, 8 },
		{ 1, 2, 1 },
		{ 1, 3, 5 },
		{ 1, 4, 4 },
		{ 2, 3, 4 },
		{ 2, 4, 7 },
		{ 3, 4, 2 },
	};


	std::vector<Edge> solution_edges = kruskal(node_count, edge_count, edges);
	std::cout << "Selected Edges:" << std::endl;
	int cost = 0;
	for (int i = 0; i < solution_edges.size(); i++) {
		std::cout << solution_edges[i].from << " " << solution_edges[i].to << " " << solution_edges[i].weight << std::endl;
		cost += solution_edges[i].weight == 999 ? 0 : solution_edges[i].weight;
	}
	std::cout << "Total cost: " << cost << std::endl;

}

//int main() {
//	run_kruskal();
//	return 0;
//}