//returns 1 if number of set bits is odd, otherwise 0

#include <array>
#include <assert.h>
#include <random>
#include <numeric>
#include <bitset>
#include <iostream>
using namespace std;

bool slow_parity(long x)
{
	short result = 0;
	while (x)
	{
		result ^= (x & 1);
		x >>= 1;
	}
	return result;
} // O(n)

bool parity(long x)
{
	short result = 0;
	while (x)
	{
		result ^= 1;
		x &= (x - 1);
	}
	return result;
} // O(s) s - number of set bits


array<short, 1 << 16> build_table()
{
	array<short, 1 << 16>result;
	for (long i = 0; i < (1 << 16); ++i)
	{
		result[i] = parity(i);
	}
	return result;
}

static array<short, 1 << 16> parity_table = build_table();

bool parity_64(long long x) // parity for 64 bit large number
{
	const int mask_size = 16;
	const int bit_mask = 0xFFFF;
	return parity_table[x >> (3 * mask_size)] ^
		parity_table[(x >> (2 * mask_size)) & bit_mask] ^
		parity_table[(x >> mask_size) & bit_mask] ^
		parity_table[x & bit_mask];
} // O(n/L) n - word size, l - cache word size (64/16)


bool parity_64_2(long long x)
{
	x ^= (x >> 32);
	x ^= (x >> 16);// or return parity_table[x&0xFFFF];
	x ^= (x >> 8);
	x ^= (x >> 4);
	x ^= (x >> 2);
	x ^= (x >> 1);
	return x & 1;
} // O(logn)

void main()
{
	mt19937 mt((random_device())());
	uniform_int_distribution<long> dist(0, numeric_limits<long>::max());
	for (int i = 0; i < 1000; ++i)
	{
		auto random = dist(mt);
		bitset<64>check( random);
		bool result = check.count() % 2;
		auto slow = slow_parity(random);
		auto faster = parity(random);
		auto parity64 = parity_64(random);
		auto parity64_2 = parity_64_2(random);
		assert(slow == result);
		assert(faster == result);
		assert(parity64 == result);
		assert(parity64_2 == result);
	}
}