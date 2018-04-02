// unsigned catalan(unsigned n) {
// 	long double res = 1;
// 	for (long double i = 2; i <= n; ++i) {
// 		res *= (n + i) / i;
// 	}
// 	return llround(res)%1000000007;
// } // time O(n); space O(1)

int catalan2(unsigned n) {
	if (n == 0) {
		return 1;
	}
	vector<unsigned long long> cat(n + 1);
	cat[0] = 1;
	for (int i = 1; i < cat.size(); ++i) {
		for (int j = 0; j < i; ++j) {
			cat[i] += cat[j] * cat[i - 1 - j];
		    cat[i] %= 1000000007;
		}
	}
	return cat.back()%1000000007;
} // time O(n^2); space O(n)

int Solution::chordCnt(int n) {
    return catalan2(n);
}
