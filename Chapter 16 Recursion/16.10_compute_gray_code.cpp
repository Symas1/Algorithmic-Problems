// compute a gray code
#include <vector>
#include <iostream>
#include <unordered_set>
#include <bitset>
#include <string>
#include <assert.h>
using namespace std;

bool gray_code_helper(int num_bits, vector<int>&res, unordered_set<int>&used);
bool differ_by_one_bit(int a, int b);
vector<int> gray_code(int num_bits)
{
	vector<int>res{ { 0 } };
	unordered_set<int>used{ {0} };
	gray_code_helper(num_bits, res, used);
	return res;
}
bool gray_code_helper(int num_bits, vector<int>&res, unordered_set<int>&used)
{
	if (res.size() == (1 << num_bits))
	{
		return differ_by_one_bit(res.front(), res.back());
	}

	for (int i = 0; i < num_bits; ++i)
	{
		int prev_code = res.back();
		int candidate_next = prev_code ^ (1 << i);
		if (!used.count(candidate_next))
		{
			used.emplace(candidate_next);
			res.emplace_back(candidate_next);
			if (gray_code_helper(num_bits, res, used))
			{
				return true;
			}
			used.erase(candidate_next);
			res.pop_back();
		}
	}
	return false;
} // time O(num_bits * 2^n); space O(2^n)
bool differ_by_one_bit(int a, int b)
{
	int diff = a^b;
	return diff && !(diff&(diff - 1));
}

void check(const vector<int>&arr)
{
	for (size_t i = 0; i < arr.size(); ++i)
	{
		assert(differ_by_one_bit(arr[i], arr[(i + 1) % arr.size()]));
	}
}

vector<int> gray_code2(int num_bits)
{
	if (num_bits == 0)
	{
		return{ {0} };
	}

	auto one_half = gray_code2(num_bits - 1);
	int lead_one = 1 << (num_bits - 1);
	for (int i = one_half.size() - 1; i >= 0; --i)
	{
		one_half.emplace_back(lead_one | one_half[i]);
	}
	return one_half;
} // time O(2^n); space O(2^n) function call stack

void main()
{
	for (int i = 1; i < 12; ++i)
	{
		auto res = gray_code(i);
		auto res2 = gray_code2(i);
		check(res);
		check(res2);
	}
	system("pause");
}