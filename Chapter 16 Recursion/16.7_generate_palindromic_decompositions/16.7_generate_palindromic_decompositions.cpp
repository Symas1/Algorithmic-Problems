// generate palindromic decompositions
#include <string>
#include <vector>
#include <assert.h>
#include <iostream>
#include <random>
using namespace std;

void palindromic_decomp_helper(const string& str, int start,vector<string>&curr, vector<vector<string>>&res);
bool is_palindromic(const string & str, int start, int end);
vector<vector<string>> palindromic_decomp(const string& str)
{
	vector<vector<string>>res{};
	vector<string>curr{};
	palindromic_decomp_helper(str, 0, curr, res);
	return res;
}
void palindromic_decomp_helper(const string& str, int start, vector<string>&curr,vector<vector<string>>&res)
{
	if (start == str.size())
	{
		res.emplace_back(curr);
	}
	else
	{
		for (int i = start; i < str.size(); ++i)
		{
			if (is_palindromic(str,start, i))
			{
				curr.emplace_back(str.substr(start, i-start+1));
				palindromic_decomp_helper(str, i+1, curr, res);
				curr.pop_back();
			}
		}
	}
} // worst-time O(n*2^(n-1)); space worst(n*2^(n-1)) + n for recursion n - string length
bool is_palindromic(const string & str,int start,int end)
{
	for (; start < end; ++start, --end)
	{
		if (str[start] != str[end])return false;
	}
	return true;
}

void check(const vector<vector<string>>&arr)
{
	for (const auto& row : arr)
	{
		for(const auto& col:row)
		{
			assert(is_palindromic(col, 0, col.size() - 1));
		}
	}
}

string rand_str(const int size)
{
	mt19937 mt{ random_device{}() };
	string res( size,{} );
	for (int i = 0; i < size; ++i)
	{
		res[i] = uniform_int_distribution<int>{ 0,9 }(mt)+'0';
	}
	return res;
}

void main()
{
	auto res = palindromic_decomp("0204451881");
	check(res);
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 100; ++i)
	{
		auto str = rand_str(uniform_int_distribution<>{1, 10}(mt));
		auto res2 = palindromic_decomp(str);
		check(res2);
	}
	system("pause");
}