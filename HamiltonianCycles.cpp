#include <deque>
#include <iostream>

bool visited[5] = { false };
std::deque<int> path;

int graph[5][5] = { // 0 = there is an edge between nodes, 1 = there is no edge
		{ 0, 1, 0, 0, 0 },
		{ 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 }
};

bool bounding_conditions(int current_node, int next_node) {
	if (visited[next_node]) { // already visited
		return false;
	}

	if (graph[current_node][next_node] == 1) { // no edge
		return false;
	}

	return true;
}

void hamiltonian_cycle() {

	if (path.size() == 5) { // promising path
		// check path from last back to first
		if (graph[path.back()][path.front()] == 0) {

			std::cout << "Hamiltonian cycle: ";
			for (int i = 0; i < 5; i++) {
				std::cout << path[i] << " ";
			}
			std::cout << std::endl;
			return;
		}
	}

	for (int i = 0; i < 5; i++) {
		if (visited[i]) { // already visited
			continue;
		}

		// check if bounding conditions are met
		// with the previous node (parent) and current one
		if (bounding_conditions(path.back(), i)) { 
			visited[i] = true; // visit this node
			path.push_back(i); // add this node to the path
			hamiltonian_cycle(); // check for next nodes
			path.pop_back(); // remove this node from the path of failed
			visited[i] = false; // remove this node from the visited list
		}
	}

}


//int main() {
//	visited[0] = true;
//	path.push_front(0);
//	hamiltonian_cycle();
//	return 0;
//}