// Write a program that takes an array A and an index i into A, and rearranges the
//elements such that all elements less than A[i](the "pivot") appear first, followed by
//elements equal to the pivot, followed by elements greater than the pivot.
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <tuple>
#include <assert.h>
#include <numeric>
using namespace std;

void rearrange(vector<int>& arr, const int ind)
{
	int less = 0;
	int bigger = arr.size();
	int pivot = arr[ind];
	int unknown = 0;
	while (unknown < bigger)
	{
		if (arr[unknown] < pivot)
		{
			swap(arr[unknown++], arr[less++]);
		}
		else if (arr[unknown] == pivot)
		{
			++unknown;
		}
		else
		{
			swap(arr[unknown], arr[--bigger]);
		}
	}
} // O(n) , memory O(1)

void rearrange_variant1(vector<int>& arr)
{
	int first_seg_elem = arr[0];
	int second_seg_elem = numeric_limits<int>::min();
	int third_seg_elem = numeric_limits<int>::min();

	int bottom = 1;
	int current = 1;
	int top = arr.size();

	while (current < top)
	{
		if (arr[current] == first_seg_elem)
		{
			swap(arr[bottom], arr[current]);
			++bottom;
			++current;
		}
		else if (second_seg_elem == numeric_limits<int>::min() || arr[current] == second_seg_elem)
		{
			second_seg_elem = arr[current];
			++current;
		}
		else if (third_seg_elem == numeric_limits<int>::min() || arr[current] == third_seg_elem)
		{
			third_seg_elem = arr[current];
			swap(arr[current], arr[--top]);
		}
	}
} // O(n), memory O(1)

void rearrange_variant2(vector<int>& arr)
{
	int first_seg_elem = arr[0];
	int second_seg_elem = numeric_limits<int>::min();
	int third_seg_elem = numeric_limits<int>::min();
	int fourth_seg_elem = numeric_limits<int>::min();

	int first = 1;
	int second = 1;
	int current = 1;
	int top = arr.size();

	while (current < top)
	{
		if (arr[current] == first_seg_elem)
		{
			swap(arr[first++], arr[current]);
			swap(arr[current++], arr[second++]);
		}
		else if (arr[current] == second_seg_elem || second_seg_elem == numeric_limits<int>::min())
		{
			second_seg_elem = arr[current];
			swap(arr[second++], arr[current++]);
		}
		else if (arr[current] == third_seg_elem || third_seg_elem == numeric_limits<int>::min())
		{
			third_seg_elem = arr[current];
			++current;
		}
		else if (arr[current] == fourth_seg_elem || fourth_seg_elem == numeric_limits<int>::min())
		{
			fourth_seg_elem = arr[current];
			swap(arr[current], arr[--top]);
		}
	}
}

void rearrange_variant3(vector<bool>& arr)
{
	int bottom = 0;
	int top = arr.size();
	while (bottom < top)
	{
		if (arr[bottom] == false)
		{
			++bottom;
		}
		else
		{
			swap(arr[bottom], arr[--top]);
		}
	}
}

void rearrange_variant4(vector<bool>& arr)
{
	for (int i = arr.size() - 1, top = arr.size(); i >= 0; --i)
	{
		if (arr[i] == true)
		{
			swap(arr[i], arr[--top]);
		}
	}
}

void test_rearrange();
void test_rearrange_variant1();
void test_rearrange_variant2();
void test_rearrange_variant3();
void test_rearrange_variant4();

void main()
{
	test_rearrange();

	test_rearrange_variant1();

	test_rearrange_variant2();

	test_rearrange_variant3();

	test_rearrange_variant4();
	system("pause");
}

void test_rearrange()
{
	const int size = 100;

	mt19937 mt((random_device{})());
	uniform_int_distribution<int> dist{ 0,2 };
	uniform_int_distribution<int> pivot{ 0, size - 1 };
	for (int i = 0; i < 1000; ++i)
	{
		vector<int>arr{};
		for (int j = 0; j < size; ++j)
		{
			arr.push_back(dist(mt));
		}

		int pivot_index = pivot(mt);
		int pivot_number = arr[pivot_index];
		rearrange(arr, pivot_index);


		for (auto i = make_tuple(0, false, false); get<0>(i) < arr.size(); ++get<0>(i))
		{
			if (arr[get<0>(i)] < pivot_number)
			{
				assert(get<1>(i) == false && get<2>(i) == false);
			}
			else if (arr[get<0>(i)] == pivot_number)
			{
				get<1>(i) = true;
				assert(get<2>(i) == false);
			}
			else if (arr[get<0>(i)] > pivot_number)
			{
				get<2>(i) = true;
			}
		}
	}
}

void test_rearrange_variant1()
{
	const int size = 100;

	mt19937 mt((random_device{})());
	uniform_int_distribution<int> dist{ 0,2 };
	for (int i = 0; i < 1000; ++i)
	{
		vector<int>arr{};
		for (int j = 0; j < size; ++j)
		{
			arr.push_back(dist(mt));
		}

		rearrange_variant1(arr);

		for (auto i = make_tuple(1, arr[0], numeric_limits<int>::min(), numeric_limits<int>::min());
			get<0>(i) < arr.size(); ++get<0>(i))
		{
			if (arr[get<0>(i)] == get<1>(i))
			{
				assert(get<2>(i) == numeric_limits<int>::min() && get<3>(i) == numeric_limits<int>::min());
			}
			else if (get<2>(i) == numeric_limits<int>::min() || arr[get<0>(i)] == get<2>(i))
			{
				get<2>(i) = arr[get<0>(i)];
				assert(get<3>(i) == numeric_limits<int>::min());
			}
			else if (get<3>(i) == numeric_limits<int>::min() || arr[get<0>(i)] == get<3>(i))
			{
				get<3>(i) = arr[get<0>(i)];
			}
		}
	}
}

void test_rearrange_variant2()
{
	const int size = 100;

	mt19937 mt((random_device{})());
	uniform_int_distribution<int> dist{ 0,3 };
	for (int i = 0; i < 1000; ++i)
	{
		vector<int>arr{};
		for (int j = 0; j < size; ++j)
		{
			arr.push_back(dist(mt));
		}

		rearrange_variant2(arr);

		for (auto i = make_tuple(1, arr[0], numeric_limits<int>::min(), numeric_limits<int>::min(), numeric_limits<int>::min());
			get<0>(i) < arr.size(); ++get<0>(i))
		{
			if (arr[get<0>(i)] == get<1>(i))
			{
				assert(get<2>(i) == numeric_limits<int>::min() && get<3>(i) == numeric_limits<int>::min() &&
					get<4>(i) == numeric_limits<int>::min());
			}
			else if (get<2>(i) == numeric_limits<int>::min() || arr[get<0>(i)] == get<2>(i))
			{
				get<2>(i) = arr[get<0>(i)];
				assert(get<3>(i) == numeric_limits<int>::min() && get<4>(i) == numeric_limits<int>::min());
			}
			else if (get<3>(i) == numeric_limits<int>::min() || arr[get<0>(i)] == get<3>(i))
			{
				get<3>(i) = arr[get<0>(i)];
				assert(get<4>(i) == numeric_limits<int>::min());
			}
			else if (get<4>(i) == numeric_limits<int>::min() || arr[get<0>(i)] == get<4>(i))
			{
				get<4>(i) = arr[get<0>(i)];
			}
		}
	}
}

void test_rearrange_variant3()
{
	const int size = 100;

	mt19937 mt((random_device{})());
	uniform_int_distribution<int> dist{ 0,1 };
	for (int i = 0; i < 1000; ++i)
	{
		vector<bool>arr{};
		for (int j = 0; j < size; ++j)
		{
			arr.push_back(dist(mt));
		}

		rearrange_variant3(arr);
		for (auto i = make_tuple(0, false); get<0>(i) < arr.size(); ++get<0>(i))
		{
			if (arr[get<0>(i)] == false)assert(get<1>(i) == false);
			else get<1>(i) = true;
		}
	}
}

void test_rearrange_variant4()
{
	const int size = 100;

	mt19937 mt((random_device{})());
	uniform_int_distribution<int> dist{ 0,1 };
	for (int i = 0; i < 1000; ++i)
	{
		vector<bool>arr{};
		for (int j = 0; j < size; ++j)
		{
			arr.push_back(dist(mt));
		}

		rearrange_variant4(arr);
		for (auto i = make_tuple(0, false); get<0>(i) < arr.size(); ++get<0>(i))
		{
			if (arr[get<0>(i)] == false)assert(get<1>(i) == false);
			else get<1>(i) = true;
		}
	}
}