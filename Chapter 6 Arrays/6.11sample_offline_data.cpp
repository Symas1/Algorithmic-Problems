// random subset
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

void subset(vector<int>& arr,int size)
{
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < size; ++i)
	{
		uniform_int_distribution<int> dist{ i,static_cast<int>(arr.size() - 1) };
		int index = dist(mt);
		swap(arr[i], arr[index]);
	}
} // time O(k), space O(1) optimization (if size > arr.size()/2, then choose elements randomly and exclude them)

void main()
{
	const int sub = 5;
	vector<int> arr{ 1,2,3,4,5,6,7,8,9,10 };
	subset(arr,sub);
	for (int i=0;i<sub;++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	system("pause");
}