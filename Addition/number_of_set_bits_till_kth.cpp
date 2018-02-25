// A simple program to count set bits in all numbers from 1 to n.
#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <algorithm>
#include <assert.h>
using namespace std;

unsigned long long count(int k)
{
	if (k == 0)return 0;
	int digits = static_cast<int>(floor(log(k) / log(2)));
	int num = pow(2,digits);
	return count(num-1)+count(k-num)+(k-num+1);
} // https://stackoverflow.com/a/9813509 time O(logn), space O(logn)

unsigned long long count_fast(int k)
{
	unsigned long long ans = 0;
	for (int i = 0; i < 32; ++i)
	{
		if (k >> i == 0)break;
		int repetitions = k + 1 >> i + 1;
		ans += repetitions << i;
		int rest = ((k + 1) % (1 << i + 1)) - (1 << i);
		if (rest > 0)ans += rest;
	}
	return ans;
} // http://www.geeksforgeeks.org/count-total-set-bits-in-all-numbers-from-1-to-n/ time O(1), space O(1)

void main()
{
	for (int i = 0; i < 2000000; ++i)
	{
		//assert(count(i) == count_fast(i));
		cout<<count_fast(i)<<endl;
	}
	system("pause");
}

