// permutate array
#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;

void permutation(vector<int>& a, vector<int>& perm)
{
	for (int i = 0; i < a.size(); ++i)
	{
		int next = i;
		while (perm[next] >=0)
		{
			swap(a[i], a[perm[next]]);
			int temp = perm[next];
			perm[next] -= perm.size();
			next = temp;
		}
	}

	for_each(perm.begin(), perm.end(), [&perm](int& x) {x += perm.size(); });
} // time O(n), space O(1)

void inverse_perm(vector<int>& a)
{
	for (int i = 0; i < a.size(); ++i)
	{
		int next = i;
		while (next>=0&&a[next] >= 0)
		{
			int temp = a[next];
			swap(a[i], a[a[next]]);
			a[temp] -= a.size();
			next = a[i];
		}
	}

	for_each(a.begin(), a.end(), [&a](int&x) {x += a.size(); });
} // O(n), O(1)

void main()
{
	vector<int>arr{ 0,1,2,3 };
	vector<int>perm{ 2,3,1,0 };
	permutation(arr, perm);
	for (int i = 0; i < arr.size(); ++i)
	{
		cout << arr[i] << " ";
		if (i == arr.size() - 1) cout << endl;
	}
	for (auto x : perm)
	{
		cout << x << " ";
	}
	cout << endl;

	inverse_perm(arr);
	for (int i = 0; i < arr.size(); ++i)
	{
		cout << arr[i] << " ";
		if (i == arr.size() - 1) cout << endl;
	}
	system("pause");
}