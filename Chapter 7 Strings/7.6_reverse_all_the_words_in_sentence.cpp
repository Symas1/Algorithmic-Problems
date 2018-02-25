// reverse all the word in a sentence
#include <string>
#include <iostream>
#include <iterator>
#include <random>
#include <assert.h>
using namespace std;

void rev(string& s)
{
	reverse(s.begin(), s.end());
	size_t start = 0, end;
	while ((end = s.find(" ", start))!=string::npos)
	{
		reverse(s.begin() + start, s.begin() + end);
		start = end+1;
	}
	reverse(s.begin() + start, s.end());
} // time O(n), space O(1)

string generate_string()
{
	mt19937 mt{ random_device{}() };
	uniform_int_distribution<int>dist{ 0,52 };
	string s(dist(mt), '\0');
	mt.seed(random_device{}());
	for (int i = 0; i < s.size(); ++i)
	{
		int ch = dist(mt);
		if (ch == 52) {
			s[i] = ' ';
		}
		else if (ch < 26) {
			s[i]= ch + 'a';
		}
		else {
			s[i]= ch - 26 + 'A';
		}
	}
	return s;
}
void main()
{
	for (int i = 0; i < 1000; ++i)
	{
		auto str = generate_string();
		auto copy = str;
		rev(copy);
		rev(copy);
		assert(copy == str);
	}
	system("pause");
}