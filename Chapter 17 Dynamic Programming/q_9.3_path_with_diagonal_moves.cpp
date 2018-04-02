
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <random>
using namespace std;

unsigned paths_exp(unsigned rows, unsigned cols) {
	if (rows == 0 || cols == 0) {
		return 1;
	}
	return paths_exp(rows - 1, cols) + paths_exp(rows, cols - 1) + paths_exp(rows - 1, cols - 1);
} // time O(3^n); space O(n+m)

unsigned paths(unsigned rows, unsigned cols) {
	if (cols > rows) {
		swap(cols, rows);
	}
	vector<unsigned>paths(cols+1, 1);
	for (int i = 1; i <= rows; ++i) {
		auto diag = paths[0];
		for (int j = 1; j < paths.size(); ++j) {
			auto save = paths[j];
			paths[j] = paths[j] + paths[j - 1] + diag;
			diag = save;
		}
	}
	return paths.back();
} // time O(n*m); space O(min(n,m))

void main() {
	assert(paths_exp(2, 3) == 25);
	assert(paths(2, 3) == 25);
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times) {
		auto rows = uniform_int_distribution<>{ 0,5 }(mt);
		auto cols = uniform_int_distribution<>{ 0,5 }(mt);
		assert(paths_exp(rows, cols) == paths(rows, cols));
	}
	system("pause");
}