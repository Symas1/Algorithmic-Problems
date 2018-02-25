// merging intervals
#include <vector>
#include <utility>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <random>
using namespace std;

vector<pair<int, int>> compute(const vector<pair<int, int>>&arr,pair<int,int>interval)
{
	size_t i = 0;
	vector < pair<int, int>>res{};
	while (i<arr.size() && interval.first > arr[i].second)
	{
		res.emplace_back(arr[i++]);
	}
	while (i < arr.size() && interval.second >= arr[i].first)
	{
		interval = { min(interval.first, arr[i].first), max(interval.second, arr[i].second) };
		++i;
	}
	res.emplace_back(interval);

	res.insert(res.end(), arr.begin() + i, arr.end());
	return res;
} // time O(n); space O(1)

bool check(const vector<pair<int, int>>&arr)
{
	for (int i = 1; i < arr.size(); ++i)
	{
		if (arr[i - 1].second >= arr[i].first)return false;
	}
	return true;
}

void small_test();

void main()
{
	small_test();
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times)
	{
		int size = uniform_int_distribution<>{ 0,100 }(mt);
		vector<pair<int, int>>arr{};
		int max = 0;
		for (int i = 0; i < size; ++i)
		{
			int left = uniform_int_distribution<>{ 1,10 }(mt)+max;
			max = left;
			int right = uniform_int_distribution<>{ 1,10 }(mt)+max;
			max = right;
			arr.emplace_back(left, right);
		}
		int left = uniform_int_distribution<>{ -1,max}(mt);
		int right = uniform_int_distribution<>{ left+1,max+1 }(mt);
		pair<int, int>interval{ left,right };
		arr = compute(arr, interval);
		assert(check(arr));
	}
	system("pause");
}

void small_test()
{
	vector<pair<int, int>>arr{ {1,5} };
	arr = compute(arr, { 0,3 });
	assert(arr.size() == 1 && arr.front().first == 0 && arr.front().second == 5 && check(arr));

	arr = compute(arr, { -2,-1 });
	assert(arr.size() == 2 && arr.front().first == -2 && arr.front().second == -1 && arr.back().first == 0 && arr.back().second == 5 &&
	check(arr));
}