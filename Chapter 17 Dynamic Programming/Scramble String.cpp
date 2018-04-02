int is_scramble_rec(const string& a, const string& b) {
	if (a == b) {
		return true;
	}
	if (a.size() != b.size()) {
		return false;
	}
	int size = a.size();
	unordered_set<char>letters;
	for (int i = 0; i < size; ++i) {
		if (letters.emplace(a[i]).second == false) {
			letters.erase(a[i]);
		}
		if (letters.emplace(b[i]).second == false) {
			letters.erase(b[i]);
		}
	}
	if (!letters.empty()) {
		return false;
	}

	for (int i = 1; i <= size - 1; ++i) {
		if (is_scramble_rec(a.substr(0, i), b.substr(0, i)) && is_scramble_rec(a.substr(i), b.substr(i))) {
			return true;
		}
		if (is_scramble_rec(a.substr(0, i), b.substr(size - i)) &&
			is_scramble_rec(a.substr(i), b.substr(0, size - i))) {
			return true;
		}
	}
	return false;
} // time O(exp - prunning); space O(n) - for recursion and set

int is_scramble_dp(const string& a, const string& b) {
	if (a.size() != b.size()) {
		return false;
	}
	int size = a.size();
	vector<vector<vector<bool>>>f(size, vector<vector<bool>>(size, vector<bool>(size+1, false)));
	for (int k = 1; k <= size; ++k) {
		for (int i = 0; i + k <= size; ++i) {
			for (int j = 0; j + k <= size; ++j) {
				if (k == 1) {
					f[i][j][k] = a[i] == b[j];
				}
				else {
					for (int q = 1; q < k && !f[i][j][k]; ++q) {
						f[i][j][k] = (f[i][j][q] && f[i + q][j + q][k - q]) ||
							(f[i][j + k - q][q] && f[i + q][j][k - q]);
					}
				}
			}
		}
	}
	return f[0][0][size];
} // time O(n^4); space O(n^3);
// https://leetcode.com/problems/scramble-string/discuss/29396/Simple-iterative-DP-Java-solution-with-explanation