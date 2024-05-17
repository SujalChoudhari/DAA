#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

// Structure to represent a job with processing times on two machines
struct Job {
	int id;
	int processingTime1;
	int processingTime2;
};

std::deque<Job> scheduleJobs(std::deque<Job>& jobs) {
	std::deque<Job> orderedJobs(jobs.size());
	int front_index = 0;
	int back_index = jobs.size() - 1;

	while (!jobs.empty()) {
		std::sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) { return a.processingTime1 < b.processingTime1; });
		Job min_job_for_a = jobs.front();

		std::sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) { return a.processingTime2 < b.processingTime2; });
		Job min_job_for_b = jobs.front();

		if (min_job_for_a.processingTime1 < min_job_for_b.processingTime2) {
			orderedJobs[front_index] = min_job_for_a;
			std::sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) { return a.processingTime1 < b.processingTime1; });
			front_index++;
			jobs.pop_front();
		}
		else {
			orderedJobs[back_index] = min_job_for_b;
			back_index--;
			std::sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) { return a.processingTime2 < b.processingTime2; });
			jobs.pop_front();
		}
	}

	return orderedJobs;
}


//int main() {
//	int n;
//	cout << "Enter the number of jobs: ";
//	cin >> n;
//
//	deque<Job> jobs(n);
//	cout << "Enter the processing times for each job on machine 1 and machine 2:\n";
//	for (int i = 0; i < n; i++) {
//		jobs[i].id = i + 1;
//		cin >> jobs[i].processingTime1 >> jobs[i].processingTime2;
//	}
//
//	std::deque<Job> orderedJobs = scheduleJobs(jobs);
//
//	for (auto job : orderedJobs) {
//		cout << job.id << " ";
//	}
//
//	return 0;
//}