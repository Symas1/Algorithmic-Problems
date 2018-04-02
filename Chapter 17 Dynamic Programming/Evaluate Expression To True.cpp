void print_arr(const vector<vector<pair<int, int>>>&arr) {
	for (int row = 0; row < arr.size(); ++row) {
		for (int col = 0; col < arr[row].size(); ++col) {
			cout << arr[row][col].first << " " << arr[row][col].second << "\t";
		}
		cout << endl;
	}
}

void add(const bool expr, int& zeros, int& ones, const int a, const int b);
bool expr(const bool a, const bool b, const char oper);
int ctr(const string& str) {
	int size = str.size() - str.size() / 2;
	vector<vector<pair<int,int>>>save(size, vector<pair<int, int>>(size));
	for (int i = 0; i < save.size(); ++i) {
		if (str[i * 2] == 'T') {
			++save[i][i].second;
		}
		else {
			++save[i][i].first;
		}
	}

	for (int row = size - 2; row >= 0; --row) {
		print_arr(save);
		cout << endl << endl;
		for (int col = row + 1; col < save[row].size(); ++col) {
			int zeros = 0;
			int ones = 0;
			for (int prev = row; prev < col; ++prev) {
				if (save[row][prev].first > 0 && save[prev + 1][col].first > 0) {
					auto zero_zero = expr(false, false, str[prev * 2 + 1]);
					add(zero_zero, zeros, ones, save[row][prev].first, save[prev + 1][col].first);
				}
				if (save[row][prev].first > 0 && save[prev + 1][col].second > 0) {
					auto zero_one = expr(false, true, str[prev * 2 + 1]);
					add(zero_one, zeros, ones, save[row][prev].first, save[prev + 1][col].second);
				}
				if (save[row][prev].second > 0 && save[prev + 1][col].first > 0) {
					auto one_zero = expr(true, false, str[prev * 2 + 1]);
					add(one_zero, zeros, ones, save[row][prev].second, save[prev + 1][col].first);
				}
				if (save[row][prev].second > 0 && save[prev + 1][col].second > 0) {
					auto one_one = expr(true, true, str[prev * 2 + 1]);
					add(one_one, zeros, ones, save[row][prev].second, save[prev + 1][col].second);
				}
			}
			save[row][col] = { zeros % 1003,ones % 1003 };
		}
	}
	print_arr(save);
	cout << endl << endl;

	return save.front().back().second;
} // time O(n^3); space O(n^2)
bool expr(const bool a, const bool b, const char oper) {
	if (oper == '|') {
		return a | b;
	}
	else if (oper == '&') {
		return a & b;
	}
	else if (oper == '^') {
		return a^b;
	}
}
void add(const bool expr, int& zeros, int& ones,const int a,const int b) {
	if (expr == false) {
		zeros += a * b;
	}
	else {
		ones += a * b;
	}
}