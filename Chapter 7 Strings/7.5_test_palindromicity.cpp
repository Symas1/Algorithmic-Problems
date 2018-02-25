// test palindromicity
#include <string>
#include <iostream>
#include <assert.h>
using namespace std;

bool check(const string& s)
{
	int i = 0, j = s.size() - 1;
	while (i < j)
	{
		while (!isalnum(s[i]) && i < j)++i;
		while (!isalnum(s[j]) && i < j)--j;
		
		if (i < j)
		{
				if (tolower(s[i++]) != tolower(s[j--]))return false;
		}
	}
	return true;
} // time O(n), space O(1)

void main()
{
	assert(check("A man, a plan, a canal, Panama.") == true);
	assert(check("Able was I, ere I saw Elba!") == true);
	assert(check("Ray a Ray") == false);
	assert(check("") == true);
	assert(check("No, it can assess an action.")==true);
	assert(check("Noel saw I was Leon.") == true);
	system("pause");
}