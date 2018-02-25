// search in a 2d sorted array
#include <vector>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <numeric>
using namespace std;

bool search(const vector<vector<int>>&arr, int k)
{
	int row = 0, column = arr.begin()->size() - 1;
	while (row < arr.size() && column >= 0)
	{
		if (arr[row][column] < k)++row;
		else if (arr[row][column] > k)--column;
		else return true;
	}
	return false;
} // time O(n+m) n - rows, m - cols; space O(1)

bool brute(const vector<vector<int>>&arr, int k)
{
	for (int i = 0; i < arr.size(); ++i)
	{
		for (int j = 0; j < arr[i].size(); ++j)
		{
			if (arr[i][j] == k)return true;
		}
	}
	return false;
}

int main(int arcg, char* argv[])
{
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times)
	{
		int rows = uniform_int_distribution<int>{ 1,10 }(mt);
		int cols = uniform_int_distribution<int>{ 1,10 }(mt);
		vector<vector<int>>arr(rows, vector<int>(cols));

		for (int i = 0; i < arr.size(); ++i)
		{
			for (int j = 0; j < arr[i].size(); ++j)
			{
				int up = i == 0 ? 0 : arr[i - 1][j];
				int left = j == 0 ? 0 : arr[i][j - 1];
				arr[i][j] = max(up, left) + uniform_int_distribution<int>{0, 20}(mt);
			}
		}

		int biggest = arr[rows - 1][cols - 1];
		for (int i = 0; i < 100; ++i)
		{
			int k = uniform_int_distribution<int>{ 0,biggest * 2 }(mt);
			assert(brute(arr, k) == search(arr, k));
		}
	}
	system("pause");
	return 0;
}