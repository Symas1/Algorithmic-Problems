int triangle(const vector<vector<int>>&arr) {
	vector<int>paths(arr.back().size(), 0);
	paths.front() = arr.front().front();
	for (int row = 1; row<arr.size(); ++row) {
		int save = paths.front();
		paths[arr[row].size() - 1] = paths[arr[row].size() - 2] + arr[row][arr[row].size() - 1];
		paths.front() = arr[row][0] + save;

		for (int col = 1; col<arr[row].size() - 1; ++col) {
			int new_save = paths[col];
			paths[col] = min(paths[col], save) + arr[row][col];
			save = new_save;
		}
	}
	return *min_element(paths.begin(), paths.end());
} // time O(n^2); space O(n)