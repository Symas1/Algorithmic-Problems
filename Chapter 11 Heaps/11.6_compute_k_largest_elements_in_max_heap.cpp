#include <queue>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <vector>
#include <functional>
#include <iterator>
#include <random>
#include <numeric>
using namespace std;

struct Heap_entry {
	Heap_entry(int ind_) :index{ ind_ } {};
	int index;
};

vector<int> compute(const vector<int>&heap, int k)
{
	if (k > heap.size())return{};
		
	priority_queue<Heap_entry, vector<Heap_entry>, function<bool(const Heap_entry&, const Heap_entry&)>>q{
		[&heap](const Heap_entry&first,const Heap_entry& second) {return heap[first.index] < heap[second.index]; }
	};

	vector<int> res{};
	q.emplace(0);
	while (res.size() != k)
	{
		auto curr_entry = q.top();
		q.pop();
		res.emplace_back(heap[curr_entry.index]);
		if (curr_entry.index * 2 + 1 < heap.size())q.emplace(curr_entry.index * 2 + 1);
		if (curr_entry.index * 2 + 2 < heap.size())q.emplace(curr_entry.index * 2 + 2);
	}
	return res;
} // time O(klogk); space O(k)

void test_main();

void main()
{
	test_main();
	system("pause");
}

void test_main()
{
	auto res = compute({ 561,314,401,28,156,359,271,11,3 }, 4);
	assert(res.size() == 4 && equal(res.begin(), res.end(), vector<int>{561,401,359,314}.begin()));
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times)
	{
		int size = uniform_int_distribution<int>{ 1,100 }(mt);
		priority_queue<int, vector<int>, less<int>>q{};
		for (int i = 0; i < size; ++i)
		{
			q.emplace(uniform_int_distribution<int>{numeric_limits<int>::min(), numeric_limits<int>::max()}(mt));
		}

		vector<int>arr{};
		while (!q.empty())
		{
			arr.emplace_back(q.top());
			q.pop();
		}

		int k = uniform_int_distribution<int>{ 1,static_cast<int>(arr.size()) }(mt);
		auto my_result = compute(arr, k);
		sort(my_result.begin(), my_result.end(), greater<int>{});
		sort(arr.begin(), arr.end(), greater<int>{});
		assert(equal(my_result.begin(), my_result.end(), arr.begin(), arr.begin() + k)&&my_result.size()==k);

	}
}