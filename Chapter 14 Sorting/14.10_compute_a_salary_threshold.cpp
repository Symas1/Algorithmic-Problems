// compute a salary threshold
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <random>
#include <iterator>
#include <numeric>
using namespace std;

double cap(vector<double>salaries, double payroll)
{
	sort(salaries.begin(), salaries.end());
	double current_sum = 0;
	for (int i = 0; i < salaries.size(); ++i)
	{
		int people = salaries.size() - i;
		double needed_money = people * salaries[i];
		if (payroll <= needed_money + current_sum)
		{
			return (payroll - current_sum) / people;
		}
		current_sum += salaries[i];
	}
	return -1;
} // time O(nlogn); space O(n)

double cap_variant(vector<double>arr, double payroll)
{
	return{};
}

void small_test()
{
	vector<double>arr{ 20,30,40,90,100 };
	double p = 210;
	assert(cap(arr, p) == 60);
	p = 280;
	assert(cap(arr,p) == 100);
	p = 50;
	assert(cap(arr, p) == 10);
	p = 281;
	assert(cap(arr, p) == -1);
}

void main(int argc,char* argv[])
{
	small_test();

	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 100; ++times)
	{
		vector<double>arr{};
		int size = uniform_int_distribution<>{ 1,1000 }(mt);
		generate_n(back_inserter(arr), size, [&mt]() {return uniform_real_distribution<>{0, 9999}(mt); });
		auto payroll = uniform_real_distribution<>{ 0,99999 }(mt);
		auto res = cap(arr, payroll);
		if (res != -1)
		{
			for (int i = 0; i < arr.size(); ++i)
			{
				if (arr[i] < res)payroll -= arr[i];
				else payroll -= res;
			}
			assert(payroll < 1.0e-8);
		}
	}
	system("pause");
}