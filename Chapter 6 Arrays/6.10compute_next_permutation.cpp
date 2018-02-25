// next permutation
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <assert.h>
#include <cmath>
#include <string>
#include <iterator>
#include <numeric>
#include <functional>
using namespace std;

vector<int> next_permutation_my(vector<int> perm)
{
	auto small = is_sorted_until(perm.rbegin(), perm.rend());
	if (small == perm.rend())return{};

	auto bigger = upper_bound(perm.rbegin(), small, *small);

	iter_swap(bigger, small);

	reverse(perm.rbegin(), small);

	return perm;
} // time O(n), memory O(1)

int perm_rank(const vector<int>&perm)
{
	int rank = 1;
	for (int i = 0; i < perm.size(); ++i)
	{
		int less = count_if(perm.begin() + i + 1, perm.end(), [&num = perm[i]](int k){return k < num; });
		rank += less*(tgamma(perm.size() - i));
	}
	return rank;
}

vector<int> kth_perm(vector<int>perm, int k)
{
	--k;
	vector<int>factoradic{};
	for (int i = 1; k; ++i)
	{
		factoradic.emplace_back(k%i);
		k /= i;
	}

	vector<int>res{};
	if (factoradic.size() != perm.size())
	{
		res.insert(res.end(), perm.begin(), perm.begin() + (perm.size() - factoradic.size()));
		perm.erase(perm.begin(), perm.begin() + (perm.size() - factoradic.size()));
	}


	for (int i = factoradic.size() - 1; i >= 0; --i)
	{
		res.emplace_back(perm[factoradic[i]]);
		perm.erase(perm.begin() + factoradic[i]);
	}
	return res;
}

vector<int> prev_permutation_my(vector<int> perm)
{
	auto big = is_sorted_until(perm.rbegin(), perm.rend(), greater<int>());

	if (big == perm.rend())return{};

	auto lower = big - 1;

	iter_swap(big, lower);

	reverse(perm.rbegin(), big);

	return perm;
}

void test_next_perm();
void test_perm_rank();
void test_prev_perm();
void test_kth_perm();

void main()
{
	test_next_perm();
	test_perm_rank();
	test_kth_perm();
	test_prev_perm();

	system("pause");
}

void test_next_perm()
{
	const int size = 10;
	mt19937 mt{ random_device{}() };
	uniform_int_distribution<int> dist{ 0,size - 1 };
	for (int times = 0; times < 1000; ++times)
	{
		vector<int> arr{};

		int i = 0;
		generate_n(back_inserter(arr), size, [&i]() {return ++i; });
		shuffle(arr.begin(), arr.end(), mt19937{ random_device{}() });


		auto ans{ next_permutation_my(arr) };
		bool has_next = next_permutation(arr.begin(), arr.end());
		assert((ans.size() == 0 && !has_next) || equal(ans.begin(), ans.end(), arr.begin(), arr.end()));
	}
}

void test_perm_rank()
{
	assert(perm_rank({ 4,3,2,1 }) == 24);
	assert(perm_rank({ 2,1,3 }) == 3);
}

void test_kth_perm()
{
	vector<int>arr;
	generate_n(back_inserter(arr), 100, []() {static int i = 1; return i++; });
	auto vec = kth_perm(arr, 6);
}

void test_prev_perm()
{
	const int size = 10;
	mt19937 mt{ random_device{}() };
	uniform_int_distribution<int> dist{ 0,size - 1 };
	for (int times = 0; times < 100000; ++times)
	{
		vector<int> arr{};

		iota(arr.begin(), arr.end(), 0);
		shuffle(arr.begin(), arr.end(), mt19937{ random_device{}() });


		auto ans{ prev_permutation_my(arr) };
		bool has_prev = prev_permutation(arr.begin(), arr.end());
		assert((ans.size() == 0 && !has_prev) || equal(ans.begin(), ans.end(), arr.begin(), arr.end()));
	}
}