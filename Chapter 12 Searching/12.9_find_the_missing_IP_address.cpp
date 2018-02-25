// find the missing IP address
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <bitset>
#include <stdexcept>
#include <random>
#include <numeric>
#include <algorithm>
#include <assert.h>
using namespace std;

int find_missing(ifstream& ifs)
{
	const int buckets = 1 << 16;
	array<int, buckets>arr{};
	for (int ip; ifs >> ip;)
	{
		ip = ip >> 16; // last 16 bits
		++arr[ip];
	}

	int candidate;
	for (int i = 0; i < arr.size(); ++i)
	{
		if (arr[i] < buckets)
		{
			candidate = i;
			break;
		}
	}

	ifs.clear();
	ifs.seekg(0, ios::beg);
	bitset<buckets>bits(0);
	for (int ip; ifs >> ip;)
	{
		int upper_part = ip >> 16;
		if (upper_part == candidate)
		{
			int lower_part = ip & ((1 << 16) - 1);
			bits.set(lower_part);
		}
	}
	ifs.close();

	for (int i = 0; i < bits.size(); ++i)
	{
		if (bits[i] == 0)
		{
			return (candidate << 16) | i;
		}
	}
	throw invalid_argument("no missing element");
} // time O(n), space O(1)

int main(int argc, char* argv[])
{
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 10; ++times)
	{
		vector<int>arr(uniform_int_distribution<int>{0, 100000}(mt));
		iota(arr.begin(), arr.end(), 0);
		ofstream ofs("ips.txt");
		for (int i = 0; i < arr.size(); ++i)
		{
			ofs << arr[i] << endl;
		}
		ofs.close();
		ifstream ifs("ips.txt");
		int missing = find_missing(ifs);
		assert(!binary_search(arr.begin(), arr.end(), missing));
		remove("ips.txt");
	}
	system("pause");
	return 0;
}