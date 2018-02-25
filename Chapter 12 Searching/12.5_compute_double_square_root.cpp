// compute the real squre root
#include <iostream>
#include <assert.h>
#include <random>
#include <numeric>
#include <cmath>
#include <algorithm>
using namespace std;

int compare(const double a, const double b);
double sq(const double n)
{
	double low = n<1.0?n:1, up = n<1.0?1:n;
	while (compare(low,up))
	{
		double mid = low + (up - low) / 2;
		double power = mid*mid;
		if (power <= n)low = mid;
		else if (power > n)up = mid;
	}
	return low;
} // time O(log(x/s)) s - tolerance; space O(1)
int compare(const double a, const double b)
{
	double eps = 0.00001;
	double diff = fabs(a - b) / b;
	return diff <= eps ? 0 : 1;
}

int compare(const double a, const double b, const double eps);
double variant1(const double x, const double y, const double eps)
{
	assert(y != 0);
	bool sign = (x < 0) ^ (y < 0);
	double xx = fabs(x), yy = fabs(y);
	double low, up;
	if (yy < 1)
	{
		int count = 1;
		for (double fake = yy; fake < 1; ++count)fake *= 10;
		low = 0, up = pow(10,count);
	}
	else low = 0, up = max(xx,yy);
	while (compare(low, up, eps))
	{
		double mid = low + 0.5*(up - low);
		double power = yy*mid;
		if (power <= xx)low = mid;
		else if (power > xx)up = mid;
	}
	return sign?-low:low;
} // time O(log(n/s)) s - precision; space O(1)
int compare(const double a, const double b, const double eps)
{
	double diff = fabs(a - b) / b;
	return diff <= eps ? 0 : 1;
}

void test_sq();
void test_variant1();

int main(int argc, char* argv[])
{
	test_sq();
	test_variant1();
	system("pause");
	return 0;
}

void test_sq()
{
	mt19937 mt{ random_device{}() };
	uniform_real_distribution<double>dist{ 0, sqrt(numeric_limits<double>::max()) };
	for (int times = 0; times < 1000; ++times)
	{
		{
			double n = dist(mt);
			long double my_result = sq(n);
			long double result = sqrt(n);
			long double eps = fabs(my_result - result) / fabs(my_result);
			assert(eps <= 0.00001);
		}

		{
			double n = generate_canonical<double, numeric_limits<double>::digits>(mt);;
			long double my_result = sq(n);
			long double result = sqrt(n);
			long double eps = fabs(my_result - result) / fabs(my_result);
			assert(eps <= 0.00001);
		}
	}
}

void test_variant1()
{
	mt19937 mt{ random_device{}() };
	uniform_real_distribution<double>dist{ 1, numeric_limits<double>::max() };
	uniform_int_distribution<int>sign{ 0,1 };
	for (int times = 0; times < 2000; ++times)
	{
		const double precision = 0.0001;
		// both more than or equal to 1
		{
			double x = dist(mt);
			double y = dist(mt);
			x = sign(mt) ? -x : x;
			y = sign(mt) ? -y : y;
			double my_result = variant1(x,y,precision);
			double result = x/y;
			double eps = fabs(my_result - result) / fabs(my_result);
			assert(eps <= precision);
		}

		 // both less than 1
		{
			double x = generate_canonical<double,numeric_limits<double>::digits>(mt);
			double y = generate_canonical<double, numeric_limits<double>::digits>(mt);
			x = sign(mt) ? -x : x;
			y = sign(mt) ? -y : y;
			double my_result = variant1(x, y, precision);
			double result = x / y;
			double eps = fabs(my_result - result) / fabs(my_result);
			assert(eps <= precision);
		}

		// first less than 1, second bigger than 1
		{
			double x = generate_canonical<double, numeric_limits<double>::digits>(mt);
			double y = dist(mt);
			x = sign(mt) ? -x : x;
			y = sign(mt) ? -y : y;
			double my_result = variant1(x, y, precision);
			double result = x / y;
			double eps = fabs(my_result - result) / fabs(my_result);
			assert(eps <= precision);
		}

		//// first bigger than 1, second less than 1
		//{
		//	double x = dist(mt);
		//	double y = generate_canonical<double, numeric_limits<double>::digits>(mt);
		//	x = sign(mt) ? -x : x;
		//	y = sign(mt) ? -y : y;
		//	double my_result = variant1(x, y, precision);
		//	double result = x / y;
		//	double eps = fabs(my_result - result) / fabs(my_result);
		//	//assert(eps <= precision);
		//	cout << my_result << "\t" << result << endl;
		//}
	}
}