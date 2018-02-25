// Normalize pathnames
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <assert.h>
using namespace std;

string pathname(const string& str)
{
	if (str.empty())throw invalid_argument("Empty string is not a valid path");

	vector<string>stack{};
	if (str.front() == '/')stack.emplace_back("/");
	stringstream ss{ str };
	string token{};
	while (getline(ss, token, '/'))
	{
		if (token == "..")
		{
			if (stack.empty() || stack.back() == "..")
			{
				stack.emplace_back(token);
			}
			else
			{
				if (stack.back() == "/")throw invalid_argument("Path error");
				stack.pop_back();
			}
		}
		else if (token != "." && token != "")
		{
			stack.emplace_back(token);
		}
	}

	string res{};
	if (!stack.empty())
	{
		res = stack.front();
		for (int i = 1; i < stack.size(); ++i)
		{
			if (i == 1 && res == "/")
			{
				res += stack[i];
			}
			else res += "/" + stack[i];
		}
	}
	return res;
} // time O(n) space O(n)

void main()
{
	assert(pathname("123/456") == string("123/456"));
	assert(pathname("/123/456") == string("/123/456"));
	assert(pathname("usr/lib/../bin/gcc") ==
		string("usr/bin/gcc"));
	assert(pathname("./../") == string(".."));
	assert(pathname("../../local") == string("../../local"));
	assert(pathname("./.././../local") == string("../../local"));
	assert(pathname("/foo/../foo/./../") == string("/"));
	try {
		pathname("/foo.txt");
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
	try {
		pathname("");
		assert(false);
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
	try {
		pathname("/..");
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
	try {
		pathname("/cpp_name/bin/");
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
	assert(pathname("scripts//./../scripts/awkscripts/././") ==
		string("scripts/awkscripts"));
	system("pause");
}