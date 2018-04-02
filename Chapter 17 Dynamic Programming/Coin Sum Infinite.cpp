
inline int add_mod(int a, int b, int m) {
	a += b;
	if (a >= m)a -= m;
	return a;
}

int ways(const vector<int>&coins, int sum) {
	vector<int>ways(sum + 1);
	ways[0] = 1;
	const int m = 1e6 + 7;
	for (const auto coin : coins) {
		for (int idx = coin; idx < ways.size(); ++idx) {
			ways[idx] = add_mod(ways[idx], ways[idx - coin], m);
		}
	}
	return ways.back();
} // time O(coins^2); space O(n)