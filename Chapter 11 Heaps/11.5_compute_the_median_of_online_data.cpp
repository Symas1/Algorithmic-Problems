// compute the median of online data
#include <vector>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
#include <iterator>
#include <random>
#include <numeric>
using namespace std;

vector<double> median(const vector<int>&arr)
{
	priority_queue<int, vector<int>, less<int>>max_heap{};
	priority_queue<int, vector<int>, greater<int>>min_heap{};
	vector<double>res{};
	for (int i = 0; i < arr.size(); ++i)
	{
		min_heap.emplace(arr[i]);
		max_heap.emplace(min_heap.top());
		min_heap.pop();
		if (max_heap.size() > min_heap.size())
		{
			min_heap.emplace(max_heap.top());
			max_heap.pop();
		}
		res.emplace_back(max_heap.size() == min_heap.size() ? (max_heap.top() + min_heap.top())*0.5 : min_heap.top());
	}
	return res;
} // time O(logn) per entry (for insertion and extraction); space O(n) n - elements

vector<double> median_brute(const vector<int>&arr)
{
	vector<double>res{};
	for (int i = 0; i < arr.size(); ++i)
	{
		vector<int> temp = { arr.begin(),arr.begin() + i + 1 };
		sort(temp.begin(), temp.end());
		res.emplace_back(i % 2 == 0 ? temp[i / 2] : (temp[i / 2] + temp[i / 2 + 1]) *0.5);
	}
	return res;
}

void small_check();

void main()
{
	small_check();
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times)
	{
		vector<int>arr(uniform_int_distribution<int>{1, 100}(mt));
		generate(arr.begin(), arr.end(), [&mt]() {return
			uniform_int_distribution<int>{numeric_limits<int>::min(), numeric_limits<int>::min()}(mt); });
		auto fast = median(arr);
		auto brute = median_brute(arr);
		assert(equal(fast.begin(), fast.end(), brute.begin(), brute.end()));
	}
	system("pause");
}

void small_check()
{
	vector<int>arr{ 1,0,3,5,2,0,1 };
	auto res = median_brute(arr);
	assert(equal(res.begin(), res.end(), vector<double>{1, 0.5, 1, 2, 2, 1.5, 1}.begin()));
	res = median(arr);
	assert(equal(res.begin(), res.end(), vector<double>{1, 0.5, 1, 2, 2, 1.5, 1}.begin()));
}