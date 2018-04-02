int sol(const vector<vector<int>>& arr) {
	if (arr.empty()) {
		return 0;
	}
	vector<vector<int>>sums(arr.size(), vector<int>(arr.front().size()));

	for (int row = 0; row < arr.size(); ++row) {
		int curr_sum = 0;
		for (int col = 0; col < arr[row].size(); ++col) {
			curr_sum += arr[row][col];
			sums[row][col] = curr_sum + (row - 1 >= 0 ? sums[row - 1][col] : 0);
		}
	}

	int res = 0;
	for (int row = 0; row < sums.size(); ++row) {
		for (int col = 0; col < sums[row].size(); ++col) {
			for (int minus_row = -1; minus_row < row; ++minus_row) {
				for (int minus_col = -1; minus_col < col; ++minus_col) {
					int bottom = minus_col >= 0 ? sums[row][minus_col] : 0;
					int top = minus_row >= 0 ? sums[minus_row][col] : 0;
					int diag = (minus_row >= 0 && minus_col >= 0) ? sums[minus_row][minus_col] : 0;

					int sum = sums[row][col] - bottom - top + diag;
					if (sum == 0) {
						++res;
					}
				}
			}
		}
	}
	return res;
} // time O(n^4); space O(n^2)

int sol2(const vector<vector<int>>& arr) {
	if (arr.empty()) {
		return 0;
	}
	vector<vector<int>>sums(arr.size(), vector<int>(arr.front().size()));

	for (int row = 0; row < arr.size(); ++row) {
		int curr_sum = 0;
		for (int col = 0; col < arr[row].size(); ++col) {
			curr_sum += arr[row][col];
			sums[row][col] = curr_sum + (row - 1 >= 0 ? sums[row - 1][col] : 0);
		}
	}

	int res = 0;
	for (int row1 = 0; row1 < sums.size(); ++row1) {
		for (int row2 = row1; row2 < sums.size(); ++row2) {
			unordered_map<int,int>prev_sums;
			for (int col = 0; col < sums[row2].size(); ++col) {
				int curr_sum = sums[row2][col] - (row1 > 0 ? sums[row1 - 1][col] : 0);
				if (curr_sum == 0)++res;
				if (prev_sums.count(curr_sum))res+=prev_sums[curr_sum];
				++prev_sums[curr_sum];
			}
		}
	}
	return res;
} // time O(n^3); space O(n^2)