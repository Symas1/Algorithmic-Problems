int coin_helper(const vector<int>&arr, const int low, const int up, bool my_turn);
int coin(const vector<int>&arr) {
	return coin_helper(arr, 0, arr.size() - 1, true);
} // time O(2^n); space O(n)
int coin_helper(const vector<int>&arr, const int low, const int up, bool my_turn) {
	if (low > up) {
		return 0;
	}
	else if (low == up) {
		return my_turn ? arr[low] : 0;
	}

	if (my_turn) {
		return max(arr[low] + coin_helper(arr, low + 1, up, !my_turn),
			arr[up] + coin_helper(arr, low, up - 1, !my_turn));
	}
	else {
		return min(coin_helper(arr, low + 1, up, !my_turn),
			coin_helper(arr, low, up - 1, !my_turn));
	}
} // time O(2^n); space O(n)


int coins_dp(const vector<int>&arr) {
	vector<vector<int>>res(arr.size(), vector<int>(arr.size()));
	for (int i = 0; i < arr.size(); ++i) {
		res[i][i] = arr[i];
	}
	vector<int>cumulative(arr.size());
	partial_sum(arr.begin(), arr.end(), cumulative.begin());
	for (int row = arr.size() - 2; row >= 0; --row) {
		for (int col = row + 1; col < arr.size(); ++col) {
			int c = row - 1 >= 0 ? cumulative[col] - cumulative[row - 1] : cumulative[col];
			res[row][col] = max(c - res[row + 1][col], c - res[row][col - 1]);
		}
	}
	return res.front().back();
} // time O(n^2); space O(n^2)

int coins_dp_better(const vector<int>&arr) {
	vector<int>res = arr;
	vector<int>cumulative(arr.size());
	partial_sum(arr.begin(), arr.end(), cumulative.begin());
	for (int row = arr.size() - 2; row >= 0; --row) {
		for (int col = row + 1; col < arr.size(); ++col) {
			int c = row - 1 >= 0 ? cumulative[col] - cumulative[row - 1] : cumulative[col];
			res[col] = max(c - res[col], c - res[col - 1]);
		}
	}
	return res.back();
} // time O(n^2); space O(n)

int coins_dp_next(const vector<int>&arr) {
	vector<vector<int>>save(arr.size(), vector<int>(arr.size()));

	for (int i = 0; i < arr.size(); ++i) {
		save[i][i] = arr[i];
	}

	for (int row = arr.size() - 2; row >= 0; --row) {
		for (int col = row + 1; col < save[row].size(); ++col) {
			int cand1 = save[row][row] + min(row + 2 < arr.size() ? save[row + 2][col] : 0,
				save[row + 1][col - 1]);
			int cand2 = save[col][col] + min(save[row + 1][col - 1],
				col - 2 >= 0 ? save[row][col - 2] : 0);
			save[row][col] = max(cand1, cand2);
		}
	}
	return save.front().back();
} // time O(n^2); space O(n^2) (O(3n) space possible)