// remove first-name duplicates
#include <vector>
#include <assert.h>
#include <iostream>
#include <utility>
#include <algorithm>
#include <string>
using namespace std;

void compute(vector < pair<string, string>>&arr)
{
	sort(arr.begin(), arr.end(), [](const pair<string, string>&first, const pair<string, string>&second) {return first.first < second.first; });
	int valid = 1;
	for (int i = 1; i < arr.size(); ++i)
	{
		if (arr[i].first != arr[i - 1].first)
		{
			arr[valid++] = arr[i];
		}
	}
	arr.erase(arr.begin()+valid,arr.end());
} // time O(nlogn); space O(n) also possible solution with hash table time O(n); space O(n)

void main()
{
	vector<pair<string, string>>arr{ {"Ian","Bell"},{ "Ian","Bel" },{ "Ian","Be" } ,{"A","Bell"},{ "A","Bell" }, {"An","Bell"} };
	compute(arr);
	for (const auto&x:arr)
	{
		cout << x.first << " " << x.second << endl;
	}
	system("pause");
}