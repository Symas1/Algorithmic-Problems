// find the number of ways to traverse a 2d array
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <random>
using namespace std;

int ways(const int rows, const int cols) {
	vector<vector<int>>arr(rows, vector<int>(cols, 0));
	for (int i = 0; i < cols; ++i) {
		arr[0][i] = 1;
	}
	for (int i = 0; i < rows; ++i) {
		arr[i][0] = 1;
	}

	for (int i = 1; i < rows; ++i) {
		for (int j = 1; j < cols; ++j) {
			arr[i][j] = arr[i - 1][j] + arr[i][j - 1];
		}
	}
	return arr.back().back();
} // time O(n*m); space O(n*m)

int ways2(int rows, int cols) {
	if (cols > rows) {
		swap(cols, rows);
	}
	vector<int>arr(cols, 1);
	for (int i = 1; i < rows; ++i) {
		for (int j = 1; j < cols; ++j) {
			arr[j] = arr[j - 1] + arr[j];
		}
	}
	return arr.back();
} // time O(n*m); space O(min(rows,cols))

// (n+m-2)!/((n-1)!(m-1)!)

void main()
{
	assert(ways(5, 5) == 70);
	assert(ways2(5, 5) == 70);
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 100; ++i) {
		const int min_num = 1,max_num = 20;
		auto rows = uniform_int_distribution<>{ min_num,max_num }(mt);
		auto cols = uniform_int_distribution<>{ min_num,max_num }(mt);
		assert(ways(rows, cols) == ways2(rows, cols));
	}
	system("pause");
}