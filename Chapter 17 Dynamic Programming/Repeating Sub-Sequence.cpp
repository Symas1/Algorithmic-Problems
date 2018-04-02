int func(string str) {
	if (str.size() <= 2) {
		return 0;
	}
	vector<vector<int>>arr(str.size(), vector<int>(str.size(), 0));
	for (int row = 0; row < str.size(); ++row) {
		for (int col = row; col < str.size(); ++col) {
			if (col != row) {
				if (str[row] == str[col]) {
					arr[row][col] = (row - 1 >= 0 && col - 1 >= 0 ? arr[row - 1][col - 1] + 2 : 2);
				}
				else {
					int first = col - 1 >= 0 ? arr[row][col - 1] : 0;
					int second = row - 1 >= 0 ? arr[row-1][col] : 0;
					arr[row][col] = max(first,second);
				}
			}
		}
	}

	return arr[arr.size() - 2].back()>2;
} // time O(n^2); space O(n^2);

int func_better(string str) {
	if (str.size() <= 2) {
		return 0;
	}
	vector<int>arr(str.size());
	for (int row = 0; row < str.size(); ++row) {
		int diag = arr[row];
		for (int col = row+1; col < str.size(); ++col) {
			int diag_save = arr[col];
			if (col != row) {
				if (str[row] == str[col]) {
					arr[col] = diag + 2;
				}
				else {
					arr[col] = max(arr[col], arr[col - 1]);
				}
			}
			diag = diag_save;
		}
	}
	return arr.back() > 2;
} // time O(n^2); space O(n);