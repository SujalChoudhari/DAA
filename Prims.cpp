#include <iostream>
#include <vector>
#include <climits>


struct Edge {
	int from;
	int to;
	int weight;
};

// Get the minimum edge that connects a set of visited nodes to any unvisited node
Edge get_min_edge(int edge_count, Edge* edges, const std::vector<Edge>& selected_edges, const std::vector<bool>& visited) {
	Edge min_edge = { -1, -1, INT_MAX };

	for (int i = 0; i < edge_count; i++) {
		int from = edges[i].from;
		int to = edges[i].to;

		if ((visited[from] && !visited[to]) || (visited[to] && !visited[from])) {
			if (edges[i].weight < min_edge.weight) {
				bool already_selected = false;
				for (const auto& selected_edge : selected_edges) {
					if ((selected_edge.from == edges[i].from && selected_edge.to == edges[i].to) ||
						(selected_edge.from == edges[i].to && selected_edge.to == edges[i].from)) {
						already_selected = true;
						break;
					}
				}
				if (!already_selected) {
					min_edge = edges[i];
				}
			}
		}
	}

	return min_edge;
}

std::vector<Edge> prims(int node_count, int edge_count, int edges[][3]) {
	std::vector<Edge> raw_edges(edge_count);

	// Create the edges
	for (int i = 0; i < edge_count; i++) {
		raw_edges[i] = { edges[i][0], edges[i][1], edges[i][2] };
	}

	std::vector<Edge> selected_edges;
	std::vector<bool> visited(node_count, false);

	// Start from a random vertex
	int random_starting_vertex = 0;
	visited[random_starting_vertex] = true;

	// Prim's Algorithm
	for (int i = 0; i < node_count - 1; i++) {
		Edge min_edge = get_min_edge(edge_count, raw_edges.data(), selected_edges, visited);
		selected_edges.push_back(min_edge);

		// Mark the newly connected node as visited
		visited[min_edge.from] = true;
		visited[min_edge.to] = true;
	}

	return selected_edges;
}

void run_prims() {
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

	std::vector<Edge> res = prims(node_count, edge_count, edges);
	int cost = 0;

	for (const auto& edge : res) {
		std::cout << edge.from << " " << edge.to << " " << edge.weight << std::endl;
		cost += edge.weight;
	}

	std::cout << "Total cost: " << cost << std::endl;
}

//int main() {
//	run_prims();
//	return 0;
//}
