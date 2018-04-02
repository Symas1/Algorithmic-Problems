int Solution::solve(int n) {
	int m = 1000000007;
	unsigned long long col_2 = 12;
	unsigned long long col_1 = 24;
	for (int i = 1; i < n; ++i) {
		unsigned long long new_col_2 = (7 * col_2 + 5 * col_1 )%m;
		unsigned long long new_col_1 = (10 * col_2 + 11 * col_1)%m;

		col_2 = new_col_2;
		col_1 = new_col_1;
	}
	return (col_2 + col_1) % m;
} // time O(n); space O(1)