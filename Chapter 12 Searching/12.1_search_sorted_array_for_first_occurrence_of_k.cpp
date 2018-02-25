// search a sorted array for the first occurrence of k
#include <vector>
#include <algorithm>
#include <functional>
#include <assert.h>
#include <string>
#include <iostream>
using namespace std;

int bsearch(const vector<int>&arr, int k)
{
	int low = 0, up = arr.size() - 1;
	int result = -1;
	while (low <= up)
	{
		int mid = low + (up - low) / 2;
		if (arr[mid] > k)up = mid - 1;
		else if (arr[mid] == k)
		{
			result = mid;
			up = mid - 1;
		}
		else if (arr[mid] < k)low = mid + 1;
	}
	return result;
} // time O(logn); space O(1)

int variant1(const vector<int>&arr, int k)
{
	int low = 0, up = arr.size() - 1;
	int result = -1;
	while (low <= up)
	{
		int mid = low + (up - low) / 2;
		if (arr[mid] > k)
		{
			result = mid;
			up = mid - 1;
		}
		else if (arr[mid] == k)
		{
			low = mid + 1;
		}
		else if (arr[mid] < k)low = mid + 1;
	}
	return result;
} // time O(logn); space O(1)

int variant2(const vector<int>&arr)
{
	if (arr.size() <= 2)return -1;
	int low = 0, up = arr.size() - 1;
	while (low <= up)
	{
		int mid = low + (up - low) / 2;
		if (mid == 0) {
			low = mid + 1;
			continue;
		}
		if (arr[mid - 1] >= arr[mid] && arr[mid] <= arr[mid + 1])return mid;
		else if (arr[mid - 1] <= arr[mid])up = mid - 1;
		else if (arr[mid] >= arr[mid + 1])low = mid + 1;
	}
	return -1;
} // time O(logn) space O(1)

int variant3_left(const vector<int>&arr, int k, int index, int low, int up);
int variant3_right(const vector<int>&arr, int k, int index, int low, int up);
pair<int, int> variant3(const vector<int>&arr, int k)
{
	int low = 0, up = arr.size() - 1;
	int index = -1;
	while (low <= up)
	{
		int mid = low + (up - low) / 2;
		if (arr[mid] > k)
		{
			up = mid - 1;
		}
		else if (arr[mid] == k)
		{
			index = mid;
			break;
		}
		else if (arr[mid] < k)
		{
			low = mid + 1;
		}
	}

	if (index != -1)
	{
		return make_pair(variant3_left(arr, k, index, low, index - 1), variant3_right(arr, k, index, index + 1, up));
	}
	else return make_pair(-1, -1);
}
int variant3_left(const vector<int>&arr, int k, int index, int low, int up)
{
	while (low <= up)
	{
		int mid = low + (up - low) / 2;
		if (arr[mid] > k)up = mid - 1;
		else if (arr[mid] == k)
		{
			index = mid;
			up = mid - 1;
		}
		else if (arr[mid] < k)low = mid + 1;
	}
	return index;
}
int variant3_right(const vector<int>&arr, int k, int index, int low, int up)
{
	while (low <= up)
	{
		int mid = low + (up - low) / 2;
		if (arr[mid] > k)up = mid - 1;
		else if (arr[mid] == k)
		{
			index = mid;
			low = mid + 1;
		}
		else if (arr[mid] < k)low = mid + 1;
	}
	return index;
}


int variant4(const vector<string>&arr, const string& str)
{
	int low = 0, up = arr.size() - 1;
	while (low <= up)
	{
		int mid = low + (up - low) / 2;
		auto c = str.compare(0, str.size(), arr[mid], 0, str.size());
		if (c > 0)low = mid + 1;
		else if (c == 0)return mid;
		else if (c < 0)up = mid - 1;
	}
	return -1;
} // time O(klogn) n - array size, k - str size; space O(1)


void test_bsearch();
void test_variant1();
void test_variant2();
void test_variant3();
void test_variant4();

int main(int argc, char* argv[])
{
	test_bsearch();
	test_variant1();
	test_variant2();
	test_variant3();
	test_variant4();
	system("pause");
	return 0;
}

void test_bsearch()
{
	vector<int>arr{ -14,-14,2,108,108,243,285,285,285,401 };
	assert(bsearch(arr, 285) == 6);
	assert(bsearch(arr, 108) == 3);
	assert(bsearch(arr, -14) == 0);
	assert(bsearch(arr, -15) == -1);
}

void test_variant1()
{
	{
		vector<int>arr{ -14,-10,2,108,108,243,285,285,285,401 };
		assert(variant1(arr, 285) == 9);
		assert(variant1(arr, -13) == 1);
		assert(variant1(arr, 108) == 5);
		assert(variant1(arr, -15) == 0);
		assert(variant1(arr, 401) == -1);
	}
	{
		vector<int>arr{ -14,-10,2,108,108,243,285,285,285,285 };
		assert(variant1(arr, 285) == -1);
	}
}

void test_variant2()
{
	vector<int>arr{ 6,5,10,11,13,14,15 };
	assert(variant2(arr) == 1);
	assert(variant2({ 1,2 }) == -1);
	assert(variant2({ 1,3,2 }) == -1);
	assert(variant2({ 1,0,2 }) == 1);
	assert(variant2({ 7,3,5,8,9,0 }) == 1);
}

void test_variant3()
{
	{
		auto res = variant3({ 1,2,2,4,4,4,7,11,11,13 }, 11);
		assert(res.first == 7 && res.second == 8);
	}
	{
		auto res = variant3({ 1,2,2,4,4,4,7,11,11,13 }, 12);
		assert(res.first == -1 && res.second == -1);
	}
	{
		auto res = variant3({ 1,2,2,4,4,4,7,11,11,13 }, 2);
		assert(res.first == 1 && res.second == 2);
	}
	{
		auto res = variant3({ 1,2,2,4,4,4,7,11,11,13 }, 1);
		assert(res.first == 0 && res.second == 0);
	}
	{
		auto res = variant3({ 1,2,2,4,4,4,7,11,11,13 }, 4);
		assert(res.first == 3 && res.second == 5);
	}
	{
		auto res = variant3({ 1,2,2,4,4,4,7,11,11,13 }, 7);
		assert(res.first == 6 && res.second == 6);
	}
	{
		auto res = variant3({ 1,2,2,4,4,4,7,11,11,13 }, 13);
		assert(res.first == 9 && res.second == 9);
	}
}

void test_variant4()
{
	vector<string>arr{ "a","aacd","ab","abc","ac","acb","acd" };
	assert(variant4(arr, "acb") == 5);
	assert(variant4(arr, "acd") == 6);
	assert(variant4(arr, "aac") == 1);
	assert(variant4(arr, "aacd") == 1);
	assert(variant4(arr, "a") == 3);
	assert(variant4(arr, "ab") == 3);
	assert(variant4(arr, "ac") == 5);
	assert(variant4(arr, "aa") == 1);
}