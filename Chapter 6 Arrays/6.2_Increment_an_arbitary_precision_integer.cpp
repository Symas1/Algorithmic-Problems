//INCREMENT AN ARBITRARY-PRECISION INTEGER
#include <vector>
#include <iostream>
#include <assert.h>
#include <random>
#include <numeric>
#include <string>
#include <bitset>
#include <algorithm>
using namespace std;

void increment(vector<int>& arr)
{
	++arr.back();
	for (int i = arr.size() - 1; i > 0 && arr[i] == 10; --i)
	{
		arr[i] = 0;
		++arr[i - 1];
	}
	if (arr[0] == 10)
	{
		arr[0] = 0;
		arr.insert(arr.begin(), 1);
	}
} // O(n)

string add_bits(const string& a, const string& b)
{
	int mask = 0;
	string ans{};
	for (int i = 0; i < min(a.size(), b.size()); ++i)
	{
		auto a_bit = stoi(string(1, a[a.size() - 1 - i]));
		auto b_bit = stoi(string(1, b[b.size() - 1 - i]));
		int new_mask = (a_bit&b_bit) || (a_bit & mask) || (b_bit & mask);
		int new_num = mask ^ a_bit ^ b_bit;
		ans = to_string(new_num) + ans;

		mask = new_mask;
	}
	if (mask)ans = to_string(mask) + ans;
	return ans;
} // O(n)

void test_increment();
void test_add_bits();

void main()
{
	test_increment();

	test_add_bits();

	system("pause");
}

void test_increment()
{
	vector<int>arr{};
	{
		arr.insert(arr.end(), { 9, 9 });
		increment(arr);
		assert(arr.size() == 3 && arr[0] == 1 && arr[1] == 0 && arr[2] == 0);
		arr.clear();
	}

	{
		arr.insert(arr.end(), { 3, 1, 4 });
		increment(arr);
		assert(arr.size() == 3 && arr[0] == 3 && arr[1] == 1 && arr[2] == 5);
		arr.clear();
	}

	{
		arr.insert(arr.end(), { 3, 9, 9 });
		increment(arr);
		assert(arr.size() == 3 && arr[0] == 4 && arr[1] == 0 && arr[2] == 0);
		arr.clear();
	}
}

void test_add_bits()
{
	mt19937 mt{ random_device{}() };
	uniform_int_distribution<int> dist(0, numeric_limits<int>::max() / 2);
	for (int times = 0; times < 1000; ++times)
	{
		auto first = dist(mt);
		auto second = dist(mt);
		auto first_s = bitset<32>(first).to_string();
		auto second_s = bitset<32>(second).to_string();

		auto result_s = add_bits(first_s, second_s);
		auto result = stoi(result_s, nullptr, 2);

		assert(result == (first + second));
	}
}