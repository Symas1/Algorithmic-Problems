// compute buildings with sunset view
#include <stack>
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <random>
#include <functional>
#include <sstream>
using namespace std;

struct Building
{
	double height;
};

bool operator<=(const Building& first, const Building& second)
{
	return first.height <= second.height;
}

bool operator==(const Building& first, const Building& second)
{
	return first.height == second.height;
}


vector<Building> view(const vector<Building>&arr)
{
	vector<Building>res{};
	for (int i = arr.size() - 1; i >= 0; --i)
	{
		while (!res.empty() && res.back() <= arr[i])
		{
			res.pop_back();
		}
		res.emplace_back(arr[i]);
	}
	return res;
} // time O(n); space worst-case O(n), best-case O(1)

vector<Building> view2(const vector<Building>&arr)
{
	vector<Building>res{};
	vector<Building>::const_iterator iter=arr.end();
	do
	{
		iter = max_element(arr.begin(), iter, [](const Building& largest, const Building& second) {return largest.height < second.height; });
		if (iter != arr.end())res.emplace_back(*iter);
	} while (iter != arr.begin() && iter!=arr.end());
	return res;
} // worst-time O(n), best-time O(1); worst-space O(n), best-space O(1)

vector<Building> variant_view(istringstream& sin)
{
	vector<Building>res{};
	double height;
	while (sin >> height)
	{
		if (res.empty() || res[res.size() - 1].height < height)
		{
			res.emplace_back(Building{ height });
		}
	}
	return res;
} // time O(n), worst-space O(n), best-space O(1)

void test_view();
void test_variant();

void main()
{
	//test_view();
	test_variant();
	system("pause");
}

void test_view()
{
	// increasing order
	{
		vector<Building>arr = { { 5 },{ 4 },{ 3 },{ 2 },{ 1 } };
		assert(equal(arr.begin(), arr.end(), view2({ { 1 },{ 2 },{ 3 },{ 4 },{ 5 } }).begin()));
	}
	// descending order
	{
		vector<Building>arr = { { 5 } };
		assert(equal(arr.begin(), arr.end(), view2({ { 5 },{ 4 },{ 3 },{ 2 },{ 1 } }).begin()));
	}
	{
		vector<Building>arr = { { 10 },{ 7 },{ 6 },{ 5 } };
		assert(equal(arr.begin(), arr.end(), view2({ { 5 },{ 2 },{ 6 },{ 7 },{ 3 },{ 10 },{ 9 } }).begin()));
	}
	{
		vector<Building>arr = {};
		assert(equal(arr.begin(), arr.end(), view2({}).begin()));
	}
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 1000; ++i)
	{
		vector<Building>arr(uniform_int_distribution<int>{0, 1000}(mt));
		generate(arr.begin(), arr.end(), [&mt]() {return Building{ uniform_real_distribution<double>{1, 1000}(mt) }; });
		arr = view2(arr);
		assert(is_sorted(arr.begin(), arr.end(), [](const Building& first, const Building& second)
		{return first.height > second.height; }));
	}
}

void test_variant()
{
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 10; ++i)
	{
		stringstream ss{};
		int size = uniform_int_distribution<int>{ 0,1000 }(mt);
		for (int j = 0; j < size; ++j)
		{
			ss << uniform_real_distribution<double>{1, 1000}(mt) << " ";
		}
		istringstream sin(ss.str());
		auto res = variant_view(sin);
		assert(is_sorted(res.begin(), res.end(), [](const Building& first, const Building& second)
		{return first.height < second.height; }));
	}
}