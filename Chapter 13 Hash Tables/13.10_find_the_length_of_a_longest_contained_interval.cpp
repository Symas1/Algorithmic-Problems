// find the length of the longest contained interval
#include<unordered_set>
#include <assert.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>
using namespace std;

int length(const vector<int>&arr)
{
	unordered_set<int>map{ arr.begin(),arr.end() };
	int longest = 0;
	while (!map.empty())
	{
		int current = 1;
		auto iter = map.begin();
		for (int left = (*iter) - 1;; --left)
		{
			auto left_it = map.find(left);
			if (left_it != map.end())
			{
				++current;
				map.erase(left_it);
			}
			else break;
		}
		for (int right = (*iter) + 1;; ++right)
		{
			auto right_it = map.find(right);
			if (right_it != map.end())
			{
				++current;
				map.erase(right_it);
			}
			else break;
		}
		map.erase(iter);
		longest = max(longest, current);
	}
	return longest;
} // time O(n), space O(m) m - distinct numbers

int brute(const vector<int>&arr)
{
	auto copy = arr;
	sort(copy.begin(), copy.end());
	auto iter = unique(copy.begin(), copy.end());
	copy.erase(iter, copy.end());
	int longest = 1;
	int current = 1;
	for (int i = 1; i < copy.size(); ++i)
	{
		if (copy[i] - 1 == copy[i - 1])++current;
		else
		{
			longest = max(longest, current);
			current = 1;
		}
	}
	longest = max(longest, current);
	return longest;
}

void small_test();

void main()
{
	small_test();
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times)
	{
		vector<int>arr(uniform_int_distribution<int>{1, 100}(mt));
		generate(arr.begin(), arr.end(), [&mt]() 
		{return uniform_int_distribution<int>{0,100}(mt); });
		assert(length(arr) == brute(arr));
	}
	system("pause");
}

void small_test()
{
	vector<int>arr{ 3,-2,7,9,8,1,2,0,-1,5,8 };
	assert(length(arr) == 6 && brute(arr)==6);
}