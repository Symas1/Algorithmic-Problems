//Suppose you were asked to write a program which takes an array of positive
//integers and returns the smallest number which is not to the sum of a subset of
//elements of the array.

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int count(const vector<int>&v);

void main()
{
	vector<int>a{ 12,2,1,15,2,4,10 };
	//vector<int>a{ 1,2};
	for (auto& x : a)
	{
		cout << x << " ";
	}
	cout << endl;

	sort(a.begin(), a.end());

	for (auto& x : a)
	{
		cout << x << " ";
	}
	cout << endl;

	cout << count(a) << endl;

	system("pause");
}

int count(const vector<int>&v)
{
	int save = 0;
	for (int i = 0; i < v.size(); ++i)
	{
		if ((save + 1) >= v[i])
		{
			save += v[i];
		}
		else
		{
			break;
		}
	}
	return save+1;
}