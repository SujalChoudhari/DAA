#include <deque>
#include <memory>
#include <iostream>


void sum_of_subsets(
	std::shared_ptr<std::deque<int>>values,
	std::shared_ptr<std::deque<bool>> taken,
	std::shared_ptr<std::deque<bool>> visited,
	int sum) {

	if (sum == 0) {
		std::cout << "A solution is: ";
		for (int i = 0; i < values->size(); i++) {
			if (taken->at(i)) {
				std::cout << values->at(i) << " ";
			}
		}
		std::cout << std::endl;

		return;
	}

	for (int i = 0; i < values->size(); i++) {

		if (visited->at(i)) {
			continue;
		}

		if (values->at(i) <= sum) {
			int new_sum = sum - values->at(i);
			taken->at(i) = true;
			visited->at(i) = true;
			sum_of_subsets(values, taken, visited, new_sum);
			taken->at(i) = false;
		}
	}
}


//int main() {
//
//	std::shared_ptr<std::deque<int>> values = std::make_shared<std::deque<int>>();
//	values->push_back(5);
//	values->push_back(10);
//	values->push_back(15);
//	values->push_back(20);
//	std::shared_ptr<std::deque<bool>> taken = std::make_shared<std::deque<bool>>(5, false);
//	std::shared_ptr<std::deque<bool>> visited = std::make_shared<std::deque<bool>>(5, false);
//
//	int sum_to_make = 25;
//
//	sum_of_subsets(values, taken, visited, sum_to_make);
//
//	return 0;
//}