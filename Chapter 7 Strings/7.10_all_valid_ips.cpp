// compute all valid ip addresses from string
#include <string>
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <random>
#include <iterator>
using namespace std;

bool is_valid(const string& str);
vector<string> ip2(const string& str)
{
	vector<string>res{};
	for (int i = 1; i < 4; ++i)
	{
		if (i >= str.size())break;
		const string first = str.substr(0, i);
		if (is_valid(first))
		{
			for (int j = 1; j < 4; ++j)
			{
				if (i + j >= str.size())break;
				const string second = str.substr(i, j);
				if (is_valid(second))
				{
					for (int k = 1; k < 4; ++k)
					{
						if (i + j + k >= str.size())break;
						const string third = str.substr(i + j, k);
						const string fourth = str.substr(i + j + k);
						if (is_valid(third) && is_valid(fourth))
						{
							res.emplace_back(first + '.' + second + '.' + third + '.' + fourth);
						}
					}
				}
			}
		}
	}
	return res;
} // time O(1) space O(1)

bool is_valid(const string& str)
{
	if (str.size() > 3 || str.size() == 0)return false;
	if (str.front() == '0'&&str.size() > 1)return false; // '0' is valid, but '001' '01' is not
	int number = stoi(str);
	return (number >= 0 && number <= 255);
}


void variant1_helper(const string&str, const string& current_str, vector<string>&res, int current_depth, int periods);
vector<string> variant1(const string& str, int periods)
{
	vector<string>res{};
	variant1_helper(str, {}, res, 0, periods);
	return res;
}

void variant1_helper(const string&str, const string& current_str, vector<string>&res, int current_depth, int periods)
{
	if (current_depth == periods - 1)
	{
		if (current_str.size() - (current_depth) < str.size())
		{
			string last = str.substr(current_str.size() - (periods - 1));
			if (is_valid(last))res.emplace_back(current_str + last);
		}
	}
	else
	{
		for (int i = 1; i < 4; ++i)
		{
			if (current_str.size() - current_depth >= str.size())break;
			string current = str.substr(current_str.size() - current_depth, i);
			if (is_valid(current))
			{
				current += '.';
				variant1_helper(str, current_str + current, res, current_depth + 1, periods);
			}
		}
	}
} // time O(n^2*3*((1-3^periods)/(1-3)))space O(n^2+n*3^periods)

string random_string();
void test_ip2();
void test_variant1();

void main()
{
	test_ip2();
	test_variant1();
	auto v = variant1("19213123312321331123131231231312313131313131231312313123123316811",20);
	copy(v.begin(), v.end(), ostream_iterator<string>{cout, "\n"});
	system("pause");
}

void test_ip2()
{
	auto vec = ip2("255255255255");
	assert(vec.size() == 1);
	assert(vec.front() == "255.255.255.255");
	vec = ip2("19216811");
	assert(vec.size() == 9);
	vec = ip2("1111");
	assert(vec.size() == 1);
	assert(vec.front() == "1.1.1.1");
}

void test_variant1()
{
	for (int i = 0; i < 100; ++i)
	{
		string str = random_string();
		auto ip2_res = ip2(str);
		auto variant1_res = variant1(str, 4);
		sort(ip2_res.begin(), ip2_res.end());
		sort(variant1_res.begin(), variant1_res.end());
		assert(equal(ip2_res.begin(), ip2_res.end(), variant1_res.begin(), variant1_res.end()));
	}
}

string random_string()
{
	mt19937 mt{ random_device{}() };
	string res(uniform_int_distribution<int>{4, 12}(mt), ' ');
	generate(res.begin(), res.end(), [&mt]() {return uniform_int_distribution<>{0, 9}(mt)+'0'; });
	return res;
}