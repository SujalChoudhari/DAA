#include <string>
#include <iostream>


int hash_function(const std::string& pattern) {
	int hash = 0;
	for (int i = 0; i < pattern.length();i++) {
		hash += pattern.at(i) * (int)std::pow(10, i) % pattern.length();
	}
	return hash;
}

/*
* In rabin karp we have a hash function that we can use to check the n length pattern
* is a match or not. If we find it to be match, then we can check it character by character.
* We can use a sliding window algorithm.
*/
int rabin_karp(const std::string& text, const std::string& pattern) {
	// this uses a sliding window kind of algo.
	int pattern_hash = hash_function(pattern);
	for (int i = 0; i < text.length() - pattern.length() + 1; i++) {
		std::string window = text.substr(i, pattern.length());
		if (hash_function(window) == hash_function(pattern)) {
			// this is a good place to check for a match
			bool found = true;
			for (int j = 0; j < pattern.length(); j++) {
				if (window.at(j) != pattern.at(j)) {
					found = false;
					break;
				}
			}
			if (found) {
				return i;
			}
		}
	}
	return - 1;

}

void run_rabin_karp() {
	std::string text = "onetwothreefourfivesixseveneightnine";
	std::string pattern = "nine";

	int index = rabin_karp(text, pattern);
	std::cout << "Index: " << index << std::endl;
}


//int main() {
//	run_rabin_karp();
//	return 0;
//}