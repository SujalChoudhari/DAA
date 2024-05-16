#include <climits>
#include <iostream>

struct Solution {
	int** matrix;
	int** p_matrix;
};

Solution floyd_warshall(int adjacency_matrix[][5], int size) {
	/**
	* Floyd-Warshall Algorithm
	*
	* We try to find the shortest path between all pairs of vertices
	* What we do is assume there is a k vertex in between of i and j
	* then we update the distances (min) between i and j or i and j via k.
	* Here k can be a single vertex or a set of vertices.
	*
	* So to work out the shortest path between two vertices i and j
	* We take k as every other vertex.
	*
	* Every time we update the distances we also update the k matrix.
	*/
	int** ret = new int* [size];
	int** the_k_matrix = new int* [size];
	for (int i = 0; i < size; i++) {
		ret[i] = new int[size];
		the_k_matrix[i] = new int[size];
		for (int j = 0; j < size; j++) {
			ret[i][j] = adjacency_matrix[i][j];
			the_k_matrix[i][j] = -1;
		}
	}

	for (int k = 0; k < size; k++) {
		for (int j = 0; j < size; j++) {
			for (int i = 0; i < size; i++) {
				/*ret[i][j] = std::min(ret[i][j], ret[i][k] + ret[k][j]);*/

				if (ret[i][j] > ret[i][k] + ret[k][j]) {
					the_k_matrix[i][j] = k;
					ret[i][j] = ret[i][k] + ret[k][j];
				}
			}
		}
	}

	return { ret,the_k_matrix };
}


void run_floyd_warshall() {
	int size = 5;
	int adjacency_matrix[][5] = {
		{	0,		400,	4,		5,		3 },
		{	4,		0,		8,		999,	999},
		{	100,	8,		0,		7,		999},
		{	300,	999,	7,		0,		9 },
		{	400,	999,	999,	9,		0 }
	};

	Solution matrices = floyd_warshall(adjacency_matrix, size);

	std::cout << "Solution Distances:\n__\t\t\t\t\t__" << std::endl;
	for (int i = 0; i < size; i++) {
		std::cout << "|  ";
		for (int j = 0; j < size; j++) {
			std::cout << matrices.matrix[i][j] << "\t";
		}
		std::cout << " |\t" << std::endl;
	}
	std::cout << "--\t\t\t\t\t--" << std::endl;

	std::cout << "Via Node:\n__\t\t\t\t\t__" << std::endl;
	for (int i = 0; i < size; i++) {
		std::cout << "|  ";
		for (int j = 0; j < size; j++) {
			std::cout << (matrices.p_matrix[i][j]) << "\t";
		}
		std::cout << " |\t" << std::endl;
	}
	std::cout << "--\t\t\t\t\t--" << std::endl;


}

int main() {
	run_floyd_warshall();
	return 0;
}