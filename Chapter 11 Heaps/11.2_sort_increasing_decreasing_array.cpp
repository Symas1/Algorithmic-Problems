// sort and increasing-decreasing array
#include <vector>
#include <iostream>
#include <assert.h>
#include <queue>
#include <algorithm>
#include <functional>
#include <iterator>
#include <random>
#include <numeric>
using namespace std;

struct Node {
	Node(vector<int>::const_iterator first_, vector<int>::const_iterator last_) :first{ first_}, last{ last_} {};
	vector<int>::const_iterator first;
	vector<int>::const_iterator last;
};

vector<int> sort_q(vector<int>&arr)
{
	if (arr.size() <= 1)return{ arr };
	bool up = arr[0] > arr[1] ? false : true;
	auto start = arr.begin();
	auto comp = [&arr](const Node&first, const Node&second)
	{return *first.first > *second.first; };
	priority_queue<Node, vector<Node>, decltype(comp)>que{ comp };
	while (start!=arr.end())
	{
		if (up)
		{
			auto end = is_sorted_until(start, arr.end());
			que.emplace(start, end);
			start = end;
		}
		else
		{
			auto end = is_sorted_until(start, arr.end(), greater<int>{});
			reverse(start, end);
			que.emplace(start,end);
			start = end;
		}
		up ^= 1;
	}
	

	vector<int>res{};
	while (!que.empty())
	{
		auto top_node = que.top();
		que.pop();
		if (top_node.first != top_node.last)
		{
			res.emplace_back(*top_node.first);
			if (top_node.first == prev(top_node.last))continue;
			que.emplace(next(top_node.first), top_node.last);
		}
	}
	return res;
} // time O(nlogk) n - all elements, k - times increasing-decreasing; space O(k) k - times increasing-decreasing

void main()
{
	vector<int>test{ 57,131,493,294,221,339,418,452,442,190 };
	auto a = sort_q(test);
	assert(is_sorted(a.begin(), a.end())&&test.size()==a.size());

	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times)
	{
		vector<int>arr{};
		bool uphill = uniform_int_distribution<int>{ 0,1 }(mt);
		int left_elements = uniform_int_distribution<int>{ 0, 100 }(mt);
		while (left_elements)
		{
			vector<int>add(uniform_int_distribution<int>{ 1, left_elements }(mt));
			generate(add.begin(), add.end(), [&mt]()
			{return uniform_int_distribution<int>{ numeric_limits<int>::min(), numeric_limits<int>::max() }(mt); });
			if (uphill)
			{
				sort(add.begin(), add.end());
			}
			else
			{
				sort(add.begin(), add.end(), greater<int>{});
			}
			uphill ^=1;
			left_elements -= add.size();
			arr.insert(arr.end(), add.begin(),add.end());
		}
		auto check = sort_q(arr);
		assert(is_sorted(check.begin(), check.end())&&check.size()==arr.size());
	}
	system("pause");
}

