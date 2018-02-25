// sort an almost-sorted array
#include <vector>
#include <iostream>
#include <assert.h>
#include <queue>
#include <functional>
#include <random>
#include <numeric>
#include <iterator>
using namespace std;

vector<int> my_sort(const vector<int>& data,const int k)
{
	vector<int>res{};
	priority_queue<int, vector<int>, greater<int>>q{};

	int next_k = 0;
	for (; next_k<= k && next_k < data.size(); ++next_k)
	{
		q.emplace(data[next_k]);
	}

	while (!q.empty())
	{
		res.emplace_back(q.top());
		q.pop();
		if (next_k < data.size())q.emplace(data[next_k++]);
	}

	return res;
} // time O(nlogk) n - elements, k - max distance to right position; space O(k)  k - max distance to right position

void main()
{
	vector<int>arr{ 3,-1,2,6,4,5,8 };
	auto res = my_sort(arr, 2);
	assert(is_sorted(res.begin(), res.end()) && res.size() == arr.size());
	mt19937 mt{ random_device{}() };

	for (int i = 0; i < 1000; ++i)
	{
		vector<int>arr(uniform_int_distribution<int>{2, 100}(mt));
		iota(arr.begin(), arr.end(), 0);
		int k = uniform_int_distribution<int>{ 1,static_cast<int>(arr.size() - 1) }(mt);
		auto iter = arr.begin();
		while (iter != arr.end())
		{
			mt.seed(random_device{}());
			if (distance(arr.begin(), iter) + k +1 >= arr.size())
			{
				shuffle(iter, arr.end(), mt);
				break;
			}
			shuffle(iter, iter + k +1 ,mt );
			advance(iter, k+1);
		}
		auto check = my_sort(arr, k);
		assert(is_sorted(check.begin(),check.end()) && check.size() == arr.size());
	}
	system("pause");
}