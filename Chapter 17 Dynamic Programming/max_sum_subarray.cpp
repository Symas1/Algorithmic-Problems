// max sum subarray
#include <vector>
#include <assert.h>
#include <numeric>
#include <algorithm>
#include <random>
#include <iterator>
#include <iostream>
#include <numeric>
#include <functional>
using namespace std;

int max_sum2(const vector<int>&arr)
{
	int current_sum = 0, max_sum = numeric_limits<int>::min();
	for (int i = 0; i < arr.size(); ++i)
	{
		current_sum += arr[i];
		max_sum = max(current_sum, max_sum);
		current_sum = max(current_sum, 0);
	}
	return max_sum;
} // time O(n); space O(1)

int max_sum_brute(const vector<int>&arr)
{
	int max_sum = numeric_limits<int>::min();
	for (int i = 0; i < arr.size(); ++i)
	{
		int sum = 0;
		for (int j = i; j < arr.size(); ++j)
		{
			sum += arr[j];
			max_sum = max(max_sum, sum);
		}
	}
	return max_sum;
} // time O(n^2); space O(1)

int max_sum_divide_helper(const vector<int>&arr, int start, int end);
int max_sum_divide(const vector<int>&arr) {
	return max_sum_divide_helper(arr, 0, arr.size() - 1);
}
int max_sum_divide_helper(const vector<int>&arr, int start, int end)
{
	if (start == end) {
		return{ arr[start] };
	}

	int middle = start + (end-start)/2;

	auto left_max = max_sum_divide_helper(arr, start, middle);
	auto right_max = max_sum_divide_helper(arr, middle + 1, end);

	int left_range = numeric_limits<int>::min();
	for (int i = middle, sum = 0; i >= start; --i) {
		sum += arr[i];
		left_range = max(left_range, sum);
	}
	int right_range = numeric_limits<int>::min();
	for (int i = middle+1, sum = 0; i <= end; ++i) {
		sum += arr[i];
		right_range = max(right_range, sum);
	}

	return max(max(left_max, right_max), left_range+right_range);
} // time O(nlogn); space O(logn)

vector<int> rand_vector(size_t size)
{
	mt19937 mt{ random_device{}() };
	vector<int>arr(size);
	generate(arr.begin(), arr.end(), [&mt]() {
		return uniform_int_distribution<>{-100, 100}(mt);
	});
	return arr;
}

void small_test()
{
	vector<int> arr{ -2,-3,4,-1,-2,1,5,-3 };
	auto res1 = max_sum2(arr);
	auto res2 = max_sum_brute(arr);
	auto res3 = max_sum_divide(arr);
	cout << res3 << endl;
	assert(res1 == 7);
	assert(res2 == 7);
	assert(res3 == 7);
}

void main()
{
	small_test();
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 10000; ++i)
	{
		const int max_size = 20;
		auto arr = rand_vector(uniform_int_distribution<>{1, max_size}(mt));
		auto res1 = max_sum2(arr);
		auto res2 = max_sum_brute(arr);
		auto res3 = max_sum_divide(arr);
		assert(res1 == res2);
		//cout << res1 << '\t' << res2 << '\t' << res3 << endl;
		assert(res1 == res3);
	}
	system("pause");
}