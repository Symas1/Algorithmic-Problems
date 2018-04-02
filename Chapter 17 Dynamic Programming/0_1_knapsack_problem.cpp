
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <iterator>
#include <random>
using namespace std;

unsigned knapsack_dp(const vector<unsigned>weights, const vector<unsigned>&prices, const unsigned limit) {
	vector<unsigned>arr(limit + 1, 0);
	for (int i = 0; i < weights.size(); ++i) {
		for (int j = arr.size() - 1; j >= weights[i]; --j) {
			if (arr[j] < arr[j - weights[i]] + prices[i]) {
				arr[j] = arr[j - weights[i]] + prices[i];
			}
		}
	}
	return arr.back();
} // time O(limit*weights.size()); space O(limit)

pair<vector<unsigned>, unsigned> knapsack_dp_with_picked(const vector<unsigned>weights,
	const vector<unsigned>&prices, const unsigned limit) {
	vector<pair<vector<unsigned>, unsigned>>arr(limit + 1, { {},0 });
	for (int i = 0; i < weights.size(); ++i) {
		for (int j = arr.size() - 1; j >= weights[i]; --j) {
			if (arr[j].second < arr[j - weights[i]].second + prices[i]) {
				arr[j].first = arr[j - weights[i]].first;
				arr[j].first.emplace_back(i + 1);
				arr[j].second = arr[j - weights[i]].second + prices[i];
			}
		}
	}
	return arr.back();
} // time O(limit*weights.size()); space O(limit*weights.size())

void main() {
	assert(knapsack_dp({ 1,2,3 }, { 6,5,4 }, 5) == 11);
	auto res = knapsack_dp_with_picked({ 1,2,3 }, { 6,5,4 }, 5);
	cout << res.second << '\n';
	copy(res.first.begin(), res.first.end(), ostream_iterator<unsigned>{cout, " "});
	cout << endl;
	system("pause");
}