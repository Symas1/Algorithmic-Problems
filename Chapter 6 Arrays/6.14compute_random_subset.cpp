// random subset
#include <vector>
#include <random>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <assert.h>
using namespace std;

//unordered_set<int> subset(int n, int length)
//{
//	unordered_set<int>set{};
//
//	mt19937 mt{ random_device{}() };
//	uniform_int_distribution<int> dist{ 0,n - 1 };
//	while (set.size() < length)
//	{
//		auto elem = dist(mt);
//		set.emplace(elem);
//	}
//	return set;
//}

vector<int> subset(int n, int length)
{
	unordered_map<int, int>map{};

	mt19937 mt{ random_device{}() };
	for (int i = 0; i < length; ++i)
	{
		auto index = uniform_int_distribution<int>{ i,n - 1 }(mt);


		auto find_index = map.find(index);
		auto find_i = map.find(i);

		if (find_index == map.end() && find_i == map.end())
		{
			map[index] = i;
			map[i] = index;
		}
		else if (find_index != map.end() && find_i == map.end())
		{
			map[i] = find_index->second;
			find_index->second = i;
		}
		else if (find_index == map.end() && find_i != map.end())
		{
			map[index] = find_i->second;
			find_i->second = index;
		}
		else if (find_index != map.end() && find_i != map.end())
		{
			swap(find_index->second, find_i->second);
		}
	}

	vector<int>res;
	for (int i = 0; i < length; ++i)
	{
		res.emplace_back(map[i]);
	}
	return res;
} // time O(k), space O(k)

void main()
{
	const int n = 20, l = 3;
	for (int i = 0; i < 10; ++i)
	{
		auto set = subset(n, l);
		copy(set.begin(), set.end(), ostream_iterator<int>{cout, " "});
		cout << endl;

		assert(set.size() == l);

		sort(set.begin(), set.end());

		vector<int>check(set.begin(), unique(set.begin(), set.end()));

		assert(equal(set.begin(), set.end(), check.begin(), check.end()));
	}
	system("pause");
}