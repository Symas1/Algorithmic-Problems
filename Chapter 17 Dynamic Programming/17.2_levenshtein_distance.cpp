// compute the levenshtein distance
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <numeric>
#include <random>
using namespace std;

void print_res(const string& from, const string& to, const vector<vector<int>>&nums);

int dist(const string& from, const string& to)
{
	vector<vector<int>>arr(from.size() + 1, vector<int>(to.size() + 1, 0));
	for (int i = 0; i < to.size() + 1; ++i)arr[0][i] = i;
	for (int i = 0; i < from.size() + 1; ++i)arr[i][0] = i;

	for (int i = 1; i < arr.size(); ++i)
	{
		for (int j = 1; j < arr.front().size(); ++j)
		{
			// min - delete, insert, substitute
			arr[i][j] = min({ arr[i - 1][j] + 1,
				arr[i][j - 1] + 1,
				arr[i - 1][j - 1]+ (from[i - 1] == to[j - 1] ? 0 : 1) });
		}
	}
	//print_res(from,to,arr);
	return arr.back().back();
} // time O(ab); space O(ab) a, b - strings sizes

int dist2(string from, string to)
{
	if (from.size() < to.size()) {
		swap(from, to);
	}
	vector<int>arr(to.size() + 1);
	iota(arr.begin(), arr.end(), 0);
	for (int i = 1; i <= from.size(); ++i) {
		int i_1_j_1 = arr[0]; // arr[i-1][j-1]
		arr[0] = i; // arr[i][j-1]
		for (int j = 1; j <= to.size(); ++j) {
			int i_1_j = arr[j]; // arr[i-1][j]
			// min - delete, insert, substitute
			arr[j] = min({ arr[j] + 1,
				arr[j - 1] + 1,
				i_1_j_1 + (from[i - 1] == to[j - 1] ? 0 : 1) });

			i_1_j_1 = i_1_j;
		}
	}
	return arr.back();
} // time O(ab); space O(min(a,b))

void print_res(const string& from, const string& to, const vector<vector<int>>&nums)
{
	cout << "\t\t";
	for (const auto&x : from)cout << x << "\t";
	cout << endl;
	cout << "\t";
	for (int i = 0; i < nums.front().size(); ++i)cout << nums[0][i] << "\t";
	cout << endl;
	for (int i = 1; i < nums.size(); ++i)
	{
		cout << to[i - 1] << "\t";
		for (int j = 0; j < nums.front().size(); ++j)
		{
			cout << nums[i][j] << "\t";
		}
		cout << endl;
	}
}

string gen_str(size_t size) {
	string res(size, {});
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < size; ++i) {
		res[i] = uniform_int_distribution<>{ 'a','z' }(mt);
	}
	return res;
}

void small_test()
{
	assert(dist("saturday", "sundays") == 4);
	assert(dist("abcdef", "azced") == 3);
	assert(dist2("saturday", "sundays") == 4);
	assert(dist2("abcdef", "azced") == 3);
}

void main()
{
	small_test();
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 1000; ++i)
	{
		const int min_size = 1, max_size = 20;
		auto source = gen_str(uniform_int_distribution<>{min_size, max_size}(mt));
		auto target = gen_str(uniform_int_distribution<>{min_size, max_size}(mt));
		//cout << dist(source, target) << '\t' << dist2(source, target) << endl;
		assert(dist(source, target) == dist2(source, target));
	}
	system("pause");
}