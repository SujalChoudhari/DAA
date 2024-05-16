#include <iostream>
#include <vector>
#include <string>
#include <memory>

std::shared_ptr<std::vector<int>> get_pi_table(const std::string& pattern) {
	std::shared_ptr<std::vector<int>> pi_table = std::make_shared<std::vector<int>>(pattern.length(), 0);

	/**
	* How to calculate PI table
	* Loop through the pattern.
	* take an index i and start from the very 0.
	*
	* If current char matches with the char at index i,
	* we found a match this is potential new longest prefix suffix.
	* Increment the index. Index is the new longest prefix suffix.
	*
	* If the pattern is not matched, we need to gi to the
	* previous longest prefix suffix of the pattern.
	*
	* and for every char in pattern we need to store the corresponding
	* pi value.
	*/
	int i = 0;
	for (int j = 1; j < pattern.length(); j++) {
		while (i > 0 && pattern[i] != pattern[j]) {
			i = pi_table->at(i - 1);
		}
		if (pattern[i] == pattern[j]) {
			i++;
		}
		pi_table->at(j) = i;
	}
	return pi_table;
}

int kmp(const std::string& text, const std::string& pattern, std::shared_ptr<std::vector<int>> pi_table) {
	/**
	* How to calculate KMP
	* Loop through the text
	* take an index i and start from the very 0 of the pattern in pi table.
	* take an index j and start from the very 0 of the text.
	* loop through j until we find a match or text ends.
	* 
	* if we find the pattern matches with the text at current i and j
	* move the i forward. if it doesn't match with current i
	*/
	
	int i = 0; // start at index 0 of the pi table. it 
	// pi table always start at index 1.
	for (int j = 0; j < text.length(); j++) {
		while (i > 0 && text[j] != pattern[i]) {
			i = pi_table->at(i - 1);
		}
		if (text[j] == pattern[i]) {
			i++;
		}
		if (i == pattern.length()) {
			return j - i + 1;
		}
	}
	return -1;
}

int run_kmp() {
	std::string text = "ababcababcabcabc";
	std::string pattern = "cabc";

	std::shared_ptr<std::vector<int>> pi_table = get_pi_table(pattern);
	int result = kmp(text, pattern, pi_table);

	if (result != -1) {
		std::cout << "Pattern found at index " << result << std::endl;
	}
	else {
		std::cout << "Pattern not found in the text" << std::endl;
	}

	return 0;
}

//int main() {
//	return run_kmp();
//}
