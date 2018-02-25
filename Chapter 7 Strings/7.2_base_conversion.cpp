// base conversion
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <assert.h>
#include <random>
#include <numeric>
//#include <cctype>
using namespace std;

string to_decimal(const string& s, int base1)
{
	int decimal = 0;
	for (int i = s.front() == '-' ? 1 : 0; i < s.size(); ++i)
	{
		decimal *= base1;
		int current_num = (!isdigit(s[i])) ?
			s[i] - static_cast<char>(55) :
			s[i] - '0';
		decimal += current_num;
	}
	return to_string(decimal);
}

string convert(const string& s, int base1, int base2)
{
	int decimal = 0;
	for (int i = s.front() == '-' ? 1 : 0; i < s.size(); ++i)
	{
		decimal *=base1;
		int current_num = (!isdigit(s[i])) ?
			s[i] - static_cast<char>(55) :
			s[i] - '0';
		decimal += current_num;
	}

	string r{};
	while (decimal)
	{
		int mod = decimal%base2;
		decimal /= base2;
		char c = (0 <= mod && mod<=9) ? '0' + mod : static_cast<char>(55) + static_cast<char>(mod);
		r.push_back(c);
	}
	if (s.front() == '-')r.push_back('-');
	return{ r.rbegin(),r.rend() };

	//int power = floor(log(decimal) / log(base2));
	//string res(power + 1, '0');
	//for (int i = 0; i < res.size() || decimal; ++i)
	//{
	//	int j = decimal%base2;
	//	char a = (j >= 0 && j <= 9) ?
	//		'0' + j :
	//		static_cast<char>(55) + j;
	//	res[res.size() - 1 - i] = a;
	//	decimal /= base2;
	//}
	//if (s.front() == '-')res.insert(res.begin(), { '-' });
	//return res;
} // time O(n(1+logbase2(base1)) space O(logbase2(base1))

void small_test();
void test();

void main()
{
	small_test();
	test();
	system("pause");
}

void test()
{
	mt19937 mt{ random_device{}() };
	uniform_int_distribution<int>dist{ 0,numeric_limits<int>::max() };
	for (int i = 2; i <= 16; ++i)
	{
		for (int times = 0; times < 1000; ++times)
		{
			int number = dist(mt);
			auto answer = convert(to_string(number), 10, i);
			auto check = to_decimal(answer, i);
			assert(number == stoi(check));
		}
	}
}

void small_test()
{
	assert(convert("3E7", 16, 2) == "1111100111");
	assert(convert("3E7", 16, 3) == "1101000");
	assert(convert("3E7", 16, 4) == "33213");
	assert(convert("3E7", 16, 5) == "12444");
	assert(convert("3E7", 16, 6) == "4343");
	assert(convert("3E7", 16, 7) == "2625");
	assert(convert("3E7", 16, 8) == "1747");
	assert(convert("3E7", 16, 9) == "1330");
	assert(convert("3E7", 16, 10) == "999");
	assert(convert("3E7", 16, 11) == "829");
	assert(convert("3E7", 16, 12) == "6B3");
	assert(convert("3E7", 16, 13) == "5BB");
	assert(convert("3E7", 16, 14) == "515");
	assert(convert("3E7", 16, 15) == "469");
	assert(convert("3E7", 16, 16) == "3E7");
}
