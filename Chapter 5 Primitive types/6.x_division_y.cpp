// divide x by y
#include <iostream>
#include <numeric>
#include <assert.h>
#include <random>
using namespace std;

unsigned divide(unsigned x, unsigned y)
{
	unsigned result = 0;
	unsigned power = numeric_limits<unsigned>::digits;
	unsigned long long y_power = static_cast<unsigned long long>(y) << power;
	while (x >= y)
	{
		while (y_power > x)
		{
			y_power >>= 1;
			--power;
		}
		result += 1L << power;
		x -= y_power;
	}
	return result;
} // O(n)

void main()
{
	divide(4, 2);
	mt19937 mt((random_device())());
	uniform_int_distribution<unsigned>dist(numeric_limits<unsigned>::min(), numeric_limits<unsigned>::max());
	for (int i = 0; i < 1000; ++i)
	{
		auto first = dist(mt);
		auto second = dist(mt);
		if (second == 0)continue;
		assert(divide(first, second) == (first / second));
	}
	system("pause");
}

