
#include <vector>
#include <assert.h>
#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
using namespace std;

void print_longest_botonic(const vector<int>&nums,const vector<int>&inc_path,
	const vector<int>&dec_path, const int start);
unsigned longest_botonic(const vector<int>&nums) {
	vector<int>longest_increasing(nums.size(), 1);
	vector<int>increasing_path(nums.size(), -1);
	for (int i = 0; i < nums.size(); ++i) {
		for (int j = i + 1; j < nums.size(); ++j) {
			if (nums[i] < nums[j]) {
				if (longest_increasing[i] + 1 > longest_increasing[j]) {
					longest_increasing[j] = longest_increasing[i] + 1;
					increasing_path[j] = i;
				}
			}
		}
	}

	vector<int>longest_decreasing(nums.size(), 1);
	vector<int>decreasing_path(nums.size(), -1);
	for (int i = nums.size() - 1; i >= 0; --i) {
		for (int j = i - 1; j >= 0; --j) {
			if (nums[j] > nums[i]) {
				if (longest_decreasing[i] + 1 > longest_decreasing[j]) {
					longest_decreasing[j] = longest_decreasing[i] + 1;
					decreasing_path[j] = i;
				}
			}
		}
	}

	int result = 1;
	int start = 0;
	for (int i = 0; i < nums.size(); ++i) {
		if (longest_increasing[i] + (longest_decreasing[i] - 1) > result) {
			result = longest_increasing[i] + (longest_decreasing[i] - 1);
			start = i;
		}
	}

	print_longest_botonic(nums, increasing_path, decreasing_path, start);
	return result;
} // time O(n^2); space O(n)
void print_longest_botonic_inc_helper(const vector<int>&nums, const vector<int>&inc_path, const int start);
void print_longest_botonic(const vector<int>&nums, const vector<int>&inc_path,
	const vector<int>&dec_path, const int start) {
	print_longest_botonic_inc_helper(nums, inc_path, start);
	for (int i = dec_path[start]; i < nums.size() && i!=-1;) {
		cout << nums[i] << " ";
		i = dec_path[i];
	}
	cout << '\n';
} // time O(n); space O(n) for recurcion
void print_longest_botonic_inc_helper(const vector<int>&nums, const vector<int>&inc_path, const int start) {
	if (start < 0) {
		return;
	}
	if (inc_path[start] != -1) {
		print_longest_botonic_inc_helper(nums, inc_path, inc_path[start]);
	}
	cout << nums[start] << " ";
}

void main() {
	assert(longest_botonic({ 1,4,6,8,3,-2 }) == 6);
	assert(longest_botonic({ 9,2,-4,-10,-15 }) == 5);
	assert(longest_botonic({ 1,2,3,4 }) == 4);
	assert(longest_botonic({ 1,3,12,4,2,10 }) == 5);
	assert(longest_botonic({ 1, 11, 2, 10, 4, 5, 2, 1 }) == 6);
	assert(longest_botonic({ 12, 11, 40, 5, 3, 1 }) == 5);
	assert(longest_botonic({ 80, 60, 30, 40, 20, 10 }) == 5);
	system("pause");
}