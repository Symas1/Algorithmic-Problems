// team photo day - 1
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
using namespace std;

bool possible(vector<int>&team1, vector<int>&team2)
{
	sort(team1.begin(), team1.end());
	sort(team2.begin(), team2.end());
	bool team1_first_row;
	if (team1.back() > team2.back())
		team1_first_row = true;
	else if(team1.back() < team2.back())
		team1_first_row = false;
	else return false;

	for (int i = team1.size() - 2; i >= 0; --i)
	{
		if (team1_first_row && (team1[i] < team2[i] || team1[i]== team2[i]))return false;
		else if (!team1_first_row && (team1[i] > team2[i] || team1[i] == team2[i]))return false;
	}
	return true;
} // time O(nlogn); space O(1)

void main()
{
	vector<int>first{ 1,5,4 };
	vector<int>second{ 2,3,4 };
	assert(!possible(first, second));

	first = { 3,5,4 };
	second = { 2,3,4 };
	assert(possible(first, second));

	first = { 1,5,4 };
	second = { 1,3,4 };
	assert(!possible(first, second));
	system("pause");
}