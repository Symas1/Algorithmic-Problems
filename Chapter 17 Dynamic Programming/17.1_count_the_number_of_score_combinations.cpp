// count the number of score combinations
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <random>
#include <assert.h>
#include <unordered_set>
#include <iterator>
#include <queue>
using namespace std;

int comb(int score, const vector<int>&individual_scores)
{
	vector<vector<int>>arr(2, vector<int>(score + 1, 0));
	arr[0][0] = 1;
	arr[1][0] = 1;
	for (int i = 0; i < individual_scores.size(); ++i)
	{
		for (int col = 0; col <= score; ++col)
		{
			int without_this_play = arr[0][col];
			int with_this_play = (col - individual_scores[i]) >= 0 ? arr[1][col - individual_scores[i]] : 0;
			arr[1][col] = without_this_play + with_this_play;
		}
		swap(arr[0], arr[1]);
	}

	return arr[0][score];
} // time O(n*nums.size()); space O(2n)

int comb2(int score, const vector<int>&numbers)
{
	vector<int>arr(score + 1, 0);
	arr[0] = 1;
	for (const auto& num : numbers)
	{
		for (int col = num; col < arr.size(); ++col)
		{
			arr[col] = arr[col] + arr[col - num];
		}
	}
	return arr.back();
} // time O(n*numbers.size()); space O(n)

int variant1(const vector<unsigned>&nums, const int score) {
	vector<unsigned>ways(score + 1, 0);
	ways[0] = 1;
	for (int curr_score = 1; curr_score < ways.size(); ++curr_score) {
		for (const auto num : nums) {
			if (num <= curr_score) {
				ways[curr_score] += ways[curr_score - num];
			}
		}
	}
	return ways.back();
} // time O(nums.size()*score); space O(score)

unsigned variant2(const vector<unsigned>&nums, const unsigned score1, const unsigned score2) {
	vector<unsigned>ways(max(score1, score2) + 1, 0);
	ways[0] = 1;
	for (const auto num : nums) {
		for (int i = num; i < ways.size(); ++i) {
			ways[i] += ways[i - num];
		}
	}
	return ways[score1] * ways[score2];
} // time O(nums.size()*max(score1,score2)); space O(max(score1,score2))

void variant3_helper(const vector<unsigned>&nums, const unsigned score1, const unsigned score2,
	const unsigned curr_score1, const unsigned curr_score2, bool score1_leads, unsigned curr_changes,
	unsigned& global_changes);
unsigned variant3(const vector<unsigned>&nums, const unsigned score1, const unsigned score2) {
	unsigned result = 0;
	variant3_helper(nums, score1, score2, 0, 0, false, 0, result);
	return result;
}
void variant3_helper(const vector<unsigned>&nums, const unsigned score1, const unsigned score2,
	const unsigned curr_score1, const unsigned curr_score2, bool score1_leads, unsigned curr_changes,
	unsigned& global_changes) {
	if (curr_score1 > score1 || curr_score2 > score2) {
		return;
	}
	if (curr_score1 == score1 && curr_score2 == score2) {
		global_changes = max(global_changes, curr_changes);
		return;
	}

	bool change_occured = false;
	if (curr_score1 < curr_score2 && score1_leads == true) {
		score1_leads = false;
		change_occured = true;
	}
	else if (curr_score2 < curr_score1 && !score1_leads) {
		score1_leads = true;
		change_occured = true;
	}

	for (const auto num : nums) {
		if (curr_score1 == 0 && curr_score2 == 0) {
			score1_leads = false;
		}
		variant3_helper(nums, score1, score2, curr_score1 + num, curr_score2,
			score1_leads, curr_changes + change_occured, global_changes);

		if (curr_score1 == 0 && curr_score2 == 0) {
			score1_leads = true;
		}
		variant3_helper(nums, score1, score2, curr_score1, curr_score2 + num,
			score1_leads, curr_changes + change_occured, global_changes);
	}
}

unsigned count_changes(const vector<unordered_set<unsigned>>&ways, const unsigned score1, const unsigned score2,
	bool first_starts);
unsigned variant3_better(const vector<unsigned>&nums, const unsigned score1, const unsigned score2) {
	vector<unordered_set<unsigned>>ways(max(score1, score2) + 1);
	for (int i = 1; i < ways.size(); ++i) {
		for (const auto num : nums) {
			if (i - (int)num >= 0 && !ways[i - num].empty()) {
				for (const auto& x : ways[i - num]) {
					ways[i].emplace(x);
				}
			}
			if (i - (int)num >= 0) {
				ways[i].emplace(num);
				if (!ways[i - num].empty()) {
					ways[i].emplace(i - num);
				}
			}

		}
	}
	copy(ways[score1].begin(), ways[score1].end(), ostream_iterator<unsigned>{cout, " "});
	cout << endl;
	copy(ways[score2].begin(), ways[score2].end(), ostream_iterator<unsigned>{cout, " "});
	cout << endl;

	if (ways[score1].empty() || ways[score2].empty()) {
		return 0;
	}

	ways[score1].emplace(score1);
	ways[score2].emplace(score2);

	return max(count_changes(ways, score1, score2, true), count_changes(ways, score1, score2, false));
}
unsigned count_changes(const vector<unordered_set<unsigned>>&ways, const unsigned score1, const unsigned score2,
	bool first_starts) {
	unsigned changes = 0;
	for (int i = 1; i < ways.size(); ++i) {
		if (first_starts && ways[score1].count(i)) {
			++changes;
			first_starts = false;
		}
		else if (!first_starts && ways[score2].count(i)) {
			++changes;
			first_starts = true;
		}
	}
	return changes;
}

unsigned variant3_width(const vector<unsigned>&nums, const unsigned score1, const unsigned score2) {
	vector<vector<unsigned>>history;
	history.front().emplace_back(vector<unsigned>{0});
	vector<unsigned>ways(max(score1, score2) + 1,0);
	ways[0] = 1;
	for (const auto num : nums) {
		for (int idx = num; idx < ways.size(); ++idx) {
			if (ways[num - idx] != 0) {
				ways[idx] += ways[num - idx];

			}
		}
	}
}


void test_main();
void test_variant3();

void main() {
	//test_main();
	test_variant3();
	system("pause");
}

void test_main() {
	assert(variant1({ 2,3,7 }, 12) == 18);
	assert(variant2({ 2,3,7 }, 12, 9) == 12);
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 100; ++i)
	{
		const int max_individual_numbers_size = 50;
		vector<int>individual_numbers(uniform_int_distribution<>{1, max_individual_numbers_size}(mt));
		generate(individual_numbers.begin(), individual_numbers.end(), [&mt]() {
			return uniform_int_distribution<>{1, 1000}(mt);
		});
		individual_numbers = vector<int>(individual_numbers.begin(), unique(individual_numbers.begin(),
			individual_numbers.end()));
		int score = uniform_int_distribution<>{ 1,999 }(mt);
		auto res1 = comb(score, individual_numbers);
		auto res2 = comb2(score, individual_numbers);
		assert(res1 == res2);
	}
}

void test_variant3() {
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 100; ++i) {
		vector<unsigned>nums(uniform_int_distribution<>{1,3}(mt));
		generate(nums.begin(), nums.end(), [&mt]() {
			return uniform_int_distribution<>{2, 5}(mt);
		});
		unsigned score1 = uniform_int_distribution<>{ 1,10 }(mt);
		unsigned score2 = uniform_int_distribution<>{ 1,10 }(mt);
		auto res1 = variant3(nums, score1,score2);
		auto res2 = variant3_better(nums, score1, score2);
		assert(res1 == res2);
	}
}