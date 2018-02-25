// check if number is palindrom
#include <iostream>
#include <assert.h>
#include <cmath>
#include <string>
#include <random>
#include <numeric>
using namespace std;

bool is_palindrome_first(int x) // reverses
{
	if (x < 0)return false;
	int res = 0;
	int remaining = x;
	while (remaining)
	{
		res = res * 10 + remaining % 10;
		remaining /= 10;
	}
	return res == x;
} // O(n)

bool is_palindrome(int x)
{
	if (x < 0)return false;
	const int  digits = static_cast<int>(floor(log10(x))+1); // number of digits in number
	int mask = pow(10, digits - 1);
	for (int i = 0; i < digits/2; ++i)
	{
		if (x%10!=x/mask) return false;
		x %= mask; // last digit
		x /= 10; // first digit
		mask /= 100;
	}
	return true;
} // O(n)

bool check(int x)
{
	if (x < 0)return false;
	string str = to_string(x);
	reverse(str.begin(), str.end());
	return str == to_string(x);
}


void main()
{
	mt19937 mt((random_device())());
	uniform_int_distribution<int> dist{ numeric_limits<int>::min(),numeric_limits<int>::max() };
	for (int i = 0; i < 10000; ++i)
	{
		auto rand = dist(mt);
		assert(check(rand) == is_palindrome(rand));
	}
	system("pause");
}