#include <string>
#include <iostream>

std::string lcs(const std::string& text, const std::string& pattern) {

	// create the matrix (keep the 0 row and column reserved)
	int** lcs_matrix = new int* [pattern.size() + 1];

	for (int i = 0; i < pattern.size() + 1; i++) {
		lcs_matrix[i] = new int[text.size() + 1];
	}

	std::string lcs = "";

	// make zero
	for (int i = 0; i <= pattern.size(); ++i) {
		for (int j = 0; j <= text.size(); ++j) {
			if (i == 0 || j == 0) {
				lcs_matrix[i][j] = 0;
			}
		}
	}

	// go through the matrix and update the values such that,
	// if match then lcs_matrix[i][j] = lcs_matrix[i - 1][j - 1] + 1
	// else take the maximum fro top or left.

	for (int i = 1; i < pattern.size() + 1; i++) {
		for (int j = 1; j < text.size() + 1; j++) {

			if (pattern[i - 1] == text[j - 1]) {
				lcs_matrix[i][j] = lcs_matrix[i - 1][j - 1] + 1;
			}
			else {
				lcs_matrix[i][j] = std::max(lcs_matrix[i - 1][j], lcs_matrix[i][j - 1]);
			}
		}
	}



	// now back track to find the lcs
	//start from very end and see if the current number is 1 + the diagonal number
	//if yes the the char is in the lcs, if not move towards the maximum of the 
	//left or top an repeat until as 0,0.

	int i = pattern.size();
	int j = text.size();

	while (i != 0 && j != 0) {

		if (pattern[i - 1] == text[j - 1]) {
			lcs += pattern[i - 1];
			i--;
			j--;
		}
		else {
			if (lcs_matrix[i - 1][j] > lcs_matrix[i][j - 1]) {
				i--;
			}
			else {
				j--;
			}
		}
	}

	std::reverse(lcs.begin(), lcs.end());
	return lcs;

}


void run_lcs() {
	std::string text = "longest common subsequence";
	std::string pattern = "lemon";

	std::cout << lcs(text, pattern) << std::endl;
}

int main() {
	run_lcs();
	return 0;
}