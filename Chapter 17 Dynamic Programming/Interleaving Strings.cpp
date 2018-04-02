bool interleave(const string& a, const string& b, const string& c) {
	if (a.size() + b.size() != c.size()) {
		return false;
	}

	vector<vector<bool>>arr(b.size() + 1, vector<bool>(a.size() + 1));
	arr[0][0] = 1;
	for (int col = 1; col < arr.front().size(); ++col) {
		if (a[col - 1] == c[col - 1]) {
			arr[0][col] = arr[0][col - 1];
		}
		else {
			arr[0][col] = false;
		}
	}
	for (int row = 1; row < arr.size(); ++row) {
		if (b[row - 1] == c[row - 1]) {
			arr[row][0] = arr[row - 1][0];
		}
		else {
			arr[row][0] = false;
		}
	}

	for (int row = 1; row < arr.size(); ++row) {
		for (int col = 1; col < arr[row].size(); ++col) {
			if (a[col - 1] == c[row + col - 1] && b[row - 1] == c[row + col - 1]) {
				arr[row][col] = arr[row - 1][col] || arr[row][col - 1];
			}
			else if (a[col - 1] == c[row + col - 1]) {
				arr[row][col] = arr[row][col - 1];
			}
			else if (b[row - 1] == c[row + col - 1]) {
				arr[row][col] = arr[row - 1][col];
			}
		}
	}

	return arr.back().back();
} // time O(nm); space O(nm);

bool interleave_better(string a, string b, const string& c) {
	if (a.size() + b.size() != c.size()) {
		return false;
	}
	if (a.size() > b.size()) {
		swap(a, b);
	}
	vector<bool>arr(a.size() + 1,false);
	arr.front() = 1;
	for (int col = 1; col < arr.size(); ++col) {
		if (a[col - 1] == c[col - 1]) {
			arr[col] = arr[col - 1];
		}
		else {
			arr[col] = false;
		}
	}

	for (int row = 0; row < b.size(); ++row) {
		arr[0] = b[row] == c[row] ? arr[0] : false;
		for (int col = 1; col < arr.size(); ++col) {
			if (a[col - 1] == c[row+col] && b[row] == c[row + col]) {
				arr[col] = arr[col] || arr[col - 1];
			}
			else if (a[col - 1] == c[row + col]) {
				arr[col] = arr[col - 1];
			}
			else if (b[row] == c[row + col]) {
				arr[col] = arr[col];
			}
			else {
				arr[col] = false;
			}
		}
	}
	return arr.back();
} // time O(nm); space O(min(n,m));

