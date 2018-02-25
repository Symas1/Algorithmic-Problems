// compute the integer square root
#include <assert.h>
#include <iostream>
#include <random>
#include <numeric>
using namespace std;

int sq(const int n)
{
	int low = 0, up = n;
	while (low <= up)
	{
		int mid = low + (up - low) / 2;
		unsigned long long s = static_cast<unsigned long long>(mid)*mid;
		if (s == n)return mid;
		else if (s < n)low = mid + 1;
		else if (s > n)up = mid - 1;
	}
	return low - 1;
} // time O(logn); space O(1)

int main(int argc, char*argv[])
{
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times)
	{
		const int n = uniform_int_distribution<int>{ 0, numeric_limits<int>::max() }(mt);
		assert(static_cast<int>(sqrt(n)) == sq(n));
	}
	system("pause");
	return 0;
}