#include <algorithm>
#include <assert.h>
#include <random>
using namespace std;

int even(int min, int max)
{
	min = min % 2 == 0 ? min : min + 1;
	max = max % 2 == 0 ? max : max - 1;
	return ((max - min) / 2) + 1;
	//return floor(max / 2) - floor((min-1) / 2);
}

int even1(int min, int max)
{
	return (max - min + 2 - (abs(min) % 2) - (abs(max) % 2)) / 2;
}

int even2(int min, int max)
{
	return (max - min + 2 - (abs(min) % 2)) / 2;
}

int even_test(int min, int max)
{
	int res = 0;
	for (int i = min; i <= max; ++i)
	{
		if (i % 2 == 0) ++res;
	}
	return res;
}



int odd(int min, int max)
{
	min = min % 2 ? min : min + 1;
	max = max % 2 ? max : max - 1;
	return ((max - min) / 2) + 1;
}

int odd_test(int min, int max)
{
	int res = 0;
	for (int i = min; i <= max; ++i)
	{
		if (i % 2)++res;
	}
	return res;
}

void main()
{
	mt19937 mt{ random_device{}() };
	uniform_int_distribution<int>min_dist{ -5000,5000 };
	uniform_int_distribution<int>max_dist{ 5001,10000 };
	for (int i = 0; i < 10000; ++i)
	{
		auto min = min_dist(mt);
		auto max = max_dist(mt);

		auto even_test = ::even_test(min, max);
		assert(even(min, max) == even_test);
		assert(even2(min, max) == even_test);
		assert(even1(min, max) == even_test);

		auto odd_test = ::odd_test(min, max);
		assert(odd(min, max) == odd_test);
	}
}