// pick up coins for maximum gain
#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;

int max_revenue_helper(const vector<int>&coins, vector<vector<int>>&revenues, int a, int b);
int max_revenue(const vector<int>&coins) {
	vector<vector<int>>revenues(coins.size(), vector<int>(coins.size(),0));
	return max_revenue_helper(coins, revenues, 0, coins.size() - 1);
} // time O(n^2); space O(n^2) n - number of coins
int max_revenue_helper(const vector<int>&coins, vector<vector<int>>&revenues, int a, int b) {
	if (a > b) {
		return 0;
	}

	if (revenues[a][b] == 0) {
		auto left = coins[a] + min(max_revenue_helper(coins, revenues, a + 2, b),
			max_revenue_helper(coins, revenues, a + 1, b - 1));
		auto right = coins[b] + min(max_revenue_helper(coins, revenues, a, b-2),
			max_revenue_helper(coins, revenues, a + 1, b - 1));
		revenues[a][b] = max(left, right);
	}

	return revenues[a][b];
}

void small_test() {
	vector<int>coins{ 10,25,5,1,10,5 };
	assert(max_revenue(coins) == 31);
	coins = { 5,10 };
	assert(max_revenue(coins) == 10);
	coins = { 25,5,10,5,10,5,10,25,1,25,1,25,1,25,5,10 };
	assert(max_revenue(coins) == 140);
}

void main() {
	small_test();
	system("pause");
}