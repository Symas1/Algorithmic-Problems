// find the minimum weight path in a triangle
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <numeric>
using namespace std;

int path(const vector<vector<int>>&triangle) {
	if (triangle.size() == 0) {
		return 0;
	}
	vector<int>current_minimum(triangle.back().size(), 0);
	current_minimum[0] = triangle.front().front();
	int res = triangle.front().front();
	for (int i = 1; i < triangle.size(); ++i) {
		for (int j = i; j > 0; --j) {
			if (j == i) {
				current_minimum[j] = current_minimum[j - 1] + triangle[i][j]; // right
				current_minimum[j - 1] += triangle[i][j - 1]; // left
				res = min({ current_minimum[j],current_minimum[j - 1] });
			}
			else {
				current_minimum[j] = min(current_minimum[j], current_minimum[j - 1] + triangle[i][j]);
				current_minimum[j - 1] += triangle[i][j - 1];
				res = min({res, current_minimum[j], current_minimum[j - 1]});
			}
		}
	}
	return res;
} // time O(n^2); space O(n)

void small_test() {
	vector<vector<int>>triangle{
		{ 2 },
		{ 4,4 },
		{ 8,5,6 },
		{ 4,2,6,2 },
		{ 1,5,2,3,4 }
	};
	assert(path(triangle) == 15);
}

void main() {
	small_test();
	system("pause");
}