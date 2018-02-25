// find the closest entries in three sorted arrays
#include <vector>
#include <map>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <numeric>
#include <utility>
#include <functional>
#include <unordered_set>
#include <random>
#include <algorithm>
using namespace std;

int closest(const vector<int>&first, const vector<int>&second, const vector<int>&third)
{
	auto comp = [](vector<int>::const_iterator f, vector<int>::const_iterator s) {return *f < *s; };
	multimap<vector<int>::const_iterator,const vector<int>&,
		function<bool(vector<int>::const_iterator, vector<int>::const_iterator)>>map{comp};
	map.emplace(first.begin(),first );
	map.emplace(second.cbegin(),second );
	map.emplace(third.begin(),third );

	auto best = *max_element(map.begin(), map.end(),map.value_comp())->first - *min_element(map.begin(), map.end(), map.value_comp())->first;
	auto mini = min_element(map.begin(), map.end(), map.value_comp());
	while (next(mini->first) != mini->second.end())
	{
		auto next_el = next(mini->first);
		map.emplace(next_el, mini->second);
		map.erase(mini);
		mini = min_element(map.begin(), map.end(), map.value_comp());
		best = min(best, *max_element(map.begin(), map.end(), map.value_comp())->first - *min_element(map.begin(), map.end(), map.value_comp())->first);
	}
	return best;
} // time O(nlogk) k - arrays; space O(k) k - arrays

int brute(const vector<int>&first, const vector<int>&second, const vector<int>&third)
{
	int best = numeric_limits<int>::max();
	for (int i = 0; i < first.size(); ++i)
	{
		for (int j = 0; j < second.size(); ++j)
		{
			for (int k = 0; k < third.size(); ++k)
			{
				auto d = max(max(first[i], second[j]), third[k])-min(min(first[i], second[j]), third[k]);
				best = min(d,best);
			}
		}
	}
	return best;
} // time O(nml); space O(1)

void small_test();

void main()
{
	small_test();
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times)
	{
		const int max_size = 15;
		vector<int>first(uniform_int_distribution<>{1, max_size}(mt));
		vector<int>second(uniform_int_distribution<>{1, max_size}(mt));
		vector<int>third(uniform_int_distribution<>{1, max_size}(mt));
		generate(first.begin(), first.end(), [&mt]()
		{return uniform_int_distribution<>{0, numeric_limits<int>::max()}(mt); });
		generate(second.begin(), second.end(), [&mt]()
		{return uniform_int_distribution<>{0, numeric_limits<int>::max()}(mt); });
		generate(third.begin(),third.end(), [&mt]()
		{return uniform_int_distribution<>{0, numeric_limits<int>::max()}(mt); });
		sort(first.begin(), first.end());
		sort(second.begin(), second.end());
		sort(third.begin(), third.end());

		assert(closest(first, second, third) == brute(first, second, third));
	}
	system("pause");
}

void small_test()
{
	vector<int> first{ 5,10,15 };
	vector<int> second{ 3,6,9,12,15 };
	vector<int> third{ 8,16,24 };
	assert(closest(first, second, third) == 1 && brute(first, second, third) == 1);
}