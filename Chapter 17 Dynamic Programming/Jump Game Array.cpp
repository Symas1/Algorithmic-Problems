int can_jump(const vector<int>&arr) {
	vector<bool>potential(arr.size(), false);
	potential.front() = true;
	for (int idx = 0; idx < arr.size() - 1;++idx) {
		if (potential[idx]) {
			for (int i = arr[idx]; i > 0; --i) {
				if (idx + i < arr.size() && !potential[idx + i]) {
					potential[idx + i] = true;
				}
			}
		}
	}
	return potential.back();
} // time O(n^2); space O(n)

int can_jump_next(const vector<int>&arr) {
	if (arr.empty() || arr.size()==1) {
		return true;
	}

	int fuel = arr.front();
	for (int idx = 1; idx < arr.size(); ++idx) {
		if (!fuel) {
			break;
		}
		if (fuel + idx - 1 >= arr.size() - 1) {
			return true;
		}
		fuel = max(fuel - 1, arr[idx]);
	}
	return false;
} // time O(n); space O(1)