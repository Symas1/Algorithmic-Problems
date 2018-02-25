// compute an optimum assigment of tasks
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
using namespace std;

struct Paired_task {
	int task_1, task_2;
};

vector<Paired_task> optimum_assigment(vector<int> durations) {
	sort(durations.begin(), durations.end());
	vector<Paired_task>res{};
	for (int i = 0, j = durations.size() - 1; i < j; ++i, --j) {
		res.emplace_back(Paired_task{ durations[i], durations[j] });
	}
	return res;
} // time O(nlogn); space O(1)

void main() {
	vector<int>durations{ 1,10,8,9 };
	auto res = optimum_assigment(durations);
	assert(res.size() == 2 && res[0].task_1 == 1 && res[0].task_2 == 10 && res[1].task_1 == 8 && res[1].task_2 == 9);
	system("pause");
}