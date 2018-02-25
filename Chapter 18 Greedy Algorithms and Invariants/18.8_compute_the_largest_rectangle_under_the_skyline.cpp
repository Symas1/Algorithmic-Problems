// compute the largest rectangle under the skyline
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;

bool is_new_or_end(const vector<int>&b, int curr_idx, int last_pillar_idx);
int rect(const vector<int>&b) {
	stack<int>s{};
	int max_area = 0;
	for (int i = 0; i <= b.size(); ++i) {
		while (!s.empty() && is_new_or_end(b, i, s.top())) {
			int height = b[s.top()];
			s.pop();
			int width = s.empty() ? i : i - s.top() - 1;
			max_area = max(max_area, height*width);
		}
		s.emplace(i);
	}
	return max_area;
} // time O(n); space O(n)
bool is_new_or_end(const vector<int>&b, int curr_idx, int last_pillar_idx) {
	return curr_idx < b.size()
		? b[curr_idx] <= b[last_pillar_idx]
		: true;
}

int maximal_square(const vector<int>&heights) {
	if (heights.empty()) {
		return 0;
	}

	int result = 0;
	stack<int>hill;
	for (int i = 0; i <= heights.size(); ++i) {
		while (!hill.empty() && (i == heights.size() || heights[i] <= heights[hill.top()])) {
			int curr_idx = hill.top();
			hill.pop();

			int width = hill.empty() ? i : i - hill.top() - 1;
			int current_square = pow(min(width, heights[curr_idx]), 2);
			result = max(result, current_square);
		}
		hill.emplace(i);
	}
	return result;
} // time O(n); space O(n);

void main() {
	vector<int>arr{ 1,4,2,5,6,3,2,6,6,5,2,1,3 };
	assert(rect(arr) == 20);

	assert(maximal_square({ 2,1,5,6,2,3 }) == 4);
	assert(maximal_square({ 2,1,5,6,3,3 }) == 9);
	assert(maximal_square({ 2,1,1,1,1,3 }) == 1);
	system("pause");
}