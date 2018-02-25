//delete duplicates in sorted array
#include <vector>
#include <iostream>
#include <assert.h>
#include <random>
#include <assert.h>
#include <algorithm>
using namespace std;

int dup_del(vector<int>&a)
{
	int valid = 1;
	for (int i = 1; i < a.size(); ++i)
	{
		if (a[i] != a[valid - 1])
		{
			a[valid++] = a[i];
		}
	}
	return valid;
} // time O(n), space O(1)

//int dup_del(vector<int>& a)
//{
//	int current=a[0];
//	int valid = 0;
//
//	bool end = false;
//	for (int i = 1; i < a.size()&&!end; ++i)
//	{
//		for (int j = i; j < a.size(); ++j)
//		{
//			if (a[j] == current)
//			{
//				a[j] = 0;
//				if (j == a.size() - 1)end = true;
//				continue;
//			}
//			else
//			{
//				current = a[j];
//				i = j;
//				swap(a[j], a[++valid]);
//				break;
//			}
//		}
//	}
//
//	return valid+1;
//} // time O(n), space O(1)

int variant1(vector<int>&a, int num)
{
	int valid = 0;
	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i] != num)
		{
			swap(a[valid++], a[i]);
		}
	}
	return valid;
} // time O(n), space O(1)

void variant2(vector<int>&a, unsigned m)
{
	int occurences = min(static_cast<unsigned>(2), m);
	int valid = 1;
	for (int i = 1, counter = 0; i < a.size(); ++i)
	{
		if (a[i] == a[valid - 1])
		{
			++counter;
			if (counter < occurences)swap(a[i], a[valid++]);
		}
		else
		{
			counter = 0;
			swap(a[i], a[valid++]);
		}
	}
} // time O(n), space O(1)

void test_dup_del();
void test_variant1();
void test_variant2();

void main()
{
	test_dup_del();

	test_variant1();

	test_variant2();
	system("pause");
}

void test_dup_del()
{
	const int size = 100;
	mt19937 mt{ random_device{} () };
	uniform_int_distribution<int> dist{ 1,10 };
	for (int i = 0; i < 1000; ++i)
	{
		vector<int>real_arr{};
		vector<int>copy_arr{};
		for (int j = 0; j < size; ++j)
		{
			real_arr.push_back(dist(mt));
		}
		sort(real_arr.begin(), real_arr.end());
		copy_arr = real_arr;

		int valid = dup_del(real_arr);
		real_arr.erase(real_arr.begin() + valid, real_arr.end());

		copy_arr.erase(unique(copy_arr.begin(), copy_arr.end()), copy_arr.end());

		assert(real_arr == copy_arr);
	}
}

void test_variant1()
{
	vector<int>arr{ 1,1,1,1,1,1,1,1,1 };
	assert(variant1(arr, 1) == 0);

	arr = { 1,2,3,4,1,5,6,1,1,1,1,10 };
	assert(variant1(arr, 1) == 6);
}

void test_variant2()
{
	vector<int>arr{ 2,3,3,3,4,4,4 };
	variant2(arr, 1);
	assert(equal(arr.begin(), arr.begin() + 3, vector<int>{ 2, 3, 4 }.begin()));

	arr = { 2,3,3,3,4,4,4 };
	variant2(arr, 2);
	assert(equal(arr.begin(), arr.begin() + 5, vector<int>{ 2, 3, 3, 4, 4 }.begin()));
}