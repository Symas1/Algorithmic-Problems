// evaluate RPN expression
#include <string>
#include <stack>
#include <iostream>
#include <assert.h>
#include <sstream>
using namespace std;

int rpn(const string& str)
{
	stack<int>numbers{};
	stringstream ss{ str };
	string read;
	while(getline(ss,read,','))
	{
		if(read=="+"|| read == "-" || read == "*" || read == "/")
		{
			int second = numbers.top();
			numbers.pop();
			int first = numbers.top();
			numbers.pop();
			switch (read.front())
			{
			case '+':
				numbers.emplace(first + second);
				break;
			case '-':
				numbers.emplace(first - second);
				break;
			case '*':
				numbers.emplace(first * second);
				break;
			case '/':
				numbers.emplace(first / second);
				break;
			}
		}
		else numbers.emplace(stoi(read));
	}
	return numbers.top();
} // time O(n) space O(n)

int pn(const string& str)
{
	stack<int>numbers;
	stringstream ss{ string{str.rbegin(),str.rend()} };
	string read;
	while (getline(ss, read, ','))
	{
		reverse(read.begin(), read.end());

		if (read == "+" || read == "-" || read == "*" || read == "/")
		{
			int first = numbers.top();
			numbers.pop();
			int second = numbers.top();
			numbers.pop();
			switch (read.front())
			{
			case '+':
				numbers.emplace(first + second);
				break;
			case '-':
				numbers.emplace(first - second);
				break;
			case '*':
				numbers.emplace(first * second);
				break;
			case '/':
				numbers.emplace(first / second);
				break;
			}
		}
		else numbers.emplace(stoi(read));
	}
	return numbers.top();
} // time O(n) space O(n)

void main()
{
	assert(0 == rpn("2,-10,/"));
	assert(-5 == rpn("-10,2,/"));
	assert(5 == rpn("-10,-2,/"));
	assert(-5 == rpn("5,10,-"));
	assert(6 == rpn("-10,-16,-"));
	assert(12 == rpn("10,2,+"));
	assert(15 == rpn("1,2,+,3,4,*,+"));
	assert(42 == rpn("1,2,3,4,5,+,*,+,+,3,4,*,+"));
	assert(-6 == rpn("1,2,3,4,5,+,*,+,+,3,4,*,+,-7,/"));

	assert(pn("-,*,/,15,-,7,+,1,1,3,+,2,+,1,1") == 5);
	assert(pn("/,10,5") == 2);
	system("pause");
}