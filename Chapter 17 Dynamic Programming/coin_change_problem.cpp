
#include <unordered_map>
#include <vector>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <random>
#include <unordered_set>
#include <queue>
using namespace std;

int coin_change_helper(const vector<int>&coins, unordered_map<int, int>&targets, int amount);
int coin_change(const vector<int>&coins, int amount) {
	if (amount == 0) {
		return 0;
	}
	unordered_map<int, int>targets;
	for (const auto& x : coins) {
		targets[x] = 1;
	}
	return coin_change_helper(coins, targets, amount);
} // time O(c*amount); space O(amount)
int coin_change_helper(const vector<int>&coins, unordered_map<int, int>&targets, int amount) {
	if (targets.count(amount)) {
		return targets[amount];
	}
	int result = -1;
	for (int i = coins.size() - 1; i >= 0; --i) {
		if (coins[i] < amount) {
			if (!targets.count(amount - coins[i])) {
				auto r = coin_change_helper(coins, targets, amount - coins[i]);
				targets.emplace(amount - coins[i], r);
			}
			if (targets[amount - coins[i]] != -1) {
				result = result == -1 ? targets[amount - coins[i]] + 1 :
					min(result, targets[amount - coins[i]] + 1);
			}
		}
	}
	return result;
}

int coin_change_dp(const vector<int>&coins, const int amount) {
	vector<int>ways(amount + 1, -1);
	ways[0] = 0;
	for (int i = 0; i < coins.size(); ++i) {
		for (int j = coins[i]; j < ways.size(); ++j) {
			if (ways[j - coins[i]] != -1) {
				ways[j] = ways[j] == -1 ? ways[j - coins[i]] + 1 : min(ways[j], ways[j - coins[i]] + 1);
			}
		}
	}
	return ways.back();
} // time O(c*amount); space O(amount)

int coin_change_bfs(const vector<int>&coins, const int amount) {
	if (amount == 0) {
		return 0;
	}
	queue<int>st{ {0} };
	queue<int>st_next;
	vector<bool>visited(amount + 1, false);
	visited[0] = true;
	int iter = 1;
	while (!st.empty()) {
		while (!st.empty())
		{
			auto top = st.front();
			st.pop();
			for (const auto&c : coins) {
				if (top + c == amount) {
					return iter;
				}
				else if (top + c < amount) {
					if (!visited[top + c]) {
						st_next.emplace(top + c);
						visited[top + c] = true;
					}
				}
			}
		}
		st = move(st_next);
		++iter;
	}
	return -1;
} // time O(c*amount); space O(amount)

void coin_change_dfs_helper(const vector<int>&coins, int amount, int curr_c, int idx, int&res);
int coin_change_dfs(vector<int>&coins, int amount) {
	sort(coins.begin(), coins.end());
	int res = numeric_limits<int>::max();
	coin_change_dfs_helper(coins, amount, 0, coins.size() - 1, res);
	return res == numeric_limits<int>::max() ? -1 : res;
} // time best-case O(nlogn), worst-case(const^coins.size()); space O(coins.size())
void coin_change_dfs_helper(const vector<int>&coins, int amount, int curr_c, int idx, int&res) {
	if (amount == 0) {
		res = curr_c;
		return;
	}
	else if (idx < 0 || amount < 0) {
		return;
	}

	int n = ceil(amount / coins[idx]);
	if (n + curr_c >= res) {
		return;
	}
	for (int i = n; i >= 0; --i) {
		coin_change_dfs_helper(coins, amount - (i*coins[idx]), curr_c + i, idx - 1, res);
	}
}

vector<int>random_coins(const int size) {
	mt19937 mt{ random_device{}() };
	unordered_set<int>res;
	for (int i = 0; i < size; ++i) {
		res.emplace(uniform_int_distribution<>{ 1, size }(mt));
	}
	return { res.begin(), res.end() };
}

void golden_test();

void main() {
	vector<int>arr{ 3,1,5,6 };
	coin_change_dfs(arr, 10);
	golden_test();
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times) {
		cout << times << endl;
		auto coins = random_coins(uniform_int_distribution<>{1, 10}(mt));
		auto amount = uniform_int_distribution<>{ 1,100 }(mt);

		auto res1 = coin_change(coins, amount);
		auto res2 = coin_change_dp(coins, amount);
		auto res3 = coin_change_bfs(coins, amount);
		auto res4 = coin_change_dfs(coins, amount);

		assert(res1 == res2);
		assert(res2 == res3);
		assert(res3 == res4);
	}
	system("pause");
}

void golden_test() {
	assert(coin_change({ 1,2,5 }, 11) == 3);
	assert(coin_change_dp({ 1,2,5 }, 11) == 3);
	assert(coin_change_bfs({ 1,2,5 }, 11) == 3);
	vector<int>arr = { 1,2,5 };
	assert(coin_change_dfs(arr, 11) == 3);
}