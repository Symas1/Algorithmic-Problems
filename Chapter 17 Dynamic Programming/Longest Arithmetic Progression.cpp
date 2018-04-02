int Solution::solve(const vector<int> &arr) {
 	vector<vector<pair<int, int>>>save(arr.size(),
		vector<pair<int, int>>(arr.size(), { 1,numeric_limits<int>::min() }));

	for (int col = 1; col < arr.size(); ++col) {
		save[0][col] = { 2,arr[col] - arr[0] };
	}

	int result = arr.size()>=2?2:1;
	for (int prev = 1; prev < arr.size() - 1; ++prev) {
		for (int next = prev + 1; next < arr.size(); ++next) {
			int diff = arr[next] - arr[prev];
			int same = 2;
			for (int prev_row = prev - 1; prev_row >= 0; --prev_row) {
				if (save[prev_row][prev].second == diff) {
					same = save[prev_row][prev].first + 1;
					break;
				}
			}
			save[prev][next] = { same,diff };
			result = max(result, save[prev][next].first);
		}
	}
	return result;
} // time O(n*(nm)) n - rows, m - cols; space O(nm) 
