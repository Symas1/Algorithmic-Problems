void create_result(const vector<vector<int>>&index,const vector<int>&cuts,
	vector<int>&res, const int low, const int high) {
	if (high - low <= 1) {
		return;
	}
	res.emplace_back(cuts[index[low][high]]);
	create_result(index, cuts, res, low, index[low][high]);
	create_result(index,  cuts, res, index[low][high], high);
}

vector<int> Solution::rodCut(int length, vector<int> &cuts) {
    sort(cuts.begin(), cuts.end());
	cuts.emplace(cuts.begin(), 0);
	cuts.emplace_back(length);

	int size = cuts.size();

	vector<vector<int>>costs(size, vector<int>(size, 0));
	vector<vector<int>>index(size, vector<int>(size));

	for (int right = 2; right < size; ++right) {
		for (int left = 0; left + right < size; ++left) {
			int min_value = numeric_limits<int>::max();
			for (int cut = left + 1; cut < left + right; ++cut) {
				int curr_value = costs[left][cut] + costs[cut][left + right];
				if (curr_value < min_value) {
					min_value = curr_value;
					costs[left][left+right] = curr_value;
					index[left][left+right] = cut;
				}
			}
			costs[left][left+right] += cuts[left+right] - cuts[left];
		}
	}

	vector<int>result;
	create_result(index, cuts, result, 0, cuts.size() - 1);

	return result;
} // time O(n^3); space O(n^2)