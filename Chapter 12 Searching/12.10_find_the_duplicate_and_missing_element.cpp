// find the duplicate and missing elements
#include <vector>
#include <assert.h>
#include <iostream>
#include <random>
#include <numeric>
#include <algorithm>
#include <iterator>
using namespace std;

struct Result
{
	int missing, duplicate;
};

Result f(const vector<int>&arr)
{
	int miss_xor_dup = 0;
	for (int i = 0; i < arr.size(); ++i)
	{
		miss_xor_dup ^= i^arr[i];
	}

	int differ_bit = miss_xor_dup & (~(miss_xor_dup - 1));
	int miss_or_dup = 0;
	for (int i = 0; i < arr.size(); ++i)
	{
		if (i&differ_bit)
		{
			miss_or_dup ^= i;
		}
		if (arr[i] & differ_bit)
		{
			miss_or_dup ^= arr[i];
		}
	}

	for (const auto x : arr)
	{
		if (x == miss_or_dup) // duplicate
			return{ miss_or_dup^miss_xor_dup,miss_or_dup };
	}
	return{ miss_or_dup ,miss_or_dup^miss_xor_dup };
} // time O(n), space O(1)

int main(int argc, char* argv[])
{
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times)
	{
		vector<int>arr(uniform_int_distribution<int>{2, 100}(mt));
		iota(arr.begin(), arr.end(),0);
		int miss = uniform_int_distribution<int>{ 0,(int)arr.size() - 1 }(mt);
		int duplicate = -1;
		while(duplicate == -1 || duplicate == miss)duplicate = uniform_int_distribution<int>{ 0,(int)arr.size() - 1 }(mt);
		arr[miss] = duplicate;
		shuffle(arr.begin(), arr.end(), mt);
		auto res = f(arr);
		assert(res.duplicate == duplicate && res.missing == miss);
	}
	system("pause");
	return 0;
}