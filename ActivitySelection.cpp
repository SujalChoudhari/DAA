#include <iostream>
#include <algorithm>

// useful for sorting
struct Activity {
	int start;
	int end;
};

int* activity_selection(int* start, int* end, int size) {

	// Preparing for sorting
	Activity* activities = new Activity[size];
	for (int i = 0; i < size; i++) {
		activities[i] = { start[i], end[i] };
	}

	// sorting nased on end times
	std::sort(
		activities,
		activities + size,
		[](Activity a, Activity b) {return (a.end < b.end);}
	);

	// get the first activity
	int* selection = new int[size];
	int selection_index = 0;
	selection[0] = 1;

	// get the rest of the activities, only if the last selected activity ends before the current activity starts
	for (int i = 1; i < size; i++) {
		if (activities[i].start >= activities[selection_index].end) {
			selection_index = i;
			selection[i] = 1;
		}
		else {
			selection[i] = 0;
		}
	}

	return selection;

}

void run_activity_selection() {
	int size = 6;
	int start[] = { 1, 3, 0, 5, 8, 5 };
	int end[] = { 2, 4, 6, 7, 9, 9 };

	int* selection = activity_selection(start, end, size);
	std::cout << "Selection: " << std::endl;
	for (int i = 0; i < size; i++) {
		std::cout << selection[i] << " ";
	}
}



//int main() {
//	run_activity_selection();
//	return 0;
//}