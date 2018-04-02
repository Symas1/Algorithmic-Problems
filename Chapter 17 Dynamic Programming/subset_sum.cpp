
#include <vector>
#include <assert.h>
#include <iostream>
#include <random>
#include <unordered_set>
using namespace std;

bool subset_sum_rec_helper(const vector<unsigned>&nums, unsigned current_sum,
	unsigned select);
bool subset_sum_rec(const vector<unsigned>&nums, const unsigned target) {
	if (target == 0) {
		return true;
	}
	return subset_sum_rec_helper(nums, target, 0);
}
bool subset_sum_rec_helper(const vector<unsigned>&nums, unsigned current_sum,
	unsigned select) {
	if (current_sum == 0) {
		return true;
	}
	if (select == nums.size()) {
		return false;
	}

	if (nums[select] > current_sum) {
		return subset_sum_rec_helper(nums, current_sum, select + 1);
	}
	return subset_sum_rec_helper(nums, current_sum - nums[select], select + 1) ||
		subset_sum_rec_helper(nums, current_sum, select + 1);
} // time O(2^n); space O(nums.size())

void print_subset(const vector<vector<bool>>&arr, vector<unsigned>nums);
bool subset_sum_dp(const vector<unsigned>&nums, unsigned target) {
	if (target == 0) {
		return true;
	}
	if (nums.empty()) {
		return false;
	}
	vector<vector<bool>>sums(nums.size(), vector<bool>(target + 1, false));
	for (int i = 0; i < sums.size(); ++i) {
		sums[i][0] = true;
		for (int j = 1; j < sums[i].size(); ++j) {
			if (i - 1 >= 0) {
				sums[i][j] = sums[i - 1][j] || ((j - (int)nums[i] >= 0) ? sums[i - 1][j - nums[i]] : false);
			}
			else {
				if (nums[i] < sums.front().size()) {
					sums[i][nums[i]] = true;
				}
				break;
			}
		}
	}

	if (sums.back().back()) {
		print_subset(sums,nums);
	}

	return sums.back().back();
} // time O(nums.size()*target); space O(nums.size()*target)
void print_subset(const vector<vector<bool>>&arr,vector<unsigned>nums) {
	sort(nums.begin(), nums.end());
	int curr_row = arr.size() - 1;
	int curr_col = arr.front().size() - 1;
	unsigned total = 0;
	for (int i = nums.size() - 1; i >= 0 && curr_col!=0;--i) {
		if (nums[i] != 0) {
			if (curr_col - (int)nums[i] >= 0 && arr[curr_row][curr_col - (int)nums[i]]) {
				cout << nums[i] << " ";
				total += nums[i];
				curr_col = curr_col - (int)nums[i];
			}
		}
	}
	assert(total == arr.front().size()-1);
	cout << "\n";
}

bool subset_sum_dp_better(const vector<unsigned>&nums, unsigned target) {
	if (target == 0) {
		return true;
	}
	if (nums.empty()) {
		return false;
	}
	vector<vector<bool>>sums(2, vector<bool>(target + 1, false));
	sums[0][0] = sums[1][0] = true;
	for (int i = 0; i < nums.size(); ++i) {
		for (int j = nums[i]; j < sums[1].size(); ++j) {
			sums[1][j] = sums[0][j] || sums[0][j - (int)nums[i]];
		}
		sums[0] = sums[1];
	}

	if (sums.back().back()) {
		print_subset(sums, nums);
	}

	return sums.back().back();
} // time O(nums.size()*target); space O(target*2)

bool subset_sum_dp_best(const vector<unsigned>&nums, const unsigned target) {
	if (target == 0) {
		return true;
	}
	unordered_set<unsigned>achievable{ {0} };
	for (int i = 0; i < nums.size(); ++i) {
		unordered_set<unsigned>old_set = achievable;
		for (const auto& x : old_set) {
			unsigned sum = x + nums[i];
			if (sum >= x && sum >= nums[i] && sum<=target && !achievable.count(sum)) {
				achievable.emplace(sum);
				if (sum == target) {
					return true;
				}
			}
		}
	}
	return achievable.count(target);
} // time O(nums.size()^2); space O(target*2)

vector<unsigned> generate_set(unsigned size) {
	mt19937 mt{ random_device{}() };
	vector<unsigned>result(size);
	for (int i = 0; i < size; ++i) {
		result[i] = uniform_int_distribution<unsigned>{ 0,100 }(mt);
	}
	return result;
}

void golden_test();

void main() {
	golden_test();
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 3000; ++times) {
		//cout << times << '\n';
		auto set = generate_set(uniform_int_distribution<>{0, 10}(mt));
		auto target = uniform_int_distribution<unsigned>{ numeric_limits<unsigned>::min(),100 }(mt);
		cout << "Target: " << target << "\n";
		auto res1 = subset_sum_rec(set, target);
		auto res2 = subset_sum_dp(set, target);
		auto res3 = subset_sum_dp_better(set, target);
		auto res4 = subset_sum_dp_best(set, target);
		//if (res1 == true) {
		//	cout << "TRUE" << endl;
		//}
		assert(res1 == res4);
		assert(res1 == res2);
		assert(res2 == res3);
	}
	system("pause");
}

void golden_test() {
	assert(subset_sum_rec({ 3,2,7,1 }, 6));
	assert(!subset_sum_rec({ 3,2,7,1 }, 14));
	assert(subset_sum_dp({ 3,2,7,1 }, 6));
	assert(!subset_sum_dp({ 3,2,7,1 }, 14));
	assert(subset_sum_dp_better({ 3,2,7,1 }, 6));
	assert(!subset_sum_dp_better({ 3,2,7,1 }, 14));
	assert(subset_sum_dp_best({ 3,2,7,1 }, 6));
	assert(!subset_sum_dp_best({3,2,7,1 }, 14));
}