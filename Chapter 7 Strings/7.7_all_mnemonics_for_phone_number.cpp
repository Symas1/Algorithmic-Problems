// compute all mnemonics for a phone number
#include <string>
#include <vector>
#include <iostream>
#include <array>
#include <assert.h>
#include <algorithm>
#include <random>
using namespace std;

void mnemonics_helper(const string& s, string& partial, vector<string>&res, int depth);
const array<string, 10> chars{ { "0", "1", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ" } };
vector<string> mnemonics(const string& s)
{
	string partial(s.size(), ' ');
	vector<string>res{};
	mnemonics_helper(s, partial, res, 0);
	return res;
} // time O(n*4^(n)) space O(n*4^n)

void mnemonics_helper(const string& s, string& partial, vector<string>&res, int depth)
{
	if (depth == s.size())
	{
		res.emplace_back(partial);
	}
	else
	{
		int digit = s[depth] - '0';
		for (int i = 0; i < chars[digit].size(); ++i)
		{
			partial[depth] = chars[digit][i];
			mnemonics_helper(s, partial, res, depth + 1);
		}
	}
} // time O(n*4^(n)) space O(n*4^n)

vector<string>mnemonics_iter(const string&s)
{
	int size = 1;
	for (int i = 0; i < s.size(); ++i)
	{
		size = size*(chars[s[i] - '0'].size());
	} // find size of result vector
	vector<string>res(size, string(s.size(), ' '));
	for (int i = 0, step = res.size() / chars[s[i] - '0'].size(); i < s.size(); ++i, step /= chars[s[i] - '0'].size())
	{
		int number = s[i] - '0';
		int digits = chars[number].size();
		for (int j = 0, index = 0; j < digits; ++j)
		{
			for (int u = 0; u < res.size() / digits; ++u)
			{
				res[index++][i] = chars[number][j];
				if ((u + 1) % step == 0) index += step*(digits - 1);
			}
			index = step*(j + 1);
		}
		if (i == s.size() - 1)break;
	}
	return res;
} // time O(n*4^n+n)

string gen_num()
{
	mt19937 mt{ random_device{}() };
	uniform_int_distribution<int>size{ 7,10 };
	string res(size(mt), ' ');
	mt.seed(random_device{}());
	uniform_int_distribution<int>num{ 2,9 };
	for (int i = 0; i < res.size(); ++i)
	{
		res[i] = num(mt) + '0';
	}
	return res;
}

void main()
{
	for (int i = 0; i < 5; ++i)
	{
		string str = gen_num();
		auto recursive = mnemonics(str);
		auto iterative = mnemonics_iter(str);
		sort(recursive.begin(), recursive.end());
		sort(iterative.begin(), iterative.end());
		assert(equal(recursive.begin(), recursive.end(), iterative.begin(), iterative.end()));
	}
	system("pause");
}