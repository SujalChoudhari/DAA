#include <iostream>
#include <climits>

int cost(int* dimension, int i, int j, int k, int** a_matrix) {
	return a_matrix[i][k] + a_matrix[k + 1][j] + dimension[i - 1] * dimension[k] * dimension[j];
}

std::pair<int**, int**> matrix_chain(int* dimension, int size) {
	int** a_matrix = new int* [size];
	int** p_matrix = new int* [size];

	// Initialize the matrices
	for (int i = 0; i < size; i++) {
		a_matrix[i] = new int[size];
		p_matrix[i] = new int[size];
		for (int j = 0; j < size; j++) {
			a_matrix[i][j] = (i == j) ? 0 : INT_MAX;
			p_matrix[i][j] = -1;
		}
	}

	// Fill the matrices starting from chain lengths
	/**
	* We need to go diagonally, so we need some way to get the exact a and j.
	* We take a chain_length variable to keep track of what chain length we
	* are considering.
	* for chain length = 1 the cost is 0 as there is only 1 matrix.
	* for every chain length increase, there is loss of a row from bottom,
	* to take this into account we end i at size - chain_length.
	* for every chain length increase, there is loss of a column from left,
	* to take this into account we keep j as i + chain_length - 1
	* 
	* k can be between i <= k < j so we loop from i to j
	* and for each k we find the minimum and update the a_matrix and p_matrix based on k and cost.
	*/
	for (int chain_length = 2; chain_length <= size; chain_length++) {
		for (int i = 1; i <= size - chain_length; i++) {
			int j = i + chain_length - 1;
			int min_cost = INT_MAX;
			int min_k = -1;

			for (int k = i; k < j; k++) {
				int new_cost = cost(dimension, i, j, k, a_matrix);
				if (new_cost < min_cost) {
					min_cost = new_cost;
					min_k = k;
				}
			}

			a_matrix[i][j] = min_cost;
			p_matrix[i][j] = min_k;
		}
	}

	return { a_matrix, p_matrix };
}

void run_matrix_chain() {
	int size = 5; // Considering the number of dimensions, including the first and last
	int dimension[] = { 3, 4, 2, 1, 4 }; // Matrix dimensions

	std::pair<int**, int**> matrices = matrix_chain(dimension, size);
	int** a_matrix = matrices.first;
	int** p_matrix = matrices.second;

	std::cout << "Cost Matrix: " << std::endl;
	for (int i = 1; i < size; i++) {
		for (int j = 1; j < size; j++) {
			std::cout << a_matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}

	// Freeing the memory
	for (int i = 0; i < size - 1; i++) {
		delete[] a_matrix[i];
		delete[] p_matrix[i];
	}
	delete[] a_matrix;
	delete[] p_matrix;
}

//int main() {
//	run_matrix_chain();
//	return 0;
//}
