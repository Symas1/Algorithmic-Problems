int Solution::lis(const vector<int> &arr) {
    	if (arr.empty()) {
		return 0;
	}

	vector<int>d{ arr[0] };
	for (int i = 1; i < arr.size(); ++i) {
		if (arr[i] < d[0]) {
			d[0] = arr[i];
		}
		else if (arr[i] > d.back()) {
			d.emplace_back(arr[i]);
		}
		else {
			auto iter = lower_bound(d.begin(), d.end(), arr[i]);
			*iter = arr[i];
		}
	}
	return d.size();
}