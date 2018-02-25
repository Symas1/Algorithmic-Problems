// pascals triangle
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <assert.h>
using namespace std;

vector<int> triangle(int n)
{
	if (n == 0)return{};
	vector<int>res{ 1 };
	for (int i = 1; i < n; ++i)
	{
		for (int j = 0; j < i + 1; ++j)
		{
			if (j == 0 || j == i)
			{
				res.emplace_back(1);
				continue;
			}
			res.emplace_back(res[res.size()-1 - (i - 1)] + res[res.size()-1 - (i)]);
		}
	}
	return res;
} // time O(n^2), space O(n^2)

void print(const vector<int>& arr)
{
	int index = 0;
	for (int i = 0;; ++i)
	{
		for (int j = 0; j < i + 1; ++j)
		{
			cout << arr[index++]<<" ";
		}
		cout << endl;
		if (index >= arr.size())return;
	}
}

vector<int> nth_row(int n)
{
	if (n == 0)return{};
	vector<int>res{ 1 };
	for (int i = 1; i < n; ++i)
	{
		for (int j = 0; j < i + 1; ++j)
		{
			if (j == 0 || j == i)
			{
				res.emplace_back(1);
				continue;
			}
			res.emplace_back(res[j-1] + res[j]);
		}
		res.erase(res.begin(), res.begin()+i);
	}
	return res;
} // time O(n^2) space O(n)


vector<int> n_row(int n)
{
	--n;
	vector<int>res{ 1 };
	for (int i = 0,prev=1; i < ceil(n / 2); ++i)
	{
		int new_num = (prev)*(n - i) / (i + 1);
		prev = new_num;
		res.emplace_back(new_num);
	}

	for (int i = 0,index=(n+1)/2-1; i < (n+1)/2; ++i)
	{
		res.push_back(res[index--]);
	}
	return res;
} // time O(n), space O(n)

void main()
{
	const int size = 30;
	auto arr = triangle(size);
	print(arr);
	for (int i = 1,index=0; i <= size; ++i)
	{
		auto row = nth_row(i);
		auto r = n_row(i);
		assert(equal(arr.begin() + index, arr.begin() + index+i, row.begin(), row.end()));
		assert(equal(row.begin(), row.end(), r.begin(), r.end()));
		index += i;
	}
	system("pause");
}