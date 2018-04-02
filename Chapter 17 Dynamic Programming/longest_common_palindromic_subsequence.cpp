
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <random>
using namespace std;

unsigned longest(const string&str) {
	if (str.empty()) {
		return 0;
	}
	vector<vector<unsigned>>arr(str.size(), vector<unsigned>(str.size(), 0));
	for (int i = 0; i < str.size(); ++i) {
		arr[i][i] = 1;
	}

	for (int size = 1; size < str.size(); ++size) {
		for (int row = 0; row < str.size() - size; ++row) {
			int col = size + row;
			if (str[row] == str[col]) {
				arr[row][col] = 2 + arr[row + 1][col - 1];
			}
			else {
				arr[row][col] = max(arr[row + 1][col], arr[row][col - 1]);
			}
		}
	}
	return arr.front()[str.size() - 1];
} // time O(n^2); space O(n^2)

unsigned longest_better(const string&str) {
	if (str.empty()) {
		return 0;
	}
	vector<unsigned>curr(str.size(), 1);
	vector<unsigned>prev(str.size(), 0);
	for (int size = 1; size < str.size(); ++size) {
		for (int row = 0; row < str.size() - size;++row) {
			int col = row + size;
			unsigned save = curr[row];
			if (str[row] == str[col]) {
				curr[row] = 2 + prev[row+1];
			}
			else {
				curr[row] = max(curr[row], curr[row+1]);
			}
			prev[row] = save;
		}
	}
	return curr.front();
} // time O(n^2); space O(n)

unsigned longest_better_better(const string&str) {
	if (str.empty()) {
		return 0;
	}
	vector<unsigned>arr(str.size(), 0);
	int diagonal;
	int save;
	for (int i = str.size() - 1; i >= 0; --i) {
		diagonal = 0;
		for (int j = i; j < str.size(); ++j) {
			if (i == j) {
				arr[j] = 1;
				continue;
			}
			save = arr[j];
			if (str[i] == str[j]) {
				arr[j] = 2 + diagonal;
			}
			else {
				arr[j] = max(arr[j], arr[j - 1]);
			}
			diagonal = save;
		}
	}
	return arr.back();
} // time O(n^2); space O(n)

string longest_palindromic2(const string&str) {
	vector<vector<unsigned>>arr(str.size(), vector<unsigned>(str.size(), 0));
	for (int i = 0; i < str.size(); ++i) {
		arr[i][i] = 1;
	}

	for (int size = 1; size < str.size(); ++size) {
		for (int row = 0; row < str.size() - size; ++row) {
			int col = size + row;
			if (str[row] == str[col]) {
				arr[row][col] = 2+arr[row+1][col-1];
			}
			else {
				arr[row][col] = max(arr[row + 1][col], arr[row][col - 1]);
			}
		}
	}

	string result(str.size(), '*');
	int row = 0;
	int col = str.size() - 1;
	while (col-row>=0) {
		if (str[row] == str[col]) {
			result[row] = result[col] = str[row];
			--col;
			++row;
		}
		else {
			if (arr[row][col - 1] > arr[row + 1][col]) {
				--col;
			}
			else {
				++row;
			}
		}
	}
	return { result.begin(),remove(result.begin(),result.end(),'*') };
}

void golden_test();

void main() {
	golden_test();
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times) {
		string str(uniform_int_distribution<>{0, 10}(mt), '\0');
		generate(str.begin(), str.end(), [&mt]() {return uniform_int_distribution<>{'a', 'z'}(mt); });
		cout <<"string: "<< str << '\n';


		auto res1 = longest(str);
		auto res2 = longest_better(str);
		auto res3 = longest_better_better(str);
		cout << "res1: " << res1 << "\tres2: " << res2 << "\tres3: "<<res3<<'\n';
		assert(res1 == res2);
		assert(res3 == res2);

		auto res4 = longest_palindromic2(str);
		cout << "res4: " << res4 << '\n';
		assert(res4.size()==res2);
	}
	system("pause");
}

void golden_test() {
	assert(longest("avcca") == 4);
	assert(longest("bbbab") == 4);
	assert(longest_better("avcca") == 4);
	assert(longest_better("bbbab") == 4);
	assert(longest_better_better("avcca") == 4);
	assert(longest_better_better("bbbab") == 4);
}