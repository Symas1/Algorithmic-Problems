// buy and sell stock twice
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <tuple>
using namespace std;

double stock_twice(const vector<double>&a)
{
	double lowest_seen = numeric_limits<double>::max();
	double profit = 0;
	vector<double>profits(a.size(), 0);

	for (int i = 0; i < a.size(); ++i)
	{
		lowest_seen = min(lowest_seen, a[i]);
		profit = max(profit, a[i] - lowest_seen);
		profits[i] = profit;
	}

	double max_seen = numeric_limits<double>::lowest();
	for (int i = a.size() - 1; i > 0; --i)
	{
		max_seen = max(max_seen, a[i]);
		profit = max(profit, max_seen - a[i] + profits[i - 1]);
	}
	return profit;
} // O(n), O(n)

double stock_twice_better(const vector<double>& a)
{
	vector<double> min{ numeric_limits<double>::max(),numeric_limits<double>::max() };
	vector<double>profits{ 0,0 };

	for (const auto& price : a)
	{
		for (int i = 1; i >= 0; --i)
		{
			profits[i] = max(profits[i], price - min[i]);
			min[i] = ::min(min[i], price - (i - 1 >= 0 ? profits[i - 1] : 0.0));
		}
	}
	return profits[1];
} // O(n), O(1)

void main()
{
	vector<double>arr{ 310,315,275,295,260,270,290,230,255,250 };
	cout << stock_twice_better(arr) << endl;
	arr = { 12,11,13,9,12,8,14,13,15 };
	cout << stock_twice_better(arr) << endl;
	system("pause");
}