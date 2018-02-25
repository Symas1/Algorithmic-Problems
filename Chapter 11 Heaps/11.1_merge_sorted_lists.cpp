// merge sorted lists
#include <queue>
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <functional>
#include <iterator>
#include <random>
#include <numeric>
using namespace std;

struct Node {
	Node(const int column_, const int arr_ind_) :column{ column_ }, array_index{ arr_ind_ } {};
	int column;
	int array_index;
};

vector<int> sort_files(const vector<vector<int>>&arr)
{
	priority_queue < Node, vector<Node>, function<bool(const Node&,const Node&)>> q{
		[&arr](const Node&first, const Node&second) 
	{return arr[first.array_index][first.column] > arr[second.array_index][second.column]; } };

	for (int i = 0; i < arr.size(); ++i)
	{
		if (!arr[i].empty())
		{
			q.emplace(0, i);
		}
	}

	vector<int>res{};
	while (!q.empty())
	{
		auto top = q.top();
		auto ind = top.column;
		auto array_index = top.array_index;
		res.emplace_back(arr[array_index][ind]);
		q.pop();
		if (ind + 1 < arr[array_index].size())
		{
			q.emplace(ind + 1, array_index);
		}
	}
	return res;
} // time O(nlog(k)) n - number of elements in files, k - number of files; space O(k) k - number of files


void main()
{
	vector<vector<int>> arr{ {3,5,7},{0,6},{0,6,28} };
	auto res = sort_files(arr);
	assert(equal(res.begin(), res.end(), vector<int>{ 0,0,3,5,6,6,7,28 }.begin()));

	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 1000; ++i)
	{
		vector<vector<int>>arr{};
		int subarrays = uniform_int_distribution<int>{ 0,20 }(mt);
		for (int j = 0; j < subarrays; ++j)
		{
			auto size = uniform_int_distribution<int>{ 0,20 }(mt);
			arr.emplace_back(vector<int>(size));
			generate(arr[j].begin(), arr[j].end(), [&mt]() 
			{return uniform_int_distribution<int>{ numeric_limits<int>::min(), numeric_limits<int>::max() }(mt); });
			sort(arr[j].begin(), arr[j].end());
		}
		auto check = sort_files(arr);
		assert(is_sorted(check.begin(), check.end()));
	}
	system("pause");
}
