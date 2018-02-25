// search a cyclically sorted array
#include <vector>
#include <iostream>
#include <assert.h>
#include <random>
#include <algorithm>
#include <iterator>
using namespace std;

int cycle(const vector<int>&arr)
{
	int left = 0, right = arr.size() - 1;
	while (left < right)
	{
		int mid = left + (right - left) / 2;
		if (arr[mid] > arr[right])left = mid + 1;
		else if (arr[mid] < arr[right])right = mid;
	}
	return left;
} // time O(logn); space O(1)


int variant1(const vector<int>&arr)
{
	int low = 0, up = arr.size() - 1;
	while (low < up)
	{
		int mid = low + (up - low) / 2;
		if (mid - 1 >= low && arr[mid - 1] < arr[mid])low = mid;
		else if (mid - 1 >= low && arr[mid - 1] > arr[mid])up = mid - 1;
		else if (mid + 1 <= up && arr[mid + 1] > arr[mid])low = mid + 1;
		else if (mid + 1 <= up && arr[mid + 1] < arr[mid])up = mid;
	}
	return low;
} // time O(logn); space O(1)

int search(const vector<int>&arr,int k, int low, int up);
int variant2(const vector<int>&arr, int k)
{
	int min_index = cycle(arr);
	auto left = search(arr, k, 0, min_index - 1);
	return left==-1? search(arr, k, min_index, arr.size()-1):left;
} // time O(logn); space O(1)
int search(const vector<int>&arr,int k, int low, int up)
{
	while (low <= up)
	{
		int mid = low + (up - low) / 2;
		if (arr[mid] > k)
		{
			up = mid - 1;
		}
		else if (arr[mid] == k)return mid;
		else if (arr[mid] < k)low = mid + 1;
	}
	return -1;
}
int brute_variant2(const vector<int>&arr, int k)
{
	for (int i = 0; i < arr.size(); ++i)
	{
		if (arr[i] == k)return i;
	}
	return -1;
}

void test_cycle();
void test_variant2();
void test_variant1();

int main(int argc, char*argv[])
{
	test_cycle();
	test_variant2();
	test_variant1();
	system("pause");
	return 0;
}

void test_cycle()
{
	{
		vector<int>arr{ 378,478,550,631,103,203,220,234,279,368 };
		assert(cycle(arr) == 4);
	}
	{
		vector<int>arr{ 1,2,3,4,5,6 };
		assert(cycle(arr) == 0);
	}
	{
		vector<int>arr{ 1,2,3,4,5,0 };
		assert(cycle(arr) == 5);
	}
}

void test_variant2()
{
	{
		vector<int>arr{ 3,4,0,1,2 };
		assert(variant2(arr, 2) == 4);
	}
	{
		vector<int>arr{ 2,3,4,0,1 };
		assert(variant2(arr, 2) == 0);
	}
	{
		mt19937 mt{ random_device{}() };
		const int size = 100;
		for (int times = 0; times < 10; ++times)
		{
			vector<int>arr(size);
			int index = uniform_int_distribution<int>{ 0,size-1 }(mt);
			int number = size-1;
			for (int i = index; i >= 0; --i)
			{
				arr[i] = number--;
			}
			for (int i = index + 1,num=0; i < arr.size(); ++i)
			{
				arr[i] = num++;
			}
			
			for (int i = 0,num=0; i <= size; ++i)
			{
				assert(variant2(arr, num) == brute_variant2(arr, num));
				++num;
			}
		}
	}
}

void test_variant1()
{
	mt19937 mt{ random_device{}() };
	const int size = 100;
	for (int times = 0; times < 1000; ++times)
	{
		vector<int>arr(size);
		int growth_until = uniform_int_distribution<int>{ 0,size - 1 }(mt);
		int num = 0;
		for (int i = 0; i <= growth_until; ++i, ++num)
		{
			arr[i] = num;
		}
		--num;
		int biggest = num;
		--num;
		for (int i = growth_until + 1; i < arr.size(); ++i,--num)
		{
			arr[i] = num;
		}
		assert(variant1(arr) == biggest);
	}
}