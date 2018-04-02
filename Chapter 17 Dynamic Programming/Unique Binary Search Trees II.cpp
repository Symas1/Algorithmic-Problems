int func(int n) {
	if (n == 0 || n == 1 || n == 2) {
		return n;
	}
	vector<int>save(n);
	save[0] = 1;
	save[1] = 2;

	for (int i = 2; i < n; ++i) {
		int sum = 0;
		for (int left = 0, right = i; left <= i; ++left, --right) {
			int left_val = left > 0 ? save[left - 1] : 1;
			int right_val = right > 0 ? save[right - 1] : 1;
			sum += (left_val * right_val);
		}
		save[i] = sum;
	}
	return save.back();
} // time O(n^2); space O(n)

int func2(int n) {
	if (n == 0) {
		return 0;
	}
	long double res = 1;
	for (long double i = 2; i <= n; ++i) {
		res *= (n + i) / i;
	}
	return round(res);
} // time O(n); space O(1)