// wirte a string sinusoidally
#include <string>
#include <vector>
#include <iostream>
using namespace std;

void sin_helper(const string&str, string& res, int start, int period);
string sin(const string& str)
{
	string res{};
	sin_helper(str, res, 1, 4);
	sin_helper(str, res, 0, 2);
	sin_helper(str, res, 3, 4);
	return res;
} // time O(n) space O(n)

void sin_helper(const string&str, string& res, int start, int period)
{
	for (; start < str.size(); start += period)
	{
		res.push_back(str[start]);
	}
}

void main()
{
	string str{ "Hello World!" };
	string sin = ::sin(str);
	cout << str << endl << sin << endl;
	system("pause");
}