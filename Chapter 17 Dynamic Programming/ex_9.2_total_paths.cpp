
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <random>
using namespace std;

unsigned number_of_paths_exp(unsigned row, unsigned col) {
	if (row == 0 || col == 0) {
		return 1;
	}
	return number_of_paths_exp(row - 1, col) + number_of_paths_exp(row, col - 1);
} // time O(2^n); space O(n+m)

unsigned number_of_paths_n2_n2(unsigned row, unsigned col) {
	vector<vector<unsigned>>paths(row + 1, vector<unsigned>(col + 1, 0));
	for (int i = 0; i < paths.front().size();++i) {
		paths[0][i] = 1;
	}
	for (int i = 0; i < paths.size(); ++i) {
		paths[i][0] = 1;
	}

	for (int i = 1; i < paths.size(); ++i) {
		for (int j = 1; j < paths[i].size(); ++j) {
			paths[i][j] = paths[i - 1][j] + paths[i][j - 1];
		}
	}

	return paths.back().back();
} // time O(n*m); space O(n*m)

unsigned number_of_paths_n2_n(unsigned row, unsigned col) {
	if (col > row) {
		swap(row, col);
	}
	vector<unsigned>paths(col+1, 1);
	for (int i = 1; i <= row; ++i) {
		for (int j = 1; j < paths.size(); ++j) {
			paths[j] = paths[j - 1] + paths[j];
		}
	}
	return paths.back();
} // time O(n*m); space O(min(row,col))

// choose(n+m,n) or choose (n+m,m)

void main() {
	assert(number_of_paths_exp(3, 3) == 20);
	assert(number_of_paths_n2_n2(3, 3) == 20);
	assert(number_of_paths_n2_n(3, 3) == 20);
	mt19937 mt{ random_device{}() };
	for(int times=0;times<1000;++times){
		auto rows = uniform_int_distribution<>{ 0,100 }(mt);
		auto cols = uniform_int_distribution<>{ 0,100 }(mt);
		//auto res1 = number_of_paths_exp(rows, cols);
		auto res2 = number_of_paths_n2_n2(rows, cols);
		auto res3 = number_of_paths_n2_n(rows, cols);
		//assert(res1 == res2);
		assert(res2 == res3);
	}
	system("pause");
}