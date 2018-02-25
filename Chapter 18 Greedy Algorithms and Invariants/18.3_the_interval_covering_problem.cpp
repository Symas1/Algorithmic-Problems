// the interval covering problem
#include <functional>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <iostream>
using namespace std;

vector<int> cover(vector < pair<int, int>>intervals) {
	if (intervals.empty()) {
		return{};
	}
	sort(intervals.begin(), intervals.end(), [](const pair<int, int>&f, const pair<int, int>&s)
	{return f.second < s.second; });

	vector<int>res{};
	for (int i = 0; i < intervals.size();) {
		res.emplace_back(intervals[i].second);
		++i;
		while (i<intervals.size()&&res.back() >=intervals[i].first) {
			++i;
		}
	}
	return res;
} // time O(nlogn); space O(1)

void main() {
	vector<pair<int, int>>arr{ {1,2},{2,3},{3,4},{2,3},{3,4},{4,5} };
	auto res = cover(arr);
	assert(res.size() == 2 && res[0] == 2 && res[1] == 4);
	system("pause");
}