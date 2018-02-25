//reverse digits
#include <algorithm>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <random>
#include <numeric>
using namespace std;

int reverse_my(int x)
{
	int res = 0;
	int remaining = abs(x);
	while (remaining)
	{
		res = res * 10 + remaining % 10;
		remaining /= 10;
	}
	return x < 0 ? -res : res;
} // O(n)

int check(int x)
{
	string str = to_string(x);
	if (str.front() == '-') reverse(str.begin()+1,str.end());
	else reverse(str.begin(), str.end());
	return stoi(str);
}

void main()
{
	mt19937 mt((random_device())());
	uniform_int_distribution<int>dist(numeric_limits<short>::min(), numeric_limits<short>::max());
	for (int i = 0; i < 1000; ++i)
	{
		auto r = dist(mt);
		assert(reverse_my(r) == check(r));
	}
	system("pause");
}