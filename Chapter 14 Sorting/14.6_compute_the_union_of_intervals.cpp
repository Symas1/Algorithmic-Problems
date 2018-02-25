// compute the union of intervals
#include <vector>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <random>
using namespace std;


struct Interval
{
	Interval(int st, int en, bool st_o, bool en_o) :start{ st }, end{ en }, start_open{ st_o }, end_open{ en_o } {};
	int start, end;
	bool start_open, end_open;
};
void print(const vector<Interval>&arr);

bool comp(const Interval& first, const Interval& second)
{
	if (first.start < second.start)return true;
	else if (first.start == second.start && first.start_open && !second.start_open)return true;
	else return false;
}

bool is_intersect(const Interval& first, const Interval& second)
{
	if (first.start <= second.end && first.end > second.start)return true;
	else if (first.end == second.start)
	{
		if (!first.end_open || !second.start_open)return true;
	}
	return false;
}

vector<Interval> unite(vector<Interval> arr)
{
	if (arr.empty())return{};
	sort(arr.begin(), arr.end(), comp);
	vector<Interval>res{};
	Interval new_entry = arr.front();
	
	for (int i = 1; i < arr.size(); ++i)
	{
		if (is_intersect(new_entry, arr[i]))
		{
			if (arr[i].end > new_entry.end)new_entry.end_open = arr[i].end_open;
			else if (arr[i].end == new_entry.end)new_entry.end_open = (!new_entry.end_open || !arr[i].end_open) ? false : true;

			new_entry.end = max(new_entry.end, arr[i].end);
			if (arr[i].start==new_entry.start)new_entry.start_open = arr[i].start_open;	
		}
		else
		{
			res.emplace_back(new_entry);
			new_entry = arr[i];
		}
	}
	res.emplace_back(new_entry);
	return res;
} // time O(nlogn), space O(1)

void print(const vector<Interval>&arr)
{
	for (const auto& x : arr)
	{
		if (x.start_open)cout << "(";
		else cout << "[";
		
		cout << x.start << ",";
		cout << x.end;
		if (x.end_open)cout << ")";
		else cout << "]";
	}
}

void check(const vector<Interval>&arr)
{
	for (size_t i = 1; i < arr.size(); ++i)
	{
		if (arr[i - 1].end_open && arr[i].start_open)assert((arr[i - 1].end == arr[i].start)|| (arr[i - 1].end < arr[i].start));
		else assert(arr[i - 1].end < arr[i].start);
	}
}

void small_test();

void main()
{
	small_test();
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 100; ++times)
	{
		int max = 1000;
		vector<Interval>arr{};
		int size = uniform_int_distribution<>{ 0,100 }(mt);
		for (int i = 0; i < size; ++i)
		{
			int left = uniform_int_distribution<>{ 0, max-1 }(mt);
			int right = uniform_int_distribution<>{ left+1, max }(mt);
			bool left_open = uniform_int_distribution<>{ 0,1 }(mt);
			bool right_open = uniform_int_distribution<>{ 0,1 }(mt);
			arr.emplace_back(left, right, left_open, right_open);
		}
		arr = unite(arr);
		check(arr);
	}
	system("pause");
}

void small_test()
{
	vector<Interval>arr{ { 0,3,true,true },{ 1,1,false,false },{ 2,4,false,false },{ 3,4,false,true },{ 5,7,false,true },{ 7,8,false,true },{ 8,11,false,true },{ 9,11,true,false },{ 12,16,true,false },{ 12,14,false,false },{ 13,15,true,true },{ 16,17,true,true } };
	auto res = unite(arr);
	check(res);
}
