int princess_rec_helper(const vector<vector<int>>&arr, pair<int, int>pos, int curr_health, int initial) {
	curr_health += arr[pos.first][pos.second];
	if (curr_health <= 0) {
		initial += abs(curr_health) + 1;
		curr_health = 1;
	}

	int right = pos.second + 1 < arr.front().size() ? princess_rec_helper(arr, { pos.first,pos.second + 1 }, curr_health, initial) : numeric_limits<int>::max();
	int bottom = pos.first + 1 < arr.size() ? princess_rec_helper(arr, { pos.first + 1,pos.second }, curr_health, initial) : numeric_limits<int>::max();
	if (right == numeric_limits<int>::max() && bottom == numeric_limits<int>::max()) {
		return initial;
	}
	return min(right, bottom);
}
int princess_rec(const vector<vector<int>>&arr) {
	if (arr.empty()) {
		return 1;
	}
	return princess_rec_helper(arr, { 0,0 }, 1, 1);
} // time O(exp); space O(n+m)


int princess(const vector<vector<int>>&arr) {
	vector<vector<int>>paths(arr.size() + 1, vector<int>(arr.front().size() + 1, numeric_limits<int>::max()));
	paths[arr.size()][arr.front().size() - 1] = 1;
	paths[arr.size() - 1][arr.front().size()] = 1;

	for (int row = arr.size() - 1; row >= 0; --row) {
		for (int col = arr.front().size() - 1; col >= 0; --col) {
			int need = min(paths[row + 1][col], paths[row][col + 1]) - arr[row][col];
			paths[row][col] = need > 0 ? need : 1;
		}
	}
	return paths.front().front();
} // time O(n^2); space O(n^2)

int princess_better(const vector<vector<int>>&arr) {
	bool vertical = arr.front().size() < arr.size();
	vector<int>paths(vertical ? arr.front().size() + 1 : arr.size() + 1, numeric_limits<int>::max());
	paths.back() = 1;

	for (int iter = vertical ? arr.size() - 1 : arr.front().size() - 1; iter >= 0; --iter) {
		for (int col = paths.size() - 2; col >= 0; --col) {
			if (vertical) {
				int need = min(paths[col], paths[col + 1]) - arr[iter][col];
				paths[col] = need > 0 ? need : 1;
			}
			else {
				int need = min(paths[col], paths[col + 1]) - arr[col][iter];
				paths[col] = need > 0 ? need : 1;
			}
		}
		paths.back() = numeric_limits<int>::max();
	}
	return paths.front();
} // time O(n^2); space O(min(row,col))

vector<vector<int>> generate_vector(const int rows, const int cols) {
	const int low = -10;
	const int up = 10;
	vector<vector<int>>res(rows, vector<int>(cols));
	mt19937 mt{ random_device{}() };
	for (auto iter = res.begin(); iter != res.end(); ++iter) {
		generate(iter->begin(), iter->end(), [&mt, low, up]()
		{return uniform_int_distribution<>{low, up}(mt); });
	}
	return res;
}

void test();

void main() {
	test();
	system("pause");
}

void test() {
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times) {
		int rows = uniform_int_distribution<>{ 15,20 }(mt);
		int cols = uniform_int_distribution<>{ 15,20 }(mt);
		auto dungeon = generate_vector(rows, cols);
		auto res1 = princess(dungeon);
		auto res2 = princess_rec(dungeon);
		auto res3 = princess_better(dungeon);

		cout << "Dungeon:\n";
		for (auto iter = dungeon.begin(); iter != dungeon.end(); ++iter) {
			copy(iter->begin(), iter->end(), ostream_iterator<int>{cout, " "});
			cout << endl;
		}
		cout << "Result DP: " << res1;
		cout << "\t Result Rec: " << res2;
		cout << "\t Result DP_better: " << res3 << endl << endl;

		assert(res1 == res2);
		assert(res1 == res3);
	}
}