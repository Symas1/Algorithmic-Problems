#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

vector<int> factorial(int n)
{
	if (n == 0 || n == 1)return{ 1 };

	vector<int>res{ 1 };
	for (int i = 2; i <= n; ++i)
	{
		int buf = 0;
		for (int j = 0; j < res.size(); ++j)
		{
			res[j] = res[j] * i + buf;
			buf = res[j] / 10;
			res[j] %= 10;
		}

		if (buf)
		{
			int digits = floor(log10(buf)) + 1;
			vector<int>buff(digits, 0);

			for (int i = 0; i < digits; ++i)
			{
				buff[i] = buf % 10;
				buf /= 10;
			}
			res.insert(res.end(), buff.begin(), buff.end());
		}
	}

	return res;
} // O(nlog10(n!))

void main()
{
	auto res = factorial(1492);
	copy(res.rbegin(), res.rend(), ostream_iterator<int>{ cout});
	cout << endl;
	int ress = 0;
	int n = 1492;
	while (n>=5)
	{
		ress += n / 5;
		n /= 5;
	}
	cout << res.size() << endl;
	cout << ress << endl;
	cout << find_if_not(res.begin(), res.end(), [](int i) {return i == 0; }) - res.begin() << endl; // vector reversed !
	system("pause");
}