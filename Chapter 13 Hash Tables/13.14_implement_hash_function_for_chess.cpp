// implement a hash function for chess
#include <bitset>
#include <random>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <numeric>
#include <iostream>
#include <assert.h>
using namespace std;

const unordered_map<bitset<2>, bitset<7>> cache_hash(const array<bitset<2>, 3>&states)
{
	mt19937 mt{ random_device{}() };
	unordered_map<bitset<2>, bitset<7>>hashes{};
	unordered_set<bitset<7>>used{};
	for (size_t i = 0; i < states.size(); ++i)
	{
		while (true)
		{
			const bitset<7>rand = uniform_int_distribution<>{ 0, 127 }(mt);
			if (used.count(rand))continue;
			else
			{
				used.emplace(rand);
				hashes.emplace(states[i], rand);
				break;
			}
		}
	}
	return hashes;
}

bitset<7> initial_hash(const unordered_map<bitset<2>, bitset<7>>&hashes, const array<array<bitset<2>, 2>, 2>& current)
{
	bitset<7>hash{};
	for (size_t i = 0; i < current.size(); ++i)
	{
		for (size_t j = 0; j < current.size(); ++j)
		{
				auto iter_current = hashes.find(current[i][j]);
				hash ^= iter_current->second;
		}
	}
	return hash;
}

bitset<7> hash_board(const unordered_map<bitset<2>, bitset<7>>&hashes,const array<array<bitset<2>, 2>, 2>& current, 
	const array<array<bitset<2>, 2>, 2>&next, bitset<7>hash)
{
	for (size_t i = 0; i < current.size(); ++i)
	{
		for (size_t j = 0; j < current.size(); ++j)
		{
			if (current[i][j] != next[i][j])
			{
				auto iter_current = hashes.find(current[i][j]);
				auto iter_next = hashes.find(next[i][j]);
				hash ^= iter_current->second;
				hash ^= iter_next->second;
			}
		}
	}
	return hash;
} // time O(nm) n - rows, m - cols; space O(1)

void main()
{
	// 3*3*3*3 combinations = 81
	// 2^7 = 128
	// log(base2)(3)+1 required bits for one square
	const array<bitset<2>, 3>states{ {0,1,2} };
	auto hashes = cache_hash(states);
	const array<array<bitset<2>, 2>, 2> current{ { {1,0},{0,2} } };
	auto current_hash = initial_hash(hashes, current);
	const array<array<bitset<2>, 2>, 2> next{ { { 1,2 },{ 0,0 } } };
	auto next_hash = hash_board(hashes, current, next, current_hash);
	assert(current_hash == next_hash);
	system("pause");
}