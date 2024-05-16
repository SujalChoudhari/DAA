#include <string>
#include <iostream>


int naive_string_matching(const std::string& text, const std::string& pattern) {
	// Simple double forloop based string matching
	for (int i = 0; i < text.length() - pattern.length(); i++) {
		bool found = true;
		for (int j = 0; j < pattern.length(); j++) {
			if (text[i + j] != pattern[j]) {
				found = false;
				break;
			}
		}
		if (found) {
			return i;
		}
	}
}

void run_naive_string_matching() {
	std::string text = "alphabetagammadeltaomega";
	std::string pattern = "ma";

	int index = naive_string_matching(text, pattern);
	std::cout << "Index: " << index << std::endl;
}



//int main() {
//	run_naive_string_matching();
//	return 0;
//}