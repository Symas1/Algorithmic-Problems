// reverse bits

#include <array>
#include <random>
#include <limits>
#include <iostream>
#include <assert.h>
using namespace std;

long long swap_bits(long long x, int i, int j)
{
	if (((x >> i) & 1) != ((x >> j) & 1))
	{
		long long bit_mask = (1LL << i) | (1LL << j);
		x ^= bit_mask;
	}
	return x;
}

long long brute_force_reverse(long long x, int n) // good for one such operation O(n)
{
	for (int j = n, i = 0; j > i; ++i, --j)
	{
		x = swap_bits(x, j, i);
	}
	return x;
}

array<long, 1 << 16>reversed_array;

array<long, 1 << 16> build_array()
{
	array<long, 1 << 16> result;
	for (int i = 0; i < (1 << 16); ++i)
	{
		result[i] = brute_force_reverse(i, 63);
	}
	return result;
}

long long reverse(long long x) // good for many reverses
{
	const int bit_mask = 0xFFFF;
	const int word_size = 16;
	return (reversed_array[x&bit_mask] << (3 * word_size)) |
		(reversed_array[(x >> word_size)&bit_mask] << (2 * word_size)) |
		(reversed_array[(x >> (2 * word_size))&bit_mask] << (word_size)) |
		(reversed_array[(x >> (3 * word_size))&bit_mask]);
} // O(n/L) 64/16

void main(int argc, char* argv[])
{
	reversed_array=build_array();
	std::random_device rd;
	std::mt19937 mt((random_device())());
	uniform_int_distribution<long> dist{0,numeric_limits<long>::max()};
	for (int i = 0; i < 1; ++i)
	{
		auto random = dist(mt);
		assert(brute_force_reverse(random, 63) == reverse(random));
	}
}