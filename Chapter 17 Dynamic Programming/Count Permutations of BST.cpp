vector<vector<long long>> n_choose_k2(int n, int k) {
	long long m = 1000000007;
	vector<vector<long long>>save(n + 1, vector<long long>(k + 1));
	for (int i = 0; i <= n; ++i) {
		save[i][0] = 1;
	}
	for (int total = 1; total <= n; ++total) {
		for (int choose = 1; choose <= total && choose<=k; ++choose) {
			save[total][choose] = (save[total - 1][choose] + save[total - 1][choose - 1])%m;
		}
	}
	return save;
}

int perm(int n, int h) {
	if (n <= 1) {
		return h == 0 ? 1 : 0;
	}
	else if (h == 0) {
		return 0;
	}

	long long m = 1e9 + 7;
	vector<vector<long long>> save(n+1, vector<long long>(h+1, 0));
	save[0][0] = save[1][0] = 1;
	auto choose = n_choose_k2(n, n);
	
	for (int elems = 2; elems <= n; ++elems) {
		for (int height = 1; height < elems && height<=h; ++height) {
			for (int i = 1; i <= elems; ++i) {
				int left = i - 1;
				int right = elems - i;

				long long res = 0;

				for (int l_height = 0; l_height <= height - 2; ++l_height) {
					res =res+ (save[left][l_height] * save[right][height - 1])%m;
					res %= m;
				}
				for (int r_height = 0; r_height <= height - 2; ++r_height) {
					res =res+ (save[left][height-1] * save[right][r_height])%m;
					res %= m;
				}
				res = res+(save[left][height - 1] * save[right][height - 1])%m;
				res %= m;

				res *= choose[left+right][right];
				res %= m;

				save[elems][height] = (save[elems][height]+res)%m;
			}
		}
	}
	return save[n][h];
} // time O(n^4); space O(n^2)

inline int add_mod(int a, int b, int m) {
	a += b;
	if (a >= m)a -= m;
	return a;
}

inline int mult_mod(int a, int b, int m) {
	return a * 1LL * b % m;
}

int perm2(int n, int h) {
	const int m = 1e9 + 7;
	vector<vector<int>> save(n + 1, vector<int>(n + 1, 0));
	save[0][0] = save[1][0] = 1;
	auto choose = n_choose_k2(n, n);

	for (int i = 2; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) {
			int left = max(j - 1, 1);
			int right = max(i - j, 1);

			int sum = 0;
			for (int k = 0; k < left; ++k) {
				sum = add_mod(sum, save[i-j][k],m);
				int l = save[j - 1][k];
				save[i][k + 1] = add_mod(save[i][k + 1],mult_mod(mult_mod(l,sum,m),choose[i - 1][j - 1],m),m);
			}
			sum = 0;
			for (int k = 0; k < right; ++k) {
				int r = save[i - j][k];
				save[i][k + 1] = add_mod(save[i][k + 1], mult_mod(mult_mod(r, sum, m), choose[i - 1][j - 1], m), m);
				sum = add_mod(sum, save[j-1][k], m);
			}
		}
	}
	return save[n][h];
} // time O(n^3); space O(n^2)