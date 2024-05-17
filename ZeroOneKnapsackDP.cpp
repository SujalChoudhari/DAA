#include <iostream>
#include <deque>

struct Item {
public:
	int profit;
	int weight;

public:
	Item(int profit, int weight) :profit(profit), weight(weight) {}


};


// set method
void run_zero_one_knapsack(std::deque<Item> items, int max_capacity) {

	int** table = new int* [items.size() + 1];
	for (int i = 0; i <= items.size(); i++) {
		table[i] = new int[max_capacity + 1];
	}

	for (int i = 0; i <= items.size(); i++) {
		table[i][0] = 0;
	}

	for (int i = 0; i <= max_capacity; i++) {
		table[0][i] = 0;
	}


	// now for each of the remaining cell
	for (int i = 1; i < items.size() + 1; i++) {
		for (int j = 1; j < max_capacity + 1; j++) {
			if (j < items[i - 1].weight) {
				table[i][j] = table[i - 1][j];
			}
			else {
				table[i][j] = std::max(table[i - 1][j], items[i - 1].profit + table[i - 1][j - items[i - 1].weight]);
			}

		}
	}

	// print table:
	for (int i = 0; i < items.size() + 1; i++) {
		for (int j = 0; j < max_capacity + 1; j++) {
			std::cout << table[i][j] << "\t";
		}
		std::cout << "\n" << std::endl;
	}

	int cap = max_capacity;
	int i = items.size(), j = max_capacity;
	while (cap > 0) {
		if (table[i][j] != table[i - 1][j]) {
			std::cout << " (weight-" << items[i - 1].weight << ";profit-" << items[i - 1].profit << ") " << "\t";
			cap = cap - items[i - 1].weight;
			j = j - items[i - 1].weight;
		}
		i--;
	}
}

int main() {

	std::deque<Item> items;
	items.push_back(Item(1, 2));
	items.push_back(Item(2, 3));
	items.push_back(Item(5, 4));
	items.push_back(Item(6, 5));
	int max_capacity = 8;

	run_zero_one_knapsack(items, max_capacity);

	return 0;
}