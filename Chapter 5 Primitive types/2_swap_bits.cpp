// swap bits in positions i and j

#include <random>
#include <bitset>
#include <assert.h>
#include <numeric>
using namespace std;

int swap_bits(int x, int i, int j)
{
	if (((x >> i) & 1) != ((x >> j) & 1))
	{
		int bit_mask = (1 << i) | (1 << j);
		x ^= bit_mask;
	}
	return x;
}

void main()
{
	mt19937 mt((random_device())());
	uniform_int_distribution<int> rand_int{ 0,numeric_limits<int>::max() };
	for (int i = 0; i < 10000; ++i)
	{
		auto number = rand_int(mt);
		auto ii = number % 32;
		auto j = number % 32;
		if (ii == j)continue;
		bitset<32>bitset = number;
		if (bitset[ii] != bitset[j])
		{
			bitset.flip(ii);
			bitset.flip(j);
		}
		auto result = swap_bits(number, ii, j);
		assert(result == ((int)bitset.to_ullong()));
	}
}