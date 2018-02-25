//count set bits slowly O(n)

#include <bitset>
#include <random>
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

unsigned count_set_bits(unsigned x)
{
	unsigned counter = 0;
	while (x)
	{
		counter += x & 1;
		x >>= 1;
	}
	return counter;
} // O(n)

unsigned counter_set_fast(unsigned x)
{
	unsigned counter = 0;
	while (x)
	{
		++counter;
		x &= (x - 1);
	}
	return counter;
} // O(s)

void main()
{
	mt19937 mt( (random_device())() );
	uniform_int_distribution<unsigned> dist{};

	for (int i = 0; i < 30000; ++i)
	{
		auto random = dist(mt);
		auto set_bits = count_set_bits(random);
		auto set_bits_f = counter_set_fast(random);
		bitset<32>check{ random };
		assert(set_bits == check.count());
		assert(set_bits_f == check.count());
	}
	system("pause");
}