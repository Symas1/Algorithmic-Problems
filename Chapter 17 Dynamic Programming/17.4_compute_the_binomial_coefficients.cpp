// compute the binomial coefficients
#include <vector>
#include <random>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cmath>
using namespace std;

int coef(int n, int k) {
	vector<int>arr{ 1 };
	for (int i = 1; i <= n; ++i) {
		vector<int>next_arr(i + 1);
		int previous=0;
		for (int j = 0; j < arr.size(); ++j) {
			next_arr[j] = previous + arr[j];
			previous = arr[j];
		}
		next_arr.back()=1;
		arr = next_arr;
	}
	return arr[k];
} // time O(n^2); space O(n)

int coef2_helper(int n, int k, vector<vector<int>>&arr);
int coef2(int n, int k) {
	vector<vector<int>>arr(n+1, vector<int>(k+1,0));
	return coef2_helper(n, k, arr);
} // time O(nk); space O(nk)
int coef2_helper(int n, int k, vector<vector<int>>&arr) {
	if (k == 0 || n == k) {
		return 1;
	}

	if (arr[n][k] == 0) {
		int one_part = coef2_helper(n - 1, k, arr);
		int second_part = coef2_helper(n - 1, k - 1, arr);
		arr[n][k] = one_part + second_part;
	}
	return arr[n][k];
}

int coef3_helper(int n, int k, vector<int>&arr);
int coef3(int n, int k) {
	vector<int>arr(k+1, 0);
	return coef3_helper(n, k, arr);
} // time O(nk); space O(k)
int coef3_helper(int n, int k, vector<int>&arr)
{
	if (k == 0 || n == k) {
		return 1;
	}

	arr[k] = coef3_helper(n - 1, k,arr) + coef3_helper(n - 1, k - 1,arr);
	return arr[k];
}

int coef4(int n, int k) {
	k = min(k, n - k);
	vector<int>arr(k + 1, 0);
	arr[0] = 1; // C(0,0)
	for (int i = 1; i <= n; ++i) {
		for (int j = min(i, k); j >= 1; --j) {
			arr[j] = arr[j] + arr[j - 1];
		}
	}
	return arr.back();
} // time O(nk); space O(min(k,n-k))

void small_test() {
	assert(coef(4, 0) == 1);
	assert(coef(4, 1) == 4);
	assert(coef(4, 2) == 6);
	assert(coef(4, 3) == 4);
	assert(coef(4, 4) == 1);

	assert(coef2(4, 0) == 1);
	assert(coef2(4, 1) == 4);
	assert(coef2(4, 2) == 6);
	assert(coef2(4, 3) == 4);
	assert(coef2(4, 4) == 1);

	assert(coef3(4, 0) == 1);
	assert(coef3(4, 1) == 4);
	assert(coef3(4, 2) == 6);
	assert(coef3(4, 3) == 4);
	assert(coef3(4, 4) == 1);

	assert(coef4(4, 0) == 1);
	assert(coef4(4, 1) == 4);
	assert(coef4(4, 2) == 6);
	assert(coef4(4, 3) == 4);
	assert(coef4(4, 4) == 1);
}

void main() {
	mt19937 mt{ random_device{}() };
	small_test();
	for (int i = 0; i < 10000; ++i) {
		const int min_n = 0, max_n = 10;
		auto n = uniform_int_distribution<>{ min_n,max_n }(mt);
		auto k = uniform_int_distribution<>{ 0,n }(mt);
		auto res1 = coef(n, k);
		auto res2 = coef2(n, k);
		auto res3 = coef3(n, k);
		auto res4 = coef4(n, k);
		assert(res1 == res2 && res2 == res3 && res3==res4);
	}
	system("pause");
}