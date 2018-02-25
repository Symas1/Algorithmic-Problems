// rearrange array elements so that even entries appear first
#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <random>
#include <numeric>
#include <tuple>
using namespace std;

void rearrange(vector<int>& arr)
{
	for (int elem=0,even=0;elem<arr.size();++elem)
	{
		if (arr[elem] % 2 == 0)
		{
			swap(arr[elem], arr[even]);
			++even;
		}
	}
} // O(n)

void rearrange2(vector<int>& arr)
{
	int even = 0, odd = arr.size() - 1;
	while (even < odd)
	{
		if (arr[even] % 2 == 0)
		{
			++even;
		}
		else
		{
			swap(arr[even], arr[odd]);
			--odd;
		}
	}
}  // O(n)

void main()
{
	const int size = 100;

	mt19937 mt((random_device())());
	uniform_int_distribution<int> dist{ numeric_limits<int>::min(),numeric_limits<int>::max() };
	for(int times=0;times<1000;++times)
	{
		vector<int>arr{};
		for (int i = 0; i < size; ++i)
		{
			arr.push_back(dist(mt));
		}

		rearrange2(arr);

		for (auto i = make_tuple(0,false); get<0>(i) < size; ++get<0>(i))
		{
			if (arr[get<0>(i)] % 2 == 0)assert(get<1>(i) == false);
			else get<1>(i) = true;
		}
	}
	system("pause");
}