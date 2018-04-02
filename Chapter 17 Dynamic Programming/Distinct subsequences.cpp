void func_helper(const string& a, const string& b, const string& curr, const int select,int& res);
int func(string a,string b) {
	if (b.size() > a.size()) {
		return 0;
	}
	else if (b.size() == a.size()) {
		return a == b;
	}

	int res = 0;
	func_helper(a, b, {}, 0, res);
	return res;
} 
void func_helper(const string& a, const string& b, const string& curr, const int select, int& res) {
	if (curr.size() == b.size()) {
		if (curr == b) {
			++res;
		}
		return;
	}

	for (int i = select; a.size() - i >= b.size()-curr.size() && i < a.size(); ++i) {
		func_helper(a, b, curr + a[i], i + 1, res);
	}
}


int func_better(string a, string b) {
	if (b.size() > a.size()) {
		return 0;
	}
	vector<vector<int>>ways(b.size()+1, vector<int>(a.size()+1, 0));
	fill(ways.begin()->begin(), ways.begin()->end(), 1);
	for (int row = 1; row <= b.size(); ++row) {
		for (int col = row; col <= a.size(); ++col) {
			if (a[col-1] == b[row-1]) {
				ways[row][col] = ways[row][col - 1] + ways[row - 1][col - 1];
			}
			else {
				ways[row][col] = ways[row][col - 1];
			}
		}
	}
	return ways.back().back();
} // time O(nm); space O(nm);

int func_better_better(string a, string b) {
	if (b.size() > a.size()) {
		return 0;
	}
	vector<int>ways(a.size() + 1, 1);
	for (int row = 0; row < b.size(); ++row) {
		int diag = ways[row];
		ways[row] = 0;
		for (int col = row+1; col < ways.size(); ++col) {
			int diag_save = ways[col];
			if (a[col - 1] == b[row]) {
				ways[col] = ways[col - 1] + diag;
			}
			else {
				ways[col] = ways[col - 1];
			}
			diag = diag_save;
		}
	}
	return ways.back();
} // time O(nm); space O(n);