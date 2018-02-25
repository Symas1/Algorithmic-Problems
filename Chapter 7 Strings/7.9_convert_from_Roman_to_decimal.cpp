// convert from Roman to decimal
#include <string>
#include <iostream>
#include <unordered_map>
#include <map>
#include <assert.h>
#include <functional>
#include <algorithm>
#include <numeric>
#include <random>
using namespace std;

unordered_map<char, int>numbers{ {'I',1}, {'V',5} ,{ 'X',10 } ,{ 'L',50 },{ 'C',100 },{ 'D',500 },{ 'M',1000 } };

int convert2(const string& s)
{
	int res = 0;
	for (int i = s.size() - 1, prev = 0; i >= 0; --i)
	{
		if (prev > numbers[s[i]])res -= numbers[s[i]];
		else res += numbers[s[i]];
		prev = numbers[s[i]];
	}
	return res;
} // time O(n), space O(1)

bool check(const string& s)
{
	int smallest= 0;
	bool used = false;
	for (int i = 1; i<s.size(); ++i)
	{
		if (numbers[s[i]] > numbers[s[smallest]])
		{
			if (used)return false;
			if (smallest + 1 == i)
			{
				used = true;
				if (s[smallest] == 'I' && (s[i] == 'V' || s[i] == 'X'))continue;
				if (s[smallest] == 'X' && (s[i] == 'L' || s[i] == 'C'))continue;
				if (s[smallest] == 'C' && (s[i] == 'D' || s[i] == 'M'))continue;
				else return false;
			}
			else return false;
		}
		else if (numbers[s[i]] <= numbers[s[smallest]])
		{
			if (numbers[s[i]] < numbers[s[smallest]])used = false;
			smallest = i;
		}
	}
	return true;
} // time O(n) space O(1)

map<int,string,greater<int>>s={ {1000,"M"},{ 900,"CM"},{ 500,"D" },{ 400, "CD" },{ 100,"C" },{ 90,"XC" },{ 50,"L" },{ 40,"XL" },
{ 10,"X" },{ 9, "IX"},{ 5,"V" },{ 4,"IV" },{ 1,"I" }};
string to_roman(int n)
{
	if (n == 0)return{};
	string res{};
	auto iter = find_if(s.begin(), s.end(), [n](const pair<int, string>&a) {return a.first <= n; });
	for (;iter!=s.end();++iter)
	{
		while (n / iter->first > 0)
		{
			res += iter->second;
			n -= iter->first;
		}
		if (n == 0)return res;
	}
	return res;
} //time O(n/1000)~O(n), space O(n) 

void test_convert();
void test_check();

void main()
{
	test_convert();
	test_check();
	assert(to_roman(98) == "XCVIII");
	assert(to_roman(499) == "CDXCIX");
	mt19937 mt{ random_device{}() };
	uniform_int_distribution<int>dist{ 0,100000 };
	for (int i = 0; i < 1000; ++i)
	{
		int num = dist(mt);
		assert(check(to_roman(num)));
	}
	system("pause");
}

void test_convert()
{
	assert(convert2("XXXXXIIIIIIIII") == 59);
	assert(convert2("LIX") == 59);
	assert(convert2("LVIIII") == 59);
	assert(7 == convert2("VII"));
	assert(184 == convert2("CLXXXIV"));
	assert(9 == convert2("IX"));
	assert(40 == convert2("XL"));
	assert(60 == convert2("LX"));
	assert(1500 == convert2("MD"));
	assert(400 == convert2("CD"));
	assert(1900 == convert2("MCM"));
	assert(9919 == convert2("MMMMMMMMMCMXIX"));
}

void test_check()
{
	assert(check("CMIX"));
	assert(check("DC"));
	assert(check("CMXCIX"));
	assert(check("CCM"));
	assert(check("CDXCIX"));

	assert(!check("CMCM"));
	assert(!check("IXIX"));
	assert(!check("CDM"));
	assert(!check("IXC"));
	assert(!check("CMM"));
	assert(!check("DM"));
	assert(!check("CMIXCM"));
	assert(!check("CCMM"));
	assert(!check("IXXC"));
}