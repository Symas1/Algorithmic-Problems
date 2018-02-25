// find the nearest repeated entries in an array
#include <vector>
#include <iostream>
#include <assert.h>
#include <unordered_map>
#include <utility>
#include <numeric>
#include <string>
using namespace std;

pair<size_t, size_t> nearest(const vector<string>& arr)
{
	unordered_map<string, size_t>map{};
	pair<size_t, size_t>nearest{ numeric_limits<size_t>::min(),numeric_limits<size_t>::max() };
	for (size_t i = 0; i < arr.size(); ++i)
	{
		auto iter = map.find(arr[i]);
		if (iter != map.end())
		{
			if (nearest.second - nearest.first > i - iter->second)
			{
				nearest.first = iter->second;
				nearest.second = i;
			}
			iter->second = i;
		}
		else
		{
			map.emplace(arr[i], i);
		}
	}
	return nearest;
} // time O(n), space O(d) d - distinct entries in array

void main()
{
	vector<string>arr{};
	{
		arr = { "All","work","and","no","play","makes","for","no","work","no","fun","and","no","results" };
		auto res = nearest(arr);
		assert(res.first == 7 && res.second == 9);
	}
	{
		arr = { "foo","smth","foo","smth", "smth" };
		auto res = nearest(arr);
		assert(res.first == 3 && res.second == 4);
	}
	{
		arr = { "foo","c","a","b", "foo" };
		auto res = nearest(arr);
		assert(res.first == 0 && res.second == 4);
	}
	system("pause");
}