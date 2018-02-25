// first occurrence of substring
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <random>
#include <assert.h>
#include <unordered_map>
using namespace std;

vector<int> prefix(const string& str)
{
	vector<int>res(str.size());
	res[0] = 0;
	for (int i = 1,state=0; i < res.size(); ++i)
	{
		while (state > 0 && (str[state] != str[i]))state=res[state-1];
		if (str[state] == str[i])++state;
		res[i] = state;
	}
	return res;
} // time O(m), space O(m) m - pattern size

unsigned kmp(const string& str, const string& search)
{
	vector<int>pre = prefix(search);
	for (int i = 0, com = 0; i < str.size(); ++i)
	{
		while ((com > 0) && (str[i] != search[com]))com = pre[com - 1];

		if (str[i] == search[com])++com;

		if (com == search.size())return i + 1 - com;
	}
	return string::npos;
} // time O(n+m) n - string size, m - pattern size, space O(m)

unsigned rabin_karp(const string& str, const string& sub) // good for finding many patterns (detecting plagiarism)
{
	int base = 101;
	int str_hash = 0, sub_hash = 0;
	int sub_power = 1;
	for (int i = 0; i < sub.size(); ++i)
	{
		sub_power = i ? sub_power*base : 1;
		str_hash = str_hash*base + str[i];
		sub_hash = sub_hash*base + sub[i];
	}

	for (int i = sub.size(); i < str.size(); ++i)
	{
		if (str_hash == sub_hash && !str.compare(i - sub.size(), sub.size(), sub))
			return i - sub.size();
		str_hash -= str[i - sub.size()] * sub_power;
		str_hash = str_hash*base + str[i];
	}

	if (str_hash == sub_hash && !str.compare(str.size()-sub.size(), sub.size(), sub))
		return str.size() - sub.size();

	return string::npos;
} // For text of length n and p patterns of combined length m, its average and best case running time is O(n+m) in space O(p) for map, but its worst-case time is O(nm)(bad hash)

unsigned brute_force(const string& str, const string& sub)
{
	for (int i = 0; i < str.size()-sub.size()+1; ++i)
	{
		for (int j = 0; j < sub.size(); ++j)
		{
			if (sub[j] != str[i + j])break;
			if (j + 1 == sub.size())return i;
		}
	}
	return string::npos;
} // worst time O(nm), best time O(n+m), average O(n), space O(1), n - string size, m - pattern size

unordered_map<char, unsigned> bad_char(const string& str)
{
	unordered_map<char, unsigned>res{};
	for (int i = 0; i < str.size(); ++i)
	{
		res[str[i]] = i;
	}
	return res;
}

vector<int> pre1(const string& str)
{
	vector<int>f(str.size()+1);
	vector<int>s(str.size()+1, 0);
	int i = str.size(), j = str.size() + 1;
	f[i] = j;
	while (i > 0)
	{
		while (j <= str.size() && str[i - 1] != str[j - 1])
		{
			if (s[j] == 0)s[j] = j - i;
			j = f[j];
		}
		--i; --j;
		f[i] = j;
	}

	j = f[0];
	for (i = 0; i <= str.size(); ++i)
	{
		if (s[i] == 0)s[i] = j;
		if (i == j)j = f[j];
	}
	return s;
}


unsigned boyer_moore(const string& str, const string& sub)
{
	auto bad_charr = ::bad_char(sub);
	auto suffix = pre1(sub);

	for (int s = 0; s <= (str.size() - sub.size());)
	{
		int j = sub.size() - 1;
		while (j >= 0 && sub[j] == str[s + j])--j;

		if (j < 0)return s;
		else
		{
			if (bad_charr.find(str[s + j]) != bad_charr.end())s += max(suffix[j+1], static_cast<int> (j - bad_charr[str[s + j]]));
			else s += max(suffix[j+1], j - (-1));
		}
	}
	return string::npos;
} // time worst case O(n*m)(a^n&&a^m) can improve to O(n+m) best case O(n/m), space O(m), n - str size, m - search size
// http://www.inf.fh-flensburg.de/lang/algorithmen/pattern/bmen.htm

string gen_str(int size)
{
	string res(size,'\0');
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < size; ++i)
	{
		res[i] = uniform_int_distribution<>{ 'a','z' }(mt);
	}
	return res;
}

void main()
{
	assert(brute_force("abxabcabcaby", "abcaby") == 6);
	assert(rabin_karp("abxabcabcaby", "abcaby") == 6);
	assert(kmp("abxabcabcaby", "abcaby") == 6);
	assert(boyer_moore("abxabcabcaby", "abcaby") == 6);
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 10000; ++i)
	{
		int first_size = uniform_int_distribution<int>{ 20,100 }(mt);
		int second_size = uniform_int_distribution<int>{ 1,static_cast<int>(sqrt(first_size)) }(mt);
		auto first = gen_str(first_size);
		auto second = gen_str(second_size);
		auto res = first.find(second);
		assert(brute_force(first, second)== res);
		assert(rabin_karp(first, second)== res);
		assert(kmp(first,second) == res);
		assert(boyer_moore(first, second) == res);
	}
	system("pause");
}