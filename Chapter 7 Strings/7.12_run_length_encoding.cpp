// implement run-length encoding
#include <string>
#include <iostream>
#include <assert.h>
using namespace std;

string encode(const string& str)
{
	string res{};
	size_t start = 0, end;
	while ((end = str.find_first_not_of(str[start],start+1)) != string::npos)
	{
		res.push_back(end - start + '0');
		res.push_back(str[start]);
		start = end;
	}
	res.push_back(str.size() - start+'0');
	res.push_back(str[start]);

	return res;
} // time O(n), space O(n)

string decode(const string& str)
{
	string res{};
	int decimal = 0;
	for (int i = 0; i < str.size();++i)
	{
		while (isdigit(str[i]))decimal = decimal * 10 + (str[i++] - '0');
		res.append(decimal,str[i]);
		decimal = 0;
	}
	return res;
} // time O(n), space O(n)

void main()
{
	assert(encode("aaaabccaa") == "4a1b2c2a");
	assert(decode("4a1b2c2a") == "aaaabccaa");
	system("pause");
}