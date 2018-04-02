int valid_dp_very_slow(const string& str) {
	vector<vector<int>>save(str.size(), vector<int>(str.size()));

	for (int row = str.size() - 2; row >= 0; --row) {
		for (int col = row + 1; col < str.size(); ++col) {
			int diag = 0;
			if (save[row + 1][col - 1] * 2 == col - row - 1) {
				diag = (str[row] == '(' && str[col] == ')') ? save[row + 1][col - 1] + 1 : 0;
			}
			for (int prev = row; prev < col; ++prev) {
				diag = max({ diag, save[row][prev],save[prev + 1][col] });
				if (save[row][prev] * 2 == prev - row + 1 && save[prev + 1][col] * 2 == col - prev) {
					diag = max(diag, save[row][prev] + save[prev + 1][col]);
				}
			}
			save[row][col] = diag;
		}
	}
	return save.front().back() * 2;
} // time O(n^3); space O(n^2)

int valid_dp(const string& str) {
	vector<int>save(str.size());
	int res = 0;
	for (int i = 1; i < str.size(); ++i) {
		if (str[i] == ')' && str[i - 1] == '(') {
			save[i] = i - 2 >= 0 ? save[i - 2] + 2 : 2;
		}
		else if (str[i] == ')' && str[i - 1] == ')') {
			if (i - save[i - 1] - 1 >= 0 && str[i - save[i - 1] - 1] == '(') {
				save[i] = i - save[i - 1] - 2 >= 0 ? save[i - save[i - 1] - 2] + 2 : 2;
				save[i] += save[i - 1];
			}
		}
		res = max(res, save[i]);
	}
	return res;
} // time O(n); space O(n)

int valid_stack(const string& str) {
	stack<int>s{ {-1} };
	int res = 0;
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == '(') {
			s.emplace(i);
		}
		else if (str[i] == ')') {
			s.pop();
			if (!s.empty()) {
				res = max(res, i - s.top());
			}
			else {
				s.emplace(i);
			}
		}
	}
	return res;
}; // time O(n); space O(n)

int valid_const(const string& str) {
	int res = 0;
	int left = 0;
	int right = 0;
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == '(') {
			++left;
		}
		else if (str[i] == ')') {
			++right;
			if (left == right) {
				res = max(res, left + right);
			}
			else if (right > left) {
				right = 0;
				left = 0;
			}
		}
	}
	left = 0;
	right = 0;
	for (int i = str.size() - 1; i >= 0; --i) {
		if (str[i] == '(') {
			++left;
			if (left == right) {
				res = max(res, left + right);
			}
			else if (left > right) {
				right = 0;
				left = 0;
			}
		}
		else if (str[i] == ')') {
			++right;
		}
	}
	return res;
} // time O(n); space O(1)