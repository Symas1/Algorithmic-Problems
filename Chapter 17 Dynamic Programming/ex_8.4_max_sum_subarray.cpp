
#include <vector>
#include <iostream>
#include <assert.h>
#include <numeric>
#include <algorithm>
#include <random>
using namespace std;

int kadane(const vector<int>&arr) {
	int result = numeric_limits<int>::min();
	int curr_sum = 0;
	for (const auto& x : arr) {
		curr_sum += x;
		result = max(result, curr_sum);
		curr_sum = max(curr_sum, 0);
	}
	return result;
} // time O(n); space O(1)

pair<int, int> find_arr_helper(const vector<int>&arr, int n);
int find_arr(const vector<int>&arr) {
	return find_arr_helper(arr, arr.size() - 1).second;
} // time O(n); space O(n)
pair<int, int> find_arr_helper(const vector<int>&arr, int n) {
	if (n == 0) {
		return{ arr[n],arr[n] };
	}
	auto lower = find_arr_helper(arr, n - 1);
	return { max(lower.first + arr[n],arr[n]),max(max(lower.first + arr[n],arr[n]),lower.second) };
}

vector<int> rand_vec(unsigned size) {
	mt19937 mt{ random_device{}() };
	vector<int>res(size, 0);
	for (int i = 0; i < size; ++i) {
		res[i] = uniform_int_distribution<>{ -1000,1000 }(mt);
	}
	return res;
 }

void main() {
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 10000; ++times) {
		auto arr = rand_vec(uniform_int_distribution<>{1, 100}(mt));
		auto res1 = kadane(arr);
		auto res2 = find_arr(arr);
		assert(res1 == res2);
	}
	system("pause");
}
