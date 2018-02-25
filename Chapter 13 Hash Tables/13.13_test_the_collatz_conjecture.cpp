// test the Collatz conjecture
#include <unordered_set>
#include <iostream>
#include <assert.h>
#include <numeric>
#include <stdexcept>
#include <string>
#include <random>
using namespace std;

bool collatz(const int n)
{
	for (int i = 3; i <= n; i+=2)
	{
		unordered_set<long>seq{};
		long current = i;
		while (current >= i)
		{
			if (!seq.emplace(current).second)return false;
			if (current % 2)
			{
				long next = current * 3 + 1;
				if (next <= current)throw overflow_error("Collatz sequence overflow for: " + to_string(i));
				current = next;
			}
			else current /= 2;
		}
	}
	return true;
} // time O(n); space O(n)

bool brute(const int n)
{
	for (int i = 3; i <= n; ++i)
	{
		long curr = i;
		while (curr != 1 && curr>=i)
		{
			if (curr % 2)curr = curr * 3 + 1;
			else curr /= 2;
		}
	}
	return true;
}

void main()
{
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 100; ++times)
	{
		const int n = uniform_int_distribution<int>{ 1,1000 }(mt);
		assert(brute(n) == collatz(n));
	}
	system("pause");
}