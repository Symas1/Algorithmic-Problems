// merge two sorted arrays
#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <iterator>
#include <random>
#include <numeric>
using namespace std;

void compute(vector<int>&first, const vector<int>&second, int first_valid_index)
{
	int second_valid_index = second.size() - 1;
	int write_index = first_valid_index + second.size();
	while (first_valid_index >= 0 && second_valid_index >= 0)
	{
		first[write_index--] = first[first_valid_index] < second[second_valid_index] ? second[second_valid_index--] : 
			first[first_valid_index--];
	}
	while (second_valid_index >= 0)first[write_index--] = second[second_valid_index--];
} // time O(n+m); space O(1)

void small_test();

void main()
{
	small_test();
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times)
	{
		const int max_size = 100;
		vector<int>first(uniform_int_distribution<>{0, max_size}(mt));
		vector<int>second(uniform_int_distribution<>{0, max_size}(mt));
		generate(first.begin(), first.end(), [&mt]() {return uniform_int_distribution<>{numeric_limits<int>::min(), numeric_limits<int>::max()}(mt); });
		generate(second.begin(), second.end(), [&mt]() {return uniform_int_distribution<>{numeric_limits<int>::min(), numeric_limits<int>::max()}(mt); });
		sort(second.begin(), second.end());
		sort(first.begin(), first.end());

		vector<int>check{};
		merge(first.begin(), first.end(), second.begin(), second.end(), back_inserter(check));

		int index_first = first.size() - 1;
		first.resize(first.size() + second.size());
		compute(first, second, index_first);
		assert(equal(check.begin(), check.end(), first.begin(), first.end()));
	}
	system("pause");
}

void small_test()
{
	vector<int>first(7);
	first[0] = 5; first[1] = 13; first[2] = 17;
	vector<int> second{ 3,7,11,19 };
	compute(first, second, 2);

	vector<int>first_check{ 5,13,17 };
	vector<int>check{};
	merge(first_check.begin(), first_check.end(), second.begin(), second.end(), back_inserter(check));

	assert(equal(check.begin(), check.end(), first.begin(), first.end()));
}