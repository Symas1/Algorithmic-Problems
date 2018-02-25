// compute the spreadsheet column encoding
#include <string>
#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;
 
int id(const string& s)
{
	int id = 0;
	for (int i = 0; i < s.size(); ++i)
	{
		id = id * 26 + (s[i] - static_cast<char>(64));
	}
	return id;
} // time O(n) n - size of string , space O(1)

int variant1(const string& s)
{
	int id = 0;
	for (int i = 0; i < s.size(); ++i)
	{
		id = id * 26 + (s[i] - static_cast<char>(64));
	}
	return id-1;
}

string variant2(int id)
{
	string ans{};
	while (id)
	{
		int mod = (id - 1) % 26;
		char digit = static_cast<char>(65)+mod;
		ans.push_back(digit);
		id = (id-mod) / 26;
	}
	return{ ans.rbegin(),ans.rend() };
}

void test_id();
void test_variant1();
void test_variant2();

void main()
{
	test_id();

	test_variant1();

	test_variant2();

	system("pause");
}

void test_id() 
{
	assert(702 == id("ZZ"));
	assert(52 == id("AZ"));
	assert(27 == id("AA"));
	assert(2109 == id("CCC"));
}

void test_variant1()
{
	assert(0 == variant1("A"));
	assert(1 == variant1("B"));
	assert(25 == variant1("Z"));
	assert(26 == variant1("AA"));
}

void test_variant2()
{
	assert(variant2(52) == "AZ");
	assert(variant2(702) == "ZZ");
	assert(variant2(27) == "AA");
	assert(variant2(2109) == "CCC");
}