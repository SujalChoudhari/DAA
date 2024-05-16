#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

std::shared_ptr<std::vector<int>> coin_change_greedy(std::vector<int> denominations, int total) {
	int remaining = total;
	std::shared_ptr<std::vector<int>> res = std::make_shared<std::vector<int>>();
	// sort denominations such that the greatest denominations are at beginning
	std::sort(denominations.begin(), denominations.end(), [](int a, int b) {return a > b;});

	/*
	* Start from the greatest denomination and try to use it,
	* if you can't try a smaller denomination.
	* until you can't, or u have your solution.
	*/
	int max_tries = total;
	while (remaining > 0) {
		max_tries--;
		if (max_tries < 0) {
			return res;
		}
		for (int denom : denominations) {
			while (denom <= remaining) {
				remaining -= denom;
				res.get()->push_back(denom);
			}
		}
	}
	return res;
}

void run_coin_change_greedy() {
	std::vector<int> denominations = { 1,2,5,10,20 };
	int total = 46;

	std::shared_ptr<std::vector<int>> res = coin_change_greedy(denominations, total);

	std::cout << "Result: ";
	for (int i = 0; i < res.get()->size(); i++) {
		std::cout << res.get()->at(i) << " ";
	}
	std::cout << std::endl;
}

//int main() {
//	run_coin_change_greedy();
//	return 0;
//}