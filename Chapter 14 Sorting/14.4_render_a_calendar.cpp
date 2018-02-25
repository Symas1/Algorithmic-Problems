// render a calendar
#include <vector>
#include <utility>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <tuple>
using namespace std;

bool comp(const pair<bool, unsigned>&first, const pair<bool, unsigned>&second)
{
	if (first.second < second.second)return true;
	else if (first.second == second.second && first.first == false && second.first == true)return true;
	else return false;
}

int render(const vector<pair<unsigned, unsigned>>&events)
{
	vector<pair<bool, unsigned>>sorted{}; // 0 - start, 1 - end
	for (const auto& x : events)sorted.emplace_back(false,x.first), sorted.emplace_back(true,x.second);
	sort(sorted.begin(), sorted.end(), comp);
	int res = 0;
	int counter = 0;
	for (const auto& x : sorted)
	{
		if (x.first == false)
		{
			++counter;
			res = max(res, counter);
		}
		else if(x.first == true)--counter;
	}
	return res;
} // time O(nlogn); space O(n) for sorted array

bool comp_var(const tuple<bool, unsigned, unsigned>&first, const tuple<bool, unsigned, unsigned>&second)
{
	if (get<1>(first) < get<1>(second))return true;
	else if (get<1>(first) == get<1>(second) && get<0>(first) == false && get<0>(second) == true) return true;
	else return false;
}
unsigned variant1(const vector<tuple<unsigned, unsigned, unsigned>>&arr)
{
	vector<tuple<bool, unsigned, unsigned>>sorted{}; // false - start, true - end
	for (const auto&x : arr)
	{
		sorted.emplace_back(false, get<0>(x), get<2>(x));
		sorted.emplace_back(true, get<1>(x), get<2>(x));
	}
	sort(sorted.begin(), sorted.end(), comp_var);
	unsigned curr = 0, res = 0;
	for (const auto& x : sorted)
	{
		if (get<0>(x) == false)
		{
			curr += get<2>(x);
			res = max(res, curr);
		}
		else
		{
			curr -= get<2>(x);
		}
	}
	return res;
} // time O(nlogn); space O(n) for sorted array

void small_test();
void variant1_test();

void main()
{
	small_test();
	variant1_test();
	system("pause");
}

void small_test()
{
	vector<pair<unsigned, unsigned>>arr{ { 0,2 },{ 1,2 },{ 2,3 },{ 3,4 },{ 3,4 } };
	assert(render(arr) == 3);
}

void variant1_test()
{
	vector<tuple<unsigned,unsigned, unsigned>>arr{ { 0,2,5 },{ 1,2,10 },{ 2,3,15 },{ 3,4,20 },{ 3,4,20 } };
	assert(variant1(arr) == 55);
}