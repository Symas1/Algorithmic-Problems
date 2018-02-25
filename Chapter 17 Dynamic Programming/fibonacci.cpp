// compute fibonacci number
#include <iostream>
using namespace std;

unsigned fibonacci(size_t n)
{
	if (n <= 1) {
		return n;
	}

	int f_minus2 = 0;
	int f_minus1 = 1;
	for (int i = 2; i <= n; ++i)
	{
		auto f = f_minus1 + f_minus2;
		f_minus2 = f_minus1;
		f_minus1 = f;
	}
	return f_minus1;
} // time O(n); space O(1)

void main()
{
	for (int i = 0; i < 10; ++i)
	{
		cout << fibonacci(i) << "  ";
	}
	system("pause");
}