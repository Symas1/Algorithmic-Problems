// multiplication
#include <limits>
#include <iostream>
#include <random>
#include <assert.h>
using namespace std;
unsigned add(unsigned a, unsigned b)
{
	unsigned res = 0, k = 1, carryin = 0, temp_a = a, temp_b = b;
	while (temp_a || temp_b)
	{
		unsigned ak = (a&k), bk = (b&k);
		unsigned carryout = (ak&bk) | (ak&carryin) | (bk&carryin);
		res |= (ak^bk^carryin);
		carryin = carryout << 1;
		temp_a >>= 1;
		temp_b >>= 1;
		k <<= 1;
	}
	return res | carryin;
} // O(n)

unsigned multiply(unsigned x, unsigned y)
{
	unsigned sum = 0;
	while (x)
	{
		if (x & 1)
		{
			sum = add(sum, y);
		}
		x >>= 1;
		y <<= 1;
	}
	return sum;
} // O(n^2)

void main()
{
	mt19937 mt((random_device())());
	uniform_int_distribution<unsigned> dist_add(numeric_limits<unsigned>::min(), numeric_limits<unsigned>::max() / 2);
	uniform_int_distribution<unsigned> dist_multiply(numeric_limits<unsigned>::min(),sqrt(numeric_limits<unsigned>::max()));
	for (int i = 0; i < 10000; ++i)
	{
		auto first = dist_add(mt);
		auto second = dist_add(mt);
		assert(add(first, second) == (first + second));
		auto third = dist_multiply(mt);
		auto fourth = dist_multiply(mt);
		assert(multiply(third, fourth) == (third*fourth));
	}

	system("pause");
}