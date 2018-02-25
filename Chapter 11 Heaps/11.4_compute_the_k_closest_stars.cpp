// compute the k closest start
#include <vector>
#include <iostream>
#include <assert.h>
#include <queue>
#include <functional>
using namespace std;

struct Coords {
	short x;
	short y;
	short z;
};

bool operator==(const Coords&a, const Coords&b)
{
	return a.x == b.x && a.y == b.y&&a.z == b.z;
}

vector<Coords> closest(const vector<Coords>&stars, int k)
{
	auto comp = [](const Coords&a, const Coords&b)
	{return pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2) < pow(b.x, 2) + pow(b.y, 2) + pow(b.z, 2); };
	priority_queue<Coords, vector<Coords>, decltype(comp)>closest_stars{ comp };

	int index = 0;
	for (; index < k && index < stars.size(); ++index)
	{
		closest_stars.emplace(stars[index]);
	}

	for (; index < stars.size(); ++index)
	{
		if (comp(stars[index], closest_stars.top()))
		{
			closest_stars.pop();
			closest_stars.emplace(stars[index]);
		}
	}

	vector<Coords>res{};
	while (!closest_stars.empty())
	{
		res.emplace_back(closest_stars.top());
		closest_stars.pop();
	}
	return res;
} // time O(nlogk) n - stars, k - closest stars; space O(k) k - closest stars

vector<int> variant1(const vector<int>&arr, int k)
{
	if (k >= arr.size())return{};
	priority_queue<int, vector<int>, greater<int>> q{};

	for (int i = 0; i < k; ++i)
	{
		q.emplace(arr[i]);
	}

	vector<int>res{};
	res.emplace_back(q.top());
	for (int i = k; i < arr.size(); ++i)
	{
		if (q.top() < arr[i])
		{
			q.pop();
			q.emplace(arr[i]);
		}
		res.emplace_back(q.top());
	}
	return res;
}

void test_main();
void test_variant1();

void main()
{
	//test_main();
	test_variant1();
	system("pause");
}

void test_main()
{
	vector<Coords>stars{ { 2,2,0 },{ 4,4,0 },{ 6,6,0 } };
	auto ans = closest(stars, 2);
	assert((ans[0] == Coords{ 4, 4, 0 }) && (ans[1] == Coords{ 2, 2, 0 }) && ans.size() == 2);
}

void test_variant1()
{
	{
		auto check = variant1({ 0,3,2,1,4,6 }, 2);
		assert(equal(check.begin(), check.end(), vector<int>{0, 2, 2, 3, 4}.begin()));
	}
	{
		auto check = variant1({ 0,3,2,1,4,6 }, 3);
		assert(equal(check.begin(), check.end(), vector<int>{0,1,2,3}.begin()));
	}
	{
		auto check = variant1({ 0,3,2,1,4,6 }, 1);
		assert(equal(check.begin(), check.end(), vector<int>{ 0, 3, 3, 3, 4, 6 }.begin()));
	}
	{
		auto check = variant1({ 0,3,2,1,4,6 }, 4);
		assert(equal(check.begin(), check.end(), vector<int>{ 0,1,2 }.begin()));
	}
	{
		auto check = variant1({ 0,3,2,1,4,6 }, 5);
		assert(equal(check.begin(), check.end(), vector<int>{ 0, 1 }.begin()));
	}
	{
		auto check = variant1({ 0,3,2,1,4,6 }, 6);
		assert(equal(check.begin(), check.end(), vector<int>{ 0}.begin()));
	}
	{
		auto check = variant1({ 0,3,2,1,4,6 }, 7);
		assert(equal(check.begin(), check.end(), vector<int>{}.begin()));
	}
}