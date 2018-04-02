
#include <vector>
#include <assert.h>
#include <iostream>
#include <algorithm>
using namespace std;

bool has_two_sum(vector<int>arr, int sum) {
	sort(arr.begin(), arr.end());
	for (int i = 0, j = arr.size() - 1; i < j;) {
		if (arr[i] + arr[j] == sum) {
			return true;
		}
		else if(arr[i] + arr[j]<sum){
			++i;
		}
		else{
			++j;
		}
	}
	return false;
} // time O(nlogn); space O(1)

void main() {
	assert(has_two_sum({ 1,4,3,2 }, 5));
	assert(!has_two_sum({ 1,4,3,2 }, 10));
	system("pause");
}