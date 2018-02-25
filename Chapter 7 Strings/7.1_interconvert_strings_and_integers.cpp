// interconvert strings and integers
#include <string>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <random>
#include <numeric>
using namespace std;

int to_i(const string& s)
{
	int res = 0;
	for (int index=s[0]=='-'?1:0; index < s.size(); ++index)
	{
		int digit = s[index] - '0';
		res = res * 10 + digit;
	}
	return s[0]=='-'?-res:res;
} // time O(n) space O(1)

string to_s(int n)
{
	string ans{};
	if (n < 0)
	{
		ans.push_back('-');
		n = -n;
	}
	int digits = floor(log10(n));
	int mask = pow(10, digits);
	for (int i = 0; i <= digits; ++i)
	{
		int num = n / mask;
		n %= mask;
		mask /= 10;
		ans += '0'+num;
	}
	return ans;
}

string to_s2(int n)
{
	string ans{};
	bool is = false;
	if (n < 0)
	{
		is = true;
		n = -n;
	}

	while (n)
	{
		int mod = n % 10;
		int c = '0' + mod;
		n /= 10;
		ans.push_back(c);
	}
	if (is)ans.push_back('-');
	return {ans.rbegin(), ans.rend()};
} // time O(log10(n)) space O(log10(n))

void main()
{
	mt19937 mt{ random_device{}() };
	uniform_int_distribution<int>dist{ numeric_limits<int>::min(),numeric_limits<int>::max() };
	for (int times = 0; times < 1000; ++times)
	{
		auto number = dist(mt);

		string check_string = to_string(number);
		int check_int = stoi(check_string);
		
		string my_string = to_s(number);
		int my_int = to_i(my_string);

		assert(my_int == check_int);
		assert(my_string == check_string);
	}
	system("pause");
}