#include <iostream>


bool place(int* queen_placements, int row, int col, int size) {
	// check for same row as nth queen is in nth row but not in nth column
	for (int i = 0; i < row; i++)
	{

		if (queen_placements[i] == col) { // same column
			return false;
		}
		else if (abs(queen_placements[i] - col) == abs(i - row)) { // same diagonal
			return false;
		}
	}
	return true;
}

bool try_place_nth_queen(int* queen_placements, int row, int col, int size) {
	if (row == size) {
		return true;
	}

	for (int i = 0; i < size; i++) {
		if (place(queen_placements, row, i, size)) {
			queen_placements[row] = i; // place current and try to place next queen
			if (try_place_nth_queen(queen_placements, row + 1, 0, size)) {
				return true;
			} // if the next queen place, find next loc for our current queen
		}
	}
	return false;
}

int* n_queens(int size) {
	// nth queen goes in nth row
	// columns are stored in queen_placements
	int* queen_placements = new int[size];
	for (int i = 0; i < size; i++)
	{
		queen_placements[i] = -1;
	}
	try_place_nth_queen(queen_placements, 0, 0, size);

	return queen_placements;
}


void run_n_queens() {
	int queens = 6;
	int* placements = n_queens(queens);

	for (int i = 0; i < queens; i++) {
		for (int j = 0; j < queens; j++) {
			if (placements[i] == j) {
				std::cout << "Q\t";
			}
			else {
				std::cout << ".\t";
			}
		}
		std::cout << std::endl << std::endl;
	}

}

//int main() {
//	run_n_queens();
//	return 0;
//}