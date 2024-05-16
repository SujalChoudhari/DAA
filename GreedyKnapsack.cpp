#include<algorithm>
#include <iostream>

// help to retuen required data to main function
struct Selection {
	float* selection;
	float profit;
};

// help to sort out the items
struct SackSelectionItem {
	int value;
	int weight;
	float profit_density;
};

Selection greedy_knapsack(int capacity, int size, int* value, int* weight) {

	// get data ready for sorting
	SackSelectionItem* items = new SackSelectionItem[size];
	for (int i = 0;i < size;i++) {
		items[i].value = value[i];
		items[i].weight = weight[i];
		items[i].profit_density = value[i] * 1.0f / weight[i];
	}

	// sort so that the most profitable items are first
	std::sort(items, items + size, [](SackSelectionItem a, SackSelectionItem b) {
		return (a.profit_density > b.profit_density);
		});

	float current_weight = 0;
	float* selection = new float[size];
	float current_profit = 0;
	for (int i = 0; i < size; i++) {
		// if I can pick it up
		if (current_weight + items[i].weight <= capacity) {
			current_weight += items[i].weight;
			current_profit += items[i].value;
			selection[i] = 1;
		}
		else {
			int remainder = capacity - current_weight;
			current_weight += remainder;
			current_profit += remainder * items[i].profit_density;
			selection[i] = remainder * 1.0f / items[i].weight;
		}
	}

	return  {
		selection, current_profit
	};

}




void run_greedy_knapsack() {
	int capacity = 20;
	int size = 3;
	int value[] = { 24,25,15 };
	int weight[] = { 18,15,20 };

	Selection result = greedy_knapsack(capacity, size, value, weight);
	std::cout << "Profit: " << result.profit << std::endl;
	std::cout << "Selection: " << std::endl;
	for (int i = 0; i < size; i++) {
		std::cout << result.selection[i] << " ";
	}

}

//int main() {
//
//	run_greedy_knapsack();
//	return 0;
//}