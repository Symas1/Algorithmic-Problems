// find the longest subarray with distinct entries
#include <unordered_map>
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>
#include <utility>
#include <unordered_set>
#include <random>
#include <algorithm>
using namespace std;

pair<int, int> subarray(const vector<int>&arr)
{
	if (arr.empty())return{ -1,-1 };
	unordered_map<int, int>indexes{};
	pair<int, int>result{ 0,0 };
	int start = 0, end = 0;
	indexes.emplace(arr[0], 0);
	for (int i = 1; i < arr.size(); ++i)
	{
		auto iter = indexes.find(arr[i]);
		if (iter == indexes.end())
		{
			indexes.emplace(arr[i], i);
		}
		else
		{
			if (iter->second < start)
			{
				iter->second = i;
			}
			else
			{
				start = iter->second + 1;
				iter->second = i;
			}
		}
		++end;
		if (end - start > result.second - result.first)
			result.first = start, result.second = end;
	}
	return result;
} // time O(n); space O(m) m - distinct elements

pair<int, int> brute_force(const vector<int>&arr)
{
	vector<pair<int, int>>result(arr.size());
	for (int i = 0; i < arr.size(); ++i)
	{
		unordered_set<int>set{};
		int start = i;
		int end = i;
		set.emplace(arr[i]);
		for (int j = i + 1; j < arr.size(); ++j)
		{
			if (!set.count(arr[j]))
			{
				++end;
				set.emplace(arr[j]);
			}
			else
			{
				break;
			}
		}
		result[i] = { start,end };
	}
	int max = 0;
	for (int i = 1; i < result.size(); ++i)
	{
		if (result[i].second - result[i].first > result[max].second - result[max].first)
			max = i;
	}
	return result[max];
}

void small_test();

void main()
{
	small_test();
	mt19937 mt{ random_device{}() };
	const int max_size = 100;
	for (int times = 0; times < 100; ++times)
	{
		vector<int>arr(uniform_int_distribution<int>{1, max_size}(mt));
		generate(arr.begin(), arr.end(), [&mt]() {return uniform_int_distribution<int>{0, 10000}(mt); });
		auto res1 = subarray(arr);
		auto res2 = brute_force(arr);
		assert(res1 == res2);
	}
	system("pause");
}

void small_test()
{
	vector<int>arr{ 1,2,1,3,4,5,3,6,4, 3 };
	auto res = subarray(arr);
	auto res2 = brute_force(arr);
	assert(res == res2);
}