// compute a random permutation
#include <vector>
#include <random>
#include <iostream>
#include <numeric>
#include <iterator>
#include <algorithm>
using namespace std;

vector<int> perm(int n)
{
	vector<int>a(n);
	iota(a.begin(), a.end(), 0);

	mt19937 mt{ random_device{}() };
	for (int i = 0; i < a.size(); ++i)
	{
		uniform_int_distribution<int>dist{ i,static_cast<int>(a.size() - 1) };
		swap(a[i],a[dist(mt)]);
	}
	return a;
} // time O(n)

void main()
{
	mt19937 mt{ random_device{}() };
	uniform_int_distribution<int>dist{ 0,30 };
	for (int i = 0; i < 100; ++i)
	{
		auto res = perm(dist(mt));
		copy(res.begin(), res.end(), ostream_iterator<int>{cout, " "});
		cout << endl;
	}
	system("pause");
}