// compute the maximum water trapped by a pair of vertical lines
#include <vector>
#include <iostream>
#include <assert.h>
#include <functional>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>
using namespace std;

int trapped(const vector<int>&arr) {
	int res = -1;
	for (int i = 0, j = arr.size() - 1; i < j;) {
		res = max(res, (j - i)*min(arr[i], arr[j]));
		if (arr[i] == arr[j]) {
			++i, --j;
		}
		else if (arr[i] < arr[j]) {
			++i;
		}
		else if (arr[i] > arr[j]) {
			--j;
		}
	}
	return res;
} // time O(n); space O(1)

int trapped_brute(const vector<int>&arr) {
	int res = -1;
	for (int i = 0; i < arr.size(); ++i) {
		for (int j = i + 1; j < arr.size(); ++j) {
			res = max(res, (j - i)*min(arr[i], arr[j]));
		}
	}
	return res;
} // time O(n^2); space O(1)

void small_test() {
	vector<int>arr{ 1,2,1,3,4,4,5,6,2,1,3,1,3,2,1,2,4,1 };
	assert(trapped(arr) == 48);
	assert(trapped_brute(arr) == 48);
}

void main() {
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 1000; ++i) {
		vector<int>arr(uniform_int_distribution<>{1, 100}(mt));
		generate(arr.begin(), arr.end(), [&mt]() {return uniform_int_distribution<>{1, 2000}(mt); });
		assert(trapped(arr) == trapped_brute(arr));
	}
	system("pause");
}