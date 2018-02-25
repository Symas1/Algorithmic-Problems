// enumerate all primes to n
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> prime(int n)
{
	vector<bool>c(n + 1, true);
	vector<int>res{};
	for (int i = 2; i < c.size(); ++i)
	{
		if (c[i])
		{
			res.emplace_back(i);
			for (int j = 2; static_cast<long long>(j*i) <= n; ++j)
			{
				c[j*i] = false;
			}
		}
	}
	return res;
} // time O(nloglogn), space O(n)

vector<int> prime_opt(int n)
{
	const int size = floor(0.5*(n - 3)) + 1;
	vector<int>res{ 2 };

	vector<bool>is_prime(size, true);//2i+3 shows

	for (int i = 0; i < is_prime.size(); ++i)
	{
		if (is_prime[i] == true)
		{
			int new_elem = 2 * i + 3;
			res.emplace_back(new_elem);

			for (long j = 2 * ((long)i*(long)i) + 6 * i + 3; j < is_prime.size(); j += new_elem)
			{
				is_prime[j] = false;
			}
		}
	}
	return res;
} // time O(nloglogn), space O(n)

void main()
{
	auto a = prime_opt(100000);
	for (auto x : a)
	{
		cout << x << " ";
	}
	cout << endl;
	system("pause");
}