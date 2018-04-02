int min_jumps(const vector<int>&arr) {
	if (arr.size() == 1 || arr.empty()) {
		return 0;
	}

	vector<int>jumps(arr.size(), numeric_limits<int>::max());
	jumps[0] = 0;
	for (int i = 0; i < arr.size(); ++i) {
		if (jumps[i] != numeric_limits<int>::max()) {
			for (int j = arr[i]; j > 0; --j) {
				if (i + j >= arr.size() - 1) {
					return jumps[i] + 1;
				}
				jumps[i + j] = min(jumps[i + j], jumps[i] + 1);
			}
		}
	}
	return -1;
} // time O(n^2); space O(n);

int min_jumps_better(const vector<int>&arr) {
	if (arr.size() == 1 || arr.empty()) {
		return 0;
	}

	int jumps = 0;
	int max_advance = arr[0];
	for (int i = 0; i < arr.size();) {
		++jumps;
		if (max_advance >= arr.size() - 1) {
			return jumps;
		}
		
		int max_idx = -1;
		for (int j = max_advance; j >i; --j) {
			if (j + arr[j] > max_advance) {
				max_advance = j + arr[j];
				max_idx = j;
			}
		}
		if (max_idx == -1) {
			return -1;
		}
		i = max_idx;
	}
	return -1;
}// time O(n); space O(1)