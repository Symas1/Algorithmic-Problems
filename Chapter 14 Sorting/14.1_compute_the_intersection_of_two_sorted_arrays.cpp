// compute the intersection of two sorted arrays
#include <vector>
#include <assert.h>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <random>
using namespace std;

vector<int> compute(const vector<int>& first, const vector<int>& second)
{
	vector<int>res{};
	auto iter_first = first.begin();
	auto iter_second = second.begin();
	while (iter_first != first.end() && iter_second != second.end())
	{
		while (iter_first != first.end() && iter_second != second.end())
		{
			if (*iter_first < *iter_second)iter_first = next(iter_first);
			else if (*iter_second < *iter_first)iter_second = next(iter_second);
			else break;
		}
		if(iter_first != first.end() && iter_second != second.end())
			res.emplace_back(*iter_first);
		else break;
		int num_to_skip = *iter_first;
		while (iter_first != first.end() && iter_second != second.end())
		{
			if (*iter_first == num_to_skip)iter_first = next(iter_first);
			else if (*iter_second == num_to_skip)iter_second = next(iter_second);
			else break;
		}
	}
	return res;
} // time O(m+n), space O(1)

vector<int> brute(const vector<int>&first, const vector<int>&second)
{
	vector<int>res{};
	for (int i = 0; i < first.size(); ++i)
	{
		if ((i == 0 || first[i] != first[i - 1]) && binary_search(second.begin(), second.end(), first[i]))
			res.emplace_back(first[i]);
	}
	return res;
}

void main()
{
	vector<int>first{ 2,3,3,5,5,6,7,7,8,12 };
	vector<int>second{ 5,5,6,8,8,9,10,10 };
	auto res = compute(first, second);
	assert(equal(res.begin(), res.end(), vector<int>{5, 6, 8}.begin()));
	res = brute(first, second);
	assert(equal(res.begin(), res.end(), vector<int>{5, 6, 8}.begin()));
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times)
	{
		const int m = 1000;
		vector<int>first(uniform_int_distribution<>{0, m}(mt));
		vector<int>second(uniform_int_distribution<>{0, m}(mt));
		generate(first.begin(), first.end(), [&mt]() {return uniform_int_distribution<>{numeric_limits<int>::min(), numeric_limits<int>::max()}(mt); });
		generate(second.begin(), second.end(), [&mt]() {return uniform_int_distribution<>{numeric_limits<int>::min(), numeric_limits<int>::max()}(mt); });
		sort(first.begin(), first.end());
		sort(second.begin(), second.end());
		auto fast = compute(first, second);
		auto slow = brute(first, second);
		assert(equal(fast.begin(), fast.end(), slow.begin(), slow.end()));
	}
	system("pause");
}