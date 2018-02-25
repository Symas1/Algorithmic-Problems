// look and say problem
#include <string>
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

string look(int n)
{
	string prev{ "1" };
	for (int i = 1; i < n; ++i)
	{
		string next{};
		size_t start=0, end;
		while ((end=prev.find_first_not_of(prev[start],start+1))!=string::npos)
		{
			next+=(to_string(end - start));
			next += prev[start];
			start = end;
		}
		next += (to_string(prev.size() - start));
		next += prev[start];
		prev = next;
	}
	return prev;
} // time O(n2^n) space O(2^n)

void main()
{
	assert(look(1) == "1");
	assert(look(2) == "11");
	assert(look(3) == "21");
	assert(look(4) == "1211");
	assert(look(5) == "111221");
	assert(look(6) == "312211");
	assert(look(7) == "13112221");
	system("pause");
}