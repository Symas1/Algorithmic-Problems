int is_match(const string& a, const string& b) {
	if (b.empty() && !a.empty()) {
		return false;
	}

	vector<vector<bool>>arr(b.size() + 1, vector<bool>(a.size() + 1));
	arr[0][0] = true;
	for (int row = 1, stars = 0; row <= b.size(); ++row) {
		if (b[row - 1] == '*') {
			++stars;
		}

		for (int col = row - stars; col < arr.front().size(); ++col) {
			if (a[col - 1>=0?col-1:0] == b[row - 1] || b[row - 1] == '?') {
				arr[row][col] = arr[row - 1][col - 1];
			}
			else if (b[row - 1] == '*') {
				arr[row][col] = arr[row - 1][col] || (col-1>=0?arr[row][col - 1]:false);
			}
		}
	}
	return arr.back().back();
} // time O(nm); space O(nm);

int is_match_better(const string& a, const string& b) {
	if (b.empty() && !a.empty()) {
		return false;
	}

	vector<bool>arr(a.size() + 1, false);
	arr[0] = true;
	for (int row = 1,stars=0; row <= b.size(); ++row) {
		if (b[row - 1] == '*') {
			++stars;
		}
		bool diag =false;
		if (row - stars - 1 >= 0 && row-stars-1<arr.size()) {
			diag = arr[row - stars - 1];
			arr[row - stars - 1] = false;
		}
		for (int col = row - stars; col < arr.size(); ++col) {
			bool diag_save = arr[col];
			if (a[col - 1 >= 0 ? col - 1 : 0] == b[row - 1] || b[row - 1] == '?') {
				arr[col] = diag;
			}
			else if (b[row - 1] == '*') {
				arr[col] = (col - 1 >= 0 ? arr[col-1] : false) || arr[col];
			}
			else {
				arr[col] = false;
			}
			diag = diag_save;
		}
	}
	return arr.back();
} // time O(nm); space O(n)

bool is_match_better_better_helper(const char* a, const char* b);
bool is_match_better_better(const string& a, const string&b) {
	return is_match_better_better_helper(a.c_str(), b.c_str());
}
bool is_match_better_better_helper(const char* a, const char* b) {
	const char* star = nullptr;
	const char* star_pos = nullptr;
	while (*a) {
		if (*b == *a || *b == '?') {
			if (*b == '*') {
				star = b++;
				star_pos = a;
			}
			++a;
			++b;
		}
		else if (*b == '*') {
			star = b++;
			star_pos = a;
		}
		else {
			if (star) {
				b = star + 1;
				a = ++star_pos;
				continue;
			}
			return false;
		}
	}
	while (*b == '*') {
		++b;
	}
	return !*b;
} // time best-case O(n+m) worst-case O(nm); space O(1)