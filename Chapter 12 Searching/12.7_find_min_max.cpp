// find the min and max simultaneously
#include <vector>
#include <assert.h>
#include <iostream>
#include <functional>
#include <algorithm>
#include <random>
#include <numeric>
using namespace std;

pair<int, int> f(const vector<int>&arr)
{
	assert(!arr.empty());
	if (arr.size() == 1)return{ arr.front(),arr.front() };
	pair<int, int >res= minmax(arr[0], arr[1]);
	for (int i = 2; i + 1 < arr.size(); i += 2)
	{
		pair<int, int>curr = minmax(arr[i], arr[i + 1]);
		res.first = min(curr.first, res.first);
		res.second = max(curr.second, res.second);
	}

	if (arr.size() % 2)
	{
		res.first = min(res.first, arr.back());
		res.second = max(res.second, arr.back());
	}
	return res;
} // time O(1.5n); space O(1)

int main(int argc, char* argv[])
{
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times)
	{
		vector<int>arr(uniform_int_distribution<int>{1, 100}(mt));
		generate(arr.begin(), arr.end(), [&mt]() 
		{return uniform_int_distribution<int>{numeric_limits<int>::min(), numeric_limits<int>::max()}(mt); });
		auto my_res = f(arr);
		auto result = minmax_element(arr.begin(), arr.end());
		assert(my_res.first == *result.first && my_res.second == *result.second);
	}
	system("pause");
	return 0;
}