#include <iostream>

struct MinMax {
	int min;
	int max;
};

MinMax minmax(int* array, int start_index, int end_index) {
	// if both the indices are same, i.e. the number is same. hence it is the min and the max
	if (start_index == end_index) {
		return { array[start_index], array[start_index] };
	}
	// if they are two distinct numbers but there is only one index difference, then the smaller number is min and larger is max.
	else if (start_index == end_index - 1) {
		if (array[start_index] > array[end_index]) {
			return { array[end_index], array[start_index] };
		}
		else {
			return { array[start_index], array[end_index] };
		}
	}
	// more than 2 indices, split the array in 2 parts (fairly equal halves) and then compare the mins and maxs of these arrays
	else {
		int mid = (start_index + end_index) / 2;
		MinMax minmax_left = minmax(array, start_index, mid);
		MinMax minmax_right = minmax(array, mid + 1, end_index);

		MinMax new_minmax = { std::min(minmax_left.min, minmax_right.min), std::max(minmax_left.max, minmax_right.max) };
		return new_minmax;
	}
}

int run_min_max() {
	int array[] = { 1, 20, 3, 4, 5, 6, 7, 8, 2, 10 };

	MinMax result = minmax(array, 0, 9);
	std::cout << result.min << " " << result.max << std::endl;
	return 0;
}


//int main() {
//	return run_min_max();
//}