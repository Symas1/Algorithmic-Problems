// double x^y
#include <iostream>
#include <random>
#include <assert.h>
using namespace std;

int compare(double a, double b)// 0 means equal, -1 means smaller, and 1 means larger.
{
	double diff = (a - b) / b; // Uses normalization for precision problem.
	return diff<-1.0e-9 ? -1 : diff>1.0e-9;
}

double power(double x, int y)
{
	double res = 1.0;
	if (y < 0)
	{
		x = 1.0 / x;
		y = -y;
	}

	while (y)
	{
		if (y & 1)
		{
			res *= x;
		}
		x *= x;
		y >>= 1;
	}
	return res;
} // O(n)

void main(int argc,char** argv)
{
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<double> dist{ 0.0,10.0 };
	uniform_int_distribution<int> int_dis{ -32,32 };
	for (int i = 0; i < 1000; ++i)
	{
		auto first = dist(mt);
		int second = int_dis(mt);
		assert(!compare(power(first, second), pow(first, second)));
	}
	system("pause");
}