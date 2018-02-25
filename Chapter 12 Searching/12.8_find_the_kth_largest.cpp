// find the kth largest element
#include<vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <assert.h>
#include <random>
#include <iterator>
#include <unordered_set>
using namespace std;

int my_partition(vector<int>&arr, int begin, int end, int pivot_index);
int find_kth_helper(vector<int>&arr, int k);
int find_kth(const vector<int>&arr, int k)
{
	assert(k != 0 && k <= arr.size());
	auto arr_copy = arr;
	return find_kth_helper(arr_copy, k);
} // time worst-case O(n^2), average O(n); space O(n)
int find_kth_helper(vector<int>&arr, int k)
{
	mt19937 mt{ random_device{}() };
	int begin = 0, end = arr.size() - 1;
	while (begin <= end)
	{
		int pivot_index = uniform_int_distribution<int>{ begin,end }(mt);
		pivot_index = my_partition(arr, begin, end, pivot_index);
		int diff = arr.size() - pivot_index;
		if (diff == k)return arr[pivot_index];
		else if (diff > k)begin = pivot_index + 1;
		else if (diff < k)end = pivot_index - 1;
	}
	assert(false);
}
int my_partition(vector<int>&arr, int begin, int end, int pivot_index)
{
	int pivot = arr[pivot_index];
	int less = begin;
	swap(arr[pivot_index], arr[end]);
	while (begin < end)
	{
		if (arr[begin] < pivot)swap(arr[less++], arr[begin++]);
		else if (arr[begin] == pivot)++begin;
		else if (arr[begin] > pivot)++begin;
	}
	swap(arr[less], arr[end]);
	return less;
}
int kth_brute(const vector<int>&arr, int k)
{
	vector<int>arr_copy = arr;
	sort(arr_copy.begin(), arr_copy.end());
	return arr_copy[arr_copy.size() - k];
} // time O(nlogn); space O(n)

double median(const vector<int>&arr)
{
	vector<int>arr_copy = arr;
	mt19937 mt{ random_device{}() };
	int begin = 0, end = arr_copy.size() - 1;
	bool found = false;
	int first, second;
	while (begin <= end)
	{
		int pivot_index = uniform_int_distribution<int>{ begin,end }(mt);
		pivot_index = my_partition(arr_copy, begin, end, pivot_index);
		int right_diff = arr_copy.size() - 1 - pivot_index;
		int left_diff = pivot_index;
		if (arr_copy.size() % 2)
		{
			if (right_diff == left_diff)return arr_copy[pivot_index];
			else if (right_diff > left_diff)begin = pivot_index + 1;
			else end = pivot_index - 1;
		}
		else if (arr_copy.size() % 2 == 0)
		{
			if (right_diff == left_diff + 1 && !found)
			{
				found = true;
				first = arr_copy[pivot_index];
				begin = pivot_index + 1;
			}
			else if (right_diff + 1 == left_diff && !found)
			{
				found = true;
				first = arr_copy[pivot_index];
				end = pivot_index - 1;
			}
			else if (right_diff == left_diff + 1 || right_diff + 1 == left_diff)
			{
				return 0.5*(first + arr_copy[pivot_index]);
			}
			else if (right_diff > left_diff)begin = pivot_index + 1;
			else if (right_diff < left_diff)end = pivot_index - 1;
		}
	}
	assert(false);
} // time worst-case O(n^2), average O(n); space O(n)
double brute_median(const vector<int>&arr)
{
	vector<int>arr_copy = arr;
	sort(arr_copy.begin(), arr_copy.end());
	if (arr_copy.size() % 2)return arr_copy[arr_copy.size() / 2];
	else return 0.5*(arr_copy[arr_copy.size() / 2] + arr_copy[arr_copy.size() / 2 - 1]);
} // time O(nlogn); space O(n)

int variant3(const vector<int>&arr,int k)
{
	assert(k != 0);
	vector<int>arr_copy{};
	unordered_set<int>set{};
	for (int i = 0; i < arr.size(); ++i)
	{
		if (!set.count(arr[i]))
		{
			arr_copy.emplace_back(arr[i]);
			set.emplace(arr[i]);
		}
	}
	assert(k <= arr_copy.size());
	return find_kth(arr_copy,k);
} // time worst-case O(n^2), average O(n); space O(n)

void test_main();
void test_median();
void test_variant3();

int main(int argc, char* argv[])
{
	//test_main();
	//test_median();
	test_variant3();
	system("pause");
	return 0;
}

void test_main()
{
	vector<int>arr{ 3,2,1,4,5 };
	for (int i = 1; i <= 5; ++i)
	{
		assert(find_kth(arr, i) == 6 - i);
		assert(kth_brute(arr, i) == 6 - i);
	}

	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 100; ++times)
	{
		vector<int>arr(uniform_int_distribution<int>{1, 100}(mt));
		generate(arr.begin(), arr.end(), [&mt]()
		{return uniform_int_distribution<int>{numeric_limits<int>::min(), numeric_limits<int>::max() }(mt); });
		for (int j = 1; j <= arr.size(); ++j)
		{
			assert(find_kth(arr, j) == kth_brute(arr, j));
		}
	}
}

void test_median()
{
	{
		vector<int>arr{ 3,2,1,5,4 };
		assert(median(arr) == 3);
		assert(brute_median(arr) == 3);
		arr = { 1,2,3 };
		assert(median(arr) == 2);
		assert(brute_median(arr) == 2);
		arr = { 1 };
		assert(median(arr) == 1);
		assert(brute_median(arr) == 1);
	}
	{
		vector<int>arr{ 3,2,1,4 };
		assert(median(arr) == 2.5);
		assert(brute_median(arr) == 2.5);
		arr = { 1,2 };
		assert(median(arr) == 1.5);
		assert(brute_median(arr) == 1.5);
	}
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 100; ++times)
	{
		vector<int>arr(uniform_int_distribution<int>{1, 100}(mt));
		generate(arr.begin(), arr.end(), [&mt]()
		{return uniform_int_distribution<int>{numeric_limits<int>::min(), numeric_limits<int>::max() }(mt); });
		assert(median(arr) == brute_median(arr));
	}
}

void test_variant3()
{
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 100; ++times)
	{
		const int elements = 10;
		vector<int>arr{};
		for (int i = 0; i < elements; ++i)
		{
			int quantity = uniform_int_distribution<int>{ 1,10 }(mt);
			vector<int>add(quantity, i);
			arr.insert(arr.end(),add.begin(),add.end());
		}
		shuffle(arr.begin(), arr.end(), mt);
		for (int i = 1; i < elements; ++i)
		{
			assert(variant3(arr, i) == elements - i);
		}
	}
}