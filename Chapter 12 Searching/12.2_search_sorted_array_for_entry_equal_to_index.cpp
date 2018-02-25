#include <vector>
#include <assert.h>
#include <iostream>
using namespace std;

int search(const vector<int>&arr)
{
	int low = 0, up = arr.size() - 1;
	while (low <= up)
	{
		int mid = low + (up - low) / 2;
		int diff = arr[mid] - mid;
		if (diff < 0)low = mid + 1;
		else if (diff == 0)return mid;
		else if (diff > 0)up = mid - 1;
	}
	return -1;
} // time O(logn); space O(1)

int variant(const vector<int>& arr, int low, int up)
{
	int index = -1;
	if (low <= up)
	{
		int mid = low + (up - low) / 2;
		if (arr[mid] == mid)return mid;
		else
		{
			if (arr[mid] <= up)
			{
				index = variant(arr, mid + 1, up);
			}
			if (index == -1 && arr[low] <= mid)
			{
				index = variant(arr, low, mid - 1);
			}
		}
	}
	return index;
} // time best-case O(logn), worst-case O(n); space O(logn)

void test_search();
void test_variant();

int main(int argc, char* argv[])
{
	test_search();
	test_variant();
	system("pause");
	return 0;
}

void test_search()
{
	{
		vector<int>arr{ -2,0,2,3,6,7,9 };
		assert(search(arr) == 3);
	}
	{
		vector<int>arr{ -2,0,1,2,3,5,9 };
		assert(search(arr) == 5);
	}
	{
		vector<int>arr{ -2,0,1,2,3,4,6 };
		assert(search(arr) == 6);
	}
	{
		vector<int>arr{ -2,0,1,2,3,46 };
		assert(search(arr) == -1);
	}
}

void test_variant()
{
	{
		vector<int>arr{ 1,1,1,1,1,1,1 };
		assert(variant(arr, 0, arr.size() - 1) == 1);
	}
	{
		vector<int>arr{ -1,-1,1,1,1,1,1 };
		assert(variant(arr, 0, arr.size() - 1) == -1);
	}
	{
		vector<int>arr{ -1,-1,2,2,3,3,3 };
		assert(variant(arr, 0, arr.size() - 1) == 2);
	}
	{
		vector<int>arr{ -1,-1,2,3,3,3,3 };
		assert(variant(arr, 0, arr.size() - 1) == 3);
	}
	{
		vector<int>arr{ -1,-1,0,2,2,5,7 };
		assert(variant(arr, 0, arr.size() - 1) == 5);
	}
}