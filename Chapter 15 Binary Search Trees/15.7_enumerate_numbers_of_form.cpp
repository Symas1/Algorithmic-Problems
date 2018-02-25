// enumerate numbers of form a + b*sqrt(2)
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <utility>
using namespace std;

double number(const int a, const int b)
{
	return a + b*sqrt(2);
}
vector<double> slow_enum(const int k)
{
	if (k <= 0)return{};
	map<double, pair<int, int>>map{ {0,{0,0}} };
	vector<double>res{};
	while (res.size() != k)
	{
		auto m = min_element(map.begin(), map.end());
		auto new_num1 = number(m->second.first + 1, m->second.second);
		auto new_num2 = number(m->second.first, m->second.second + 1);
		res.emplace_back(m->first);
		map.emplace(new_num1, pair<int, int>{ m->second.first + 1, m->second.second });
		map.emplace(new_num2, pair<int, int>{ m->second.first, m->second.second + 1 });
		map.erase(m);
	}
	return res;
} // time O(klogk); space O(k)

vector<double> fast_enum(const int k)
{
	if (k <= 0)return{};
	vector<double>res{0};
	int i = 0, j = 0;
	while (res.size() != k)
	{
		auto ith = res[i] + 1;
		auto jth = res[j] + sqrt(2);
		auto eps = fabs(ith - jth) / ith;
		if (ith < jth && eps > 0.0000000001)
		{
			res.emplace_back(ith);
			++i;
		}
		else if (jth < ith&& eps > 0.0000000001)
		{
			res.emplace_back(jth);
			++j;
		}
		else if(eps < 0.0000000001)
		{
			res.emplace_back(ith);
			++i, ++j;
		}
	}
	return res;
} // time O(k); space O(1)

void main()
{
	for (int i = 1; i <= 200; ++i)
	{
		auto res_slow = slow_enum(i);
		auto res_fast = fast_enum(i);
		assert(res_slow[0] == res_fast[0]);
		for (int j = 1; j < res_slow.size(); ++j)
		{
			auto eps = fabs(res_slow[j] - res_fast[j]) / res_slow[j];
			assert(eps < 0.00001);
		}
	}
	system("pause");
}