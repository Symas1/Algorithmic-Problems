//advance through array

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>
using namespace std;

bool advance(const vector<int>& a)
{
	if (a.size()==1||a.empty())return true;

	for (int j = a[0]; j > 0; --j)
	{
		bool res = advance(vector<int>(a.begin() + j, a.end()));
		if (res)return true;
	}
	return false;
} //worst time O(n^2), space O(n)

bool advance1(const vector<int>&a)
{
	int furthest = 0;
	for (int i = 0; i <= furthest && furthest < a.size()-1; ++i)
	{
		furthest = max(furthest,a[i] + i);
	}

	return furthest >= a.size()-1;
} // time O(n), space O(1)


int variant_advance1(const vector<int>&a)
{
	int furthest = 0;
	int steps = 0;
	for (int i = 0; i <= furthest && furthest < a.size() - 1; ++i)
	{
		if (furthest < a[i] + i)
		{
			furthest = a[i] + i;
			++steps;
		}
	}

	return furthest >= a.size() - 1 ? steps : -1;
}

void main()
{
	vector<int> arr{ 3,3,1,0,2,0,1 };
	assert(advance1(arr) == true);
	vector<int>arr1{ 3,2,0,0,2,0,1 };
	assert(advance1(arr1) == false);
	vector<int>arr2{ 2,4,1,1,0,2,3 };
	assert(advance1(arr2) == true);


	assert(variant_advance1(arr) == 3);
	assert(variant_advance1(arr1) == -1);
	assert(variant_advance1(arr2) == 3);

	system("pause");
}