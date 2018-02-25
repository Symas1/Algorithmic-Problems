// test brackets for well-formedness
#include <stack>
#include <string>
#include <iostream>
#include <assert.h>
#include <unordered_map>
using namespace std;

bool brackets(const string& str)
{
	stack<char>brackets{};
	const unordered_map<char, char>map{ {'(',')'},{ '[',']' } ,{ '{','}' } };
	for (int i = 0; i < str.size(); ++i)
	{
		if (map.count(str[i]))
		{
			brackets.emplace(str[i]);
		}
		else
		{
			if (brackets.empty() || map.at(brackets.top()) != str[i])return false;
			brackets.pop();
		}
	}
	return brackets.empty();
} // time O(n) space O(n)

void main()
{
	assert(brackets("()[]{}"));
	assert(brackets("[({}){([])(()())}]"));
	assert(!brackets("((){}[{()}]]"));
	assert(!brackets("]"));
	system("pause");
}