#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <string>
using namespace std;

vector<int> multi(vector<int>& a, vector<int>& b)
{
	const int sign = (a.front() < 0) ^ (b.front() < 0) ? -1 : 1;
	a.front() = abs(a.front()), b.front() = abs(b.front());

	vector<int>result(a.size() + b.size(), 0);
	for (int i = a.size() - 1; i >= 0; --i)
	{
		for (int j = b.size() - 1; j >= 0; --j)
		{
			result[i + j + 1] += a[i] * b[j];
			result[i + j] += result[i + j + 1] / 10;
			result[i + j + 1] %= 10;
		}
	}

	//Remove leading zeros
	result = {
		find_if_not(result.begin(),result.end(),[](int a) {return a == 0; }),
		result.end()
	};
	if (result.empty())return{ 0 };

	result.front() *= sign;
	return result;
} // O(nm)

void main()
{
	vector<int>a;
	vector<int>b;
	vector<int>res;
	{
		a.insert(a.begin(), { 1, 2, 3 });
		b.insert(b.begin(), { 9, 8, 7 });
		res = multi(a, b);
		assert(res[0] == 1 && res[1] == 2 && res[2] == 1 && res[3] == 4 && res[4] == 0 && res[5] == 1);
		a.clear();
		b.clear();
	}

	{
		a.insert(a.begin(), { -1, 1, 2,1,3,5,1 });
		b.insert(b.begin(), { 3,1,4,5,2,1 });
		res = multi(a, b);
		assert(res[0] == -3 && res[1] == 5 && res[2] == 2 && res[3] == 6 && res[4] == 8 && res[5] == 8
			&& res[6] == 4 && res[7] == 3 && res[8] == 7 && res[9] == 8 && res[10] == 7 && res[11] == 1);
		a.clear();
		b.clear();
	}
}