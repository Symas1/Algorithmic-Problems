
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <random>
#include <iterator>
using namespace std;

unsigned longest_subsequence_recursive_helper(const vector<int>&nums,unsigned idx);
unsigned longest_subsequence_recursive(const vector<int>&nums) {
	if (nums.empty()) {
		return 0;
	}
	return longest_subsequence_recursive_helper(nums, nums.size() - 1);
} // time O(2^n); space O(n)
unsigned longest_subsequence_recursive_helper(const vector<int>&nums, unsigned idx) {
	if (idx == 0) {
		return 1;
	}
	unsigned overall_max = 1;
	unsigned max_at_point = 1;
	for (int i = 0; i < idx; ++i) {
		unsigned candidate = longest_subsequence_recursive_helper(nums, i);
		if (nums[idx] > nums[i]) {
			overall_max = max(overall_max, candidate + 1);
			max_at_point = max(max_at_point,candidate+1);
		}
		else {
			overall_max = max(overall_max, candidate);
		}
	}
	if (idx == nums.size() - 1) {
		return overall_max;
	}
	return max_at_point;
}

void print_path(const vector<int>&nums, const vector<int>&path, const int start);
int longest_subsequence(const vector<int>&nums) {
	if (nums.empty()) {
		return 0;
	}
	vector<int>longest(nums.size(), 1);
	int res = 1;

	vector<int>path(nums.size(), -1); //
	int start = 0; //

	for (int i = 0; i < longest.size(); ++i) {
		for (int j = i+1; j < longest.size(); ++j) {
			if (nums[j] > nums[i]) {
				if (longest[i] + 1 > longest[j]) {
					longest[j] =longest[i] + 1;

					path[j] = i; //
					if (res < longest[j]) {
						res =longest[j];

						start = j; //
					}	
				}

			}
		}
	}

	print_path(nums, path, start);
	cout << endl;

	return res;
} // time O(n^2); space O(n)
void print_path(const vector<int>&nums, const vector<int>&path, const int start) {
	if (start < 0) {
		return;
	}
	if (path[start] != -1) {
		print_path(nums, path, path[start]);
	}
	cout << nums[start]<<" ";
}

int longest_subsequence_log(const vector<int>&nums) {
	if (nums.empty()) {
		return 0;
	}
	vector<int>longest{nums[0]};
	for (int i = 1; i < nums.size(); ++i) {
		if (nums[i] < longest[0]) {
			longest[0] = nums[i];
		}
		else if (nums[i] > longest.back()) {
			longest.emplace_back(nums[i]);
		}
		else {
			auto iter = lower_bound(longest.begin(), longest.end(), nums[i]);
			*iter = nums[i];
		}
	}
	copy(longest.begin(), longest.end(), ostream_iterator<int>{cout, " "});
	cout << endl;
	return longest.size();
} // time O(nlogn); space O(n)

vector<int> random_array(const unsigned size) {
	mt19937 mt{ random_device{}() };
	vector<int>result(size);
	for (int i = 0; i < result.size(); ++i) {
		result[i] = uniform_int_distribution<>{ numeric_limits<int>::min(),numeric_limits<int>::max() }(mt);
		//result[i] = uniform_int_distribution<>{ 0,9}(mt);
	}
	return result;
}

void golden_test();
void test();

void main() {
	golden_test();
	test();
	system("pause");
}

void golden_test() {
	assert(longest_subsequence({ 2,5,3,6 }) == 3);
	assert(longest_subsequence({ 2,3,4,18 }) == 4);
	assert(longest_subsequence({ 2,3,4,5,1,6 }) == 5);

	assert(longest_subsequence_recursive({ 2,5,3,6 }) == 3);
	assert(longest_subsequence_recursive({ 2,3,4,18 }) == 4);
	assert(longest_subsequence_recursive({ 2,3,4,5,1,6 }) == 5);

	assert(longest_subsequence_log({ 2,5,3,6 }) == 3);
	assert(longest_subsequence_log({ 2,3,4,18 }) == 4);
	assert(longest_subsequence_log({ 2,3,4,5,1,6 }) == 5);
}

void test() {
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times) {
		auto arr = random_array(uniform_int_distribution<>{0, 10}(mt));

		auto res1 = longest_subsequence_recursive(arr);
		auto res2 = longest_subsequence(arr);
		auto res3 = longest_subsequence_log(arr);
		assert(res1 == res2);
		assert(res2 == res3);
	}
	for (int times = 0; times < 1000; ++times) {
		auto arr = random_array(uniform_int_distribution<>{0, 1000}(mt));

		auto res2 = longest_subsequence(arr);
		auto res3 = longest_subsequence_log(arr);
		assert(res2 == res3);
	}
}