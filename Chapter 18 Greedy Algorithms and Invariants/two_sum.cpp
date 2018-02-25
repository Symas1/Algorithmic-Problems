// two sum problem
#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;

bool has_two_sum(const vector<int>&arr, int sum) {
	for (int i = 0, j = arr.size() - 1; i <= j;) {
		if (arr[i] + arr[j] == sum) {
			return true;
		}
		else if (arr[i] + arr[j] < sum) {
			++i;
		}
		else{
			--j;
		}
	}
	return false;
} // time O(n); space O(1)

void main() {
	vector<int>arr{ 5,10,15,22,32 };
	assert(has_two_sum(arr, 27) && !has_two_sum(arr, 26) && !has_two_sum(arr, 2));
	system("pause");
}