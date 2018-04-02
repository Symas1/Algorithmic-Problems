vector<vector<int> > Solution::solve(int k, vector<vector<int> > &arr) {
    	auto res = arr;
	for (int k_iter = 1; k_iter <= k; ++k_iter) {
		auto new_res = res;
		for (int row = 0; row < res.size(); ++row) {
			for (int col = 0; col < res[row].size(); ++col) {
				if (col - 1 >= 0) {
					new_res[row][col] = max(new_res[row][col], res[row][col - 1]);
				}
				if (row - 1 >= 0) {
					new_res[row][col] = max(new_res[row][col], res[row - 1][col]);
				}
				if (col + 1 < res[row].size()) {
					new_res[row][col] = max(new_res[row][col], res[row][col + 1]);
				}
				if (row + 1 < res.size()) {
					new_res[row][col] = max(new_res[row][col], res[row+1][col]);
				}
			}
		}
		res = new_res;
	}
	return res;
} // time O(n*m*k); space O(n*m)