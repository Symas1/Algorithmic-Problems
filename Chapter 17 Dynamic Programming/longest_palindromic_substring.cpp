
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include <random>
#include <algorithm>
using namespace std;

string longest(const string&str) {
	if (str.empty()) {
		return {};
	}
	vector<bool>arr(str.size(),true);
	int row = str.size() - 1;
	int col = str.size() - 1;
	for (int i = str.size() - 2; i >= 0; --i) {
		bool diagonal = true;
		for (int j = i+1; j < str.size(); ++j) {
			bool save = arr[j];
			if (str[i] == str[j]) {
				arr[j] = diagonal;
				if (diagonal&&col - row + 1 < j - i + 1) {
					row = i;
					col = j;
				}
			}
			else {
				arr[j] = false;
			}
			diagonal = save;
		}
	}
	return str.substr(row,col-row+1);
} // time O(n^2); space O(n)

pair<int, int>expand_around_center(const string&str, int low, int up);
string longest_better(const string&str) {
	if (str.empty()) {
		return {};
	}
	int res_low = 0;
	int res_up = 0;
	for (int start = 0; start < str.size()-1; ++start) {
		if (start >= ceil(str.size() / 2)) {
			int right = str.size() - 1 - start;
			if (1 + 2 * right <= res_up - res_low + 1) {
				break;
			}
		} // truncate useless operations

		auto expansion = expand_around_center(str, start - 1, start + 1);
		if (expansion.second - expansion.first > res_up - res_low) {
			res_low = expansion.first;
			res_up = expansion.second;
		}

		expansion = expand_around_center(str, start, start + 1);
		if (expansion.second - expansion.first > res_up - res_low) {
			res_low = expansion.first;
			res_up = expansion.second;
		}
	}
	return str.substr(res_low, (res_up - res_low + 1));
} // time O(n^2); space O(1)
pair<int, int>expand_around_center(const string&str, int low, int up) {
	while (low >= 0 && up < str.size()) {
		if (str[low] != str[up]) {
			break;
		}
		--low;
		++up;
	}
	return { low + 1,up - 1 };
}

string transform_string(const string& str) {
	string new_string(2*str.size()+1,'*');
	for (int i = 1; i < new_string.size(); i += 2) {
		new_string[i] = str[i / 2];
	}
	return new_string;
}

//https://articles.leetcode.com/longest-palindromic-substring-part-ii/
string longest_very_fast(const string& str) {
	if (str.empty()) {
		return {};
	}
	string t_str = transform_string(str);

	vector<int>arr(t_str.size());
	int center = 0;
	int right = 0;
	int max_idx = 0;
	for (int i = 1; i < t_str.size() - 1; ++i) {
		int i_mirror=2*center-i; // center-(i-center)
		arr[i] = right > i ? min(right - i, arr[i_mirror]) : 0;

		while (i + 1 + arr[i]<t_str.size()&& i - 1 - arr[i]>=0&&
			t_str[i + 1 + arr[i]] == t_str[i - 1 - arr[i]]) {
			++arr[i];
		}

		max_idx = arr[i] > arr[max_idx] ? i : max_idx;

		if (i + arr[i] > right) {
			right = i + arr[i];
			center = right - arr[i];
		}
	}

	return str.substr(max_idx/2-arr[max_idx]/2,arr[max_idx]);
} // time O(n); space O(n)

void main() {
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times) {
		string str(uniform_int_distribution<>{0, 4}(mt), '\0');
		generate(str.begin(), str.end(), [&mt]() {return uniform_int_distribution<>{'a','z'}(mt); });
		cout <<"str: "<< str << endl;

		auto res1 = longest(str);
		auto res2 = longest_better(str);
		auto res3 = longest_very_fast(str);
		cout << "res1: " << res1;
		cout << "\tres2: " << res2<<endl;
		cout << "\tres3: " << res3<<endl;
		assert(res1.size() == res2.size());
		assert(res3.size() == res2.size());
	}
	system("pause");
}