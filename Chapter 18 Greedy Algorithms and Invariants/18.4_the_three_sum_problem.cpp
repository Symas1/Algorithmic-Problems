// the three sum problem
#include <vector>
#include <iostream>
#include <assert.h>
#include <random>
#include <algorithm>
#include <unordered_set>
using namespace std;

bool has_two_sum(const vector<int>&arr, int sum);
bool has_three_sum(vector<int>arr, int sum) {
	sort(arr.begin(), arr.end());

	for (const auto& x : arr) {
		if (has_two_sum(arr, sum - x)) {
			return true;
		}
	}
	return false;
} // time O(n^2); space O(1)
bool has_two_sum(const vector<int>&arr, int sum) {
	for (int i = 0, j = arr.size() - 1; i <= j;) {
		if (arr[i] + arr[j] == sum) {
			return true;
		}
		else if (arr[i] + arr[j] < sum) {
			++i;
		}
		else {
			--j;
		}
	}
	return false;
}

bool has_three_sum_hash(const vector<int>&arr, int sum) {
	unordered_set<int>set{};
	for (const auto&num : arr) {
		set.emplace(num);
	}

	for (int i = 0; i < arr.size(); ++i) {
		for (int j = i; j < arr.size(); ++j) {
			if (set.count(sum - (arr[i] + arr[j]))) {
				return true;
			}
		}
	}
	return false;
} // time O(n^2); space O(n)

void main() {
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 1000; ++i) {
		vector<int>arr(uniform_int_distribution<>{0, 100}(mt));
		generate(arr.begin(), arr.end(), [&mt]() {
			return uniform_int_distribution<>{0, 100}(mt);
		});
		int sum = uniform_int_distribution<>{ 0,10000 }(mt);
		assert(has_three_sum(arr, sum) == has_three_sum_hash(arr, sum));
	}
	system("pause");
}