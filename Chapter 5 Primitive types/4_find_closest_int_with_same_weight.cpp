#include <algorithm>
#include <iostream>
#include <numeric>
#include <assert.h>
#include <stdexcept>
#include <iostream>
#include <random>
using namespace std;
short weight(int x)
{
	short result = 0;
	while (x)
	{
		++result;
		x &= (x - 1);
	}
	return result;
}

int closest_brute_force(int x) // brute-force O(2*2^(n-1)) ~ O(2^(n-1))
{
	int y1 = x;
	int y2 = x;
	while (true)
	{
		y1 -= 1;
		y2 += 1;
		if (weight(y1) == weight(x) && weight(y2) == weight(x))
		{
			return abs(y1 - x) <= abs(y2 - x) ? y1 : y2;
		}
		else if (weight(y1) == weight(x))return y1;
		else if (weight(y2) == weight(x))return y2;
	}
}

int closest_almost_fast(int x)
{
	for (int i = 0; i < (sizeof(x) * 8 - 2); ++i) // dont access last bit (as not assumed to be non negative)
	{
		if (((x >> i) & 1) !=((x >> i + 1) & 1) ) // if LSB and NEXT different
		{
			x ^= ((1 << i + 1) | (1 << i)); // swap LSB and NEXT
			return x;
		}
	}
	throw invalid_argument("Argument consists of all 0s all 1s");
} // O(n)

int closest(int x)
{
	int lowest_not_set = (~x)&(x + 1);
	int lowest_set = x&(~(x - 1));
	if (lowest_not_set > lowest_set)
	{
		x ^= lowest_not_set | (lowest_not_set>>1);
	}
	else
		x ^= lowest_set | (lowest_set >> 1);
	return x;
} // O(1)

void main()
{
	assert(closest(6) == 5);
	assert(closest(7) == 11);
	assert(closest(2) == 1);
	assert(closest(32) == 16);

	try {
		closest_almost_fast(numeric_limits<int>::max());
		assert(false);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	mt19937 mt((random_device())());
	uniform_int_distribution<int>dist(1, numeric_limits<int>::max() - 1);
	for (int i = 0; i < 1000; ++i)
	{
		auto rand = dist(mt);
		auto res = closest(rand);
		assert(weight(res) == weight(rand));
	}

	system("pause");
}