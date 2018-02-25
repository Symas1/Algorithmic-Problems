// compute the k most frequent queries
#include <unordered_map>
#include <assert.h>
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>
#include <utility>
#include <random>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;

size_t find_kth(vector<pair<string, unsigned>>&arr, int k);
size_t my_partition(vector<pair<string, unsigned>>&arr, size_t begin, size_t end, size_t pivot_index);
vector<string> compute(const vector<string>&queries, int k)
{
	unordered_map<string, unsigned>frequencies{};
	for (const auto& x : queries)
	{
		++frequencies[x];
	}

	vector<pair<string, unsigned>> arr(frequencies.begin(), frequencies.end());
	size_t kth_index = find_kth(arr, k);

	vector<string> res(arr.size() - kth_index);
	for (int i = kth_index, ind = 0; i < arr.size(); ++i, ++ind)
	{
		res[ind] = arr[i].first;
	}
	return res;
} // time worst-case O(n+m^2), average O(n+m); space O(m) m - queries
size_t find_kth(vector<pair<string, unsigned>>&arr, int k)
{
	assert(k <= arr.size() && k > 0);
	mt19937 mt{ random_device{}() };
	size_t begin = 0, end = arr.size() - 1;
	while (true)
	{
		size_t pivot = uniform_int_distribution<size_t>{ begin,end }(mt);
		pivot = my_partition(arr, begin, end, pivot);
		size_t diff = arr.size() - pivot;
		if (diff > k)begin = pivot + 1;
		else if (diff == k)return pivot;
		else if (diff < k)end = pivot - 1;
	}
	assert(false);
}
size_t my_partition(vector<pair<string, unsigned>>&arr, size_t begin, size_t end, size_t pivot_index)
{
	unsigned pivot = arr[pivot_index].second;
	swap(arr[pivot_index], arr[end]);
	size_t less = begin;
	while (begin < end)
	{
		if (arr[begin].second < pivot)swap(arr[begin++], arr[less++]);
		else if (arr[begin].second == pivot)++begin;
		else if (arr[begin].second > pivot)++begin;
	}
	swap(arr[less], arr[end]);
	return less;
}

vector<string> brute_compute(const vector<string>&queries, int k)
{
	unordered_map<string, unsigned>frequencies{};
	for (const auto& x : queries)
	{
		++frequencies[x];
	}

	vector<pair<string, unsigned>> arr(frequencies.begin(), frequencies.end());
	priority_queue < pair<string, unsigned>,
		vector<pair<string, unsigned>>,
		function<bool(const pair<string, unsigned>&,const pair<string, unsigned>&)>>
		q{ [](const pair<string, unsigned>& first,const pair<string, unsigned>& second)
	{return first.second > second.second; } };
	for (int i = 0; i < arr.size(); ++i)
	{
		if (i < k)
		{
			q.emplace(arr[i]);
			continue;
		}
		else
		{
			if (arr[i].second >= q.top().second)
			{
				q.pop();
				q.emplace(arr[i]);
			}
		}
	}

	vector<string> res{};
	while (!q.empty())
	{
		res.emplace_back(q.top().first);
		q.pop();
	}
	return res;
} // time O(n + mlogk); space O(m)

void small_test();

int main()
{
	small_test();
	system("pause");
	return 0;
}

void small_test()
{
	vector<string>arr{ "hello","hello","hi","hi","hi" };
	{
		auto res = brute_compute(arr, 1);
		assert(res[0] == "hi" && res.size()==1);
	}
	{
		auto res = compute(arr, 1);
		assert(res[0] == "hi"&&res.size()==1);
	}
}