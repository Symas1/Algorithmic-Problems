//B[0] <= B[l] => B[2] <= B[3] => B[4] <= B[5]...

#include <vector>
#include <iostream>
using namespace std;


void rearrange(vector<int>&v)
{
	for (int i = 1; i < v.size(); ++i)
	{
		if (
			(i % 2 == 0 && v[i - 1] < v[i]) ||
			(i % 2 != 0 && v[i - 1] > v[i])
			)
		{
			swap(v[i - 1], v[i]);
		}
	}
}

void main()
{
	vector<int>a{ 1,2,3,4,5,6,7,8,9 };
	rearrange(a);

	for (auto& x : a)
	{
		cout << x << " ";
	}
	cout << endl;
	system("pause");
}