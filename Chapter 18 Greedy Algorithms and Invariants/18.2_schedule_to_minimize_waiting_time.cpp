// schedule to minimize waiting time
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
using namespace std;

int time(vector<int>times) {
	sort(times.begin(), times.end());
	int total_time = 0;
	for (int i = 0; i < times.size(); ++i) {
		total_time += times[i] * (times.size() -(i+1));
	}
	return total_time;
} // time O(nlogn); space O(1)

void main() {
	vector<int>times{ 2,5,1,3 };
	assert(time(times) == 10);
	system("pause");
}