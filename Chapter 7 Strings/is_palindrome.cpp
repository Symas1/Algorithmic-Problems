#include <string>
#include <vector>
#include <assert.h>
using namespace std;

bool is_p(const string& s)
{
	for (int i = 0,j=s.size()-1;i<j; ++i,--j)
	{
		if (s[i] != s[j])return false;
	}
	return true;
}

void main()
{
	assert(is_p("121"));
	assert(!is_p("123"));
	assert(is_p("111"));
	assert(!is_p("1234"));
	assert(is_p("1234321"));
	system("pause");
}