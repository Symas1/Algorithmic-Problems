// sample online data
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <random>
#include <numeric>
#include <assert.h>
#include <algorithm>
#include <iterator>
using namespace std;


//assuption: k elems in stream
vector<int> sample(istringstream& s, int k)
{
	vector<int> data{};
	int d;
	for (int i = 0; i<k&&s >> d; ++i)
	{
		data.emplace_back(d);
	}

	mt19937 mt{ random_device{}() };

	int read_elems = data.size();
	while (s >> d)
	{
		++read_elems;
		uniform_int_distribution<int> dist{ 0,read_elems - 1 };
		int index = dist(mt);
		if (index < k)
		{
			data[index] = d;
		}
	}
	return data;
} // time ? propotional to n in stream/ space O(k)

void main()
{
	mt19937 mt{ random_device{}() };
	uniform_int_distribution<int> n_dist{ 1,100 };
	const int n = n_dist(mt);
	uniform_int_distribution<int> k_dist{ 0,n };
	const int k = k_dist(mt);

	vector<int>packets(n);
	iota(packets.begin(), packets.end(), 0);
	string s{};
	for (const auto& p : packets)
	{
		s += to_string(p);
		s += ' ';
	}
	istringstream str{ s };

	auto ans = sample(str, k);
	assert(ans.size() == k);

	copy(ans.begin(), ans.end(), ostream_iterator<int>{ cout, " "  });

	system("pause");
}