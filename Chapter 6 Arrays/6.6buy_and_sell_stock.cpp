//buy and sell stock once with maximum profit
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <assert.h>
using namespace std;

int stock(const vector<int>& a)
{
	int min_seen = numeric_limits<int>::max();
	int profit = 0;

	for (int i = 0; i < a.size(); ++i)
	{
		profit = max(profit, a[i] - min_seen);
		min_seen=min(min_seen,a[i]);
	}

	return profit;
} // O(n)

int longest(const vector<int>&a)
{
	int longest = 1;

	for (int i = 1,cur=1; i < a.size(); ++i)
	{
		if (a[i] == a[i - 1])longest = max(longest, ++cur);
		else cur = 1;
	}
	return longest;
}

void main()
{
	vector<int> arr{ 310,315,275,295,260,270,290,230,255,250 };
	assert(stock(arr) == 30);

	arr={ 1,1,1,2,2,2,2,3,3,5,5,6,7,9,9,9 };
	assert(longest(arr) == 4);
	arr = { 1,1,1,1,1,2,2,2,2,3,3,5,5,6,7,9,9,9 };
	assert(longest(arr) == 5);
	arr = { 1,2,3,4,5,6 };
	assert(longest(arr) == 1);
	system("pause");
}