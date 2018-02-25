// replace and remove
#include <string>
#include <iostream>
#include <assert.h>
#include <random>
#include <algorithm>
#include <vector>
#include <iterator>
#include <numeric>
using namespace std;

void replace_and_remove(string& s, int size)
{
	int write_ind = 0;
	int a_cnt = 0;
	for (int i = 0; i < size; ++i)
	{
		if (s[i] != 'b')
		{
			s[write_ind++] = s[i];
		}
		if (s[i] == 'a')
		{
			++a_cnt;
		}
	}

	int res_index = write_ind + a_cnt - 1;
	for (int i = write_ind - 1; i >= 0; --i)
	{
		if (s[i] == 'a')
		{
			s[res_index--] = 'd';
			s[res_index--] = 'd';
		}
		else
		{
			s[res_index--] = s[i];
		}
	}
	s = {
		s.begin(),s.begin() + write_ind + a_cnt
	};
} // time O(n) space O(1)

string generate_sring(int size)
{
	mt19937 mt{ random_device{}() };
	uniform_int_distribution<>dist{ 'a','c' };
	string res(size << 1, '\0');
	for (int i = 0; i < size; ++i)
	{
		res[i] = dist(mt);
	}
	return res;
}

string replace_and_remove_test(const string& s)
{
	string res{};
	for (int i = 0; i < s.size() && s[i] != '\0'; ++i)
	{
		if (s[i] == 'a')
		{
			res.insert(res.end(), { 'd','d' });
		}
		else if (s[i] != 'b')
		{
			res.push_back(s[i]);
		}
	}
	return res;
}

void telex_encoding(string& s, int valid)
{
	int size = 0;
	for (int i = 0; i < valid; ++i)
	{
		if (!ispunct(s[i]))++size;
		else if (s[i] == ',')size += 5;
		else if (s[i] == '.')size += 3;
	}
	int write_index = size - 1;
	for (int i = valid - 1; i >= 0; --i)
	{
		if (!ispunct(s[i]))
		{
			s[write_index--] = s[i];
		}
		else if (s[i] == ',')
		{
			s[write_index--] = 'A';
			s[write_index--] = 'M';
			s[write_index--] = 'M';
			s[write_index--] = 'O';
			s[write_index--] = 'C';
		}
		else if (s[i] == '.')
		{
			s[write_index--] = 'T';
			s[write_index--] = 'O';
			s[write_index--] = 'D';
		}
	}
}

void my_sort(vector<int>&a, const vector<int>&b,int valid_size)
{
	int a_pointer = valid_size - 1;
	int b_pointer = b.size() - 1;
	int index = a.size() - 1;
	while(a_pointer>=0&&b_pointer>=0)
	{
		if (b[b_pointer] > a[a_pointer])a[index--] = b[b_pointer--];
		else a[index--] = a[a_pointer--];
	}

	if (b_pointer)
	{
		while (b_pointer>=0)
		{
			a[index--] = b[b_pointer--];
		}
	}
} // time O(n+m) space O(1)

vector<int> generate_vector(int size)
{
	mt19937 mt{ random_device{}() };
	uniform_int_distribution<int>dist{ numeric_limits<int>::min(),numeric_limits<int>::max() };
	vector<int>res(size);
	generate(res.begin(), res.end(), [&dist,&mt]() {return dist(mt); });
	sort(res.begin(), res.end());
	return res;
}

void test();
void test_telex();
void test_sort();

void main()
{
	test();
	test_telex();
	test_sort();
	system("pause");
}

void test()
{
	mt19937 mt{ random_device{}() };
	uniform_int_distribution<int>dist{ 1,1000 };
	for (int i = 0; i < 100; ++i)
	{
		int size = dist(mt);
		auto s = generate_sring(size);
		auto test = ::replace_and_remove_test(s);
		replace_and_remove(s, size);
		assert(test == s);
	}
}

void test_telex()
{
	string s{ "a.b,c,k.,," };
	s.resize(s.size() * 5);
	telex_encoding(s, 10);
	cout << s << endl;
}

void test_sort()
{
	mt19937 mt{ random_device{}() };
	uniform_int_distribution<int>dist{ 1,1000 };
	for (int i = 0; i < 1000; ++i)
	{
		auto a = generate_vector(dist(mt));
		auto b = generate_vector(dist(mt));
		int valid = a.size();
		a.resize(a.size() + b.size());
		my_sort(a, b, valid);
		assert(is_sorted(a.begin(), a.end()));
	}
}