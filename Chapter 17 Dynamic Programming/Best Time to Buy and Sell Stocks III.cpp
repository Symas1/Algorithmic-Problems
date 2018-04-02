int two(const vector<int>&arr) {
	if (arr.empty()) {
		return 0;
	}
	vector<int>save(arr.size());
	int g_min = arr.front();
	int res = 0;
	for (int i = 1; i < arr.size(); ++i) {
		save[i] = max(save[i - 1], arr[i] - g_min);
		g_min = min(g_min, arr[i]);
	}
	int g_max = arr.back();
	for (int i = arr.size() - 2; i >= 0; --i) {
		res = max(res, g_max - arr[i] + (i - 1 >= 0 ? save[i - 1] : 0));
		g_max = max(g_max, arr[i]);
	}
	return res;
} // time O(n); space O(n)

int two_const(const vector<int>&arr) {
	if (arr.empty()) {
		return 0;
	}
	vector<int>profits{ 0,0 };
	vector<int>min_price{ numeric_limits<int>::max(),numeric_limits<int>::max() };
	for (const auto& price : arr) {
		for (int i = 1; i >= 0; --i) {
			profits[i] = max(profits[i], price - min_price[i]);
			min_price[i] = min(min_price[i], price - (i - 1 >= 0 ? profits[i - 1] : 0));
		}
	}
	return profits.back();
} // time O(n); space O(1)

int two_const_second(const vector<int>&arr) {
	int max_profit_first = 0;
	int max_profit_second = 0;
	int min_price_first = numeric_limits<int>::max();
	int min_price_second = numeric_limits<int>::max();
	for (const auto& p : arr) {
		max_profit_first = max(max_profit_first, p - min_price_first);
		min_price_first = min(min_price_first, p - max_profit_second);
		max_profit_second = max(max_profit_second, p - min_price_second);
		min_price_second = min(min_price_second, p);
	}
	return max_profit_first;
} // time O(n); space O(1)

https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/discuss/39611/Is-it-Best-Solution-with-O(n)-O(1).