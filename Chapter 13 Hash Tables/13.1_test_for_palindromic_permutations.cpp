// test for palindromic permutations
#include <unordered_set>
#include <string>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <random>
using namespace std;

bool test_str(const string& str)
{
	unordered_set<char>dictionary{};
	for (const auto& c : str)
	{
		if (dictionary.count(c))
		{
			dictionary.erase(c);
		}
		else dictionary.emplace(c);
	}
	return dictionary.size() <= 1;
} // time O(n), space O(c) c - distinct chars in the string
bool brute(const string& str)
{
	auto sorted_copy = str;
	sort(sorted_copy.begin(), sorted_copy.end());
	auto start = sorted_copy.begin();
	int dist = 0;
	bool found_odd = false;
	while (start != sorted_copy.end())
	{
		auto last = find_if_not(start, sorted_copy.end(), [&](char c) {return *start == c; });
		int dist_to_last = distance(start, last)+dist;
		if ((dist_to_last - dist) % 2)
		{
			if (found_odd)return false;
			else found_odd = true;
		}
		dist = dist_to_last;
		start = last;
	}
	return true;
} // time O(nlogn), space O(n) or O(1)

string generate_str(int size)
{
	mt19937 mt{ random_device{}() };
	string str(size, ' ');
	for (int i = 0; i < size; ++i)
	{
		str[i] = uniform_int_distribution<int>{ 0,25 }(mt)+(uniform_int_distribution<>{0, 1}(mt) ? 'a' : 'A');
	}
	return str;
}

void small_test();

int main(int argc, char* argv[])
{
	small_test();
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times)
	{
		const string str = generate_str(uniform_int_distribution<>{1, 100}(mt));
		assert(brute(str) == test_str(str));
	}

	system("pause");
	return 0;
}

void small_test()
{
	assert(test_str("edified"));
	assert(test_str("rotator"));
	assert(test_str("level"));
	assert(test_str("foobaraboof"));
	assert(!test_str("foobaraboo"));

	assert(brute("edified"));
	assert(brute("rotator"));
	assert(brute("level"));
	assert(brute("foobaraboof"));
	assert(!brute("foobaraboo"));
}