// matched parens
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <assert.h>
using namespace std; 

void generate_helper(vector<string>&res,string curr,int left, int right);
vector<string> generate(int n) {
	vector<string>res;
	generate_helper(res, "", n, n);
	return res;
} // time O(2n!/(n!*(n+1)!)); space O(2n!/(n!*(n+1)!*n) + n for recursion

void generate_helper(vector<string>&res, string curr, int left, int right) {
	if (!left && !right) {
		res.emplace_back(curr);
		return;
	}
	if (left > 0) {
		generate_helper(res,curr+'(',left - 1, right);
	}
	if (right > left) {
		generate_helper(res, curr+')', left, right-1);
	}
}

void check(const vector<string>&vec) {
	for (int i = 0; i < vec.size(); ++i) {
		int open = 0;
		for (int j = 0; j < vec[i].size(); ++j) {
			if (vec[i][j] == ')') {
				assert(open-- != 0);
			}
			else if (vec[i][j] == '(') {
				++open;
			}
		}
	}
}

void main() {
	for (int i = 0; i < 10; ++i) {
		auto res = generate(i);
		check(res);
	}
	system("pause");
}
