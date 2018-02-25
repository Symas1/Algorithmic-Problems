// sudoku checker

#include <vector>
#include <iostream>
#include <assert.h>
using namespace std;

bool check(const vector<vector<int>>& game)
{
	for (int i = 0; i < 9; ++i) // cols
	{
		vector<bool>seen(9, false);
		for (int j = 0; j < 9; ++j)
		{
			if (game[i][j] && !seen[game[i][j] - 1]) seen[game[i][j] - 1]=true;
			else if (game[i][j] && seen[game[i][j] - 1])return false;
		}
	}

	for (int i = 0; i < 9; ++i) // rows
	{
		vector<bool>seen(9, false);
		for (int j = 0; j < 9; ++j)
		{
			if (game[j][i] && !seen[game[j][i] - 1]) seen[game[j][i] - 1]=true;
			else if (game[j][i] && seen[game[j][i] - 1])return false;
		}
	}

	for (int i = 0; i < 9; i += 3) // squares
	{
		for (int j = 0; j < 9; j += 3)
		{
			vector<bool>seen(9, false);
			for (int k = 0; k < 3; ++k)
			{
				for (int h = 0; h < 3; ++h)
				{
					if (game[i + k][j + h] && !seen[game[i + k][j + h] - 1])seen[game[i + k][j + h] - 1]=true;
					else if (game[i + k][j + h] && seen[game[i + k][j + h] - 1])return false;
				}
			}
		}
	}
	return true;
} // time O(n^2), space O(n)

void main()
{
	vector<vector<int>>board{
		{ 5,3,0,0,7,0,0,0,0 },
		{ 6,0,0,1,9,5,0,0,0 },
		{ 0,9,8,0,0,0,0,6,0 },
		{ 8,0,0,0,6,0,0,0,3 },
		{ 4,0,0,8,0,3,0,0,1 },
		{ 7,0,0,0,2,0,0,0,6 },
		{ 0,6,0,0,0,0,2,8,0 },
		{ 0,0,0,4,1,9,0,0,5 },
		{ 0,0,0,0,8,0,0,7,9 },
	};
	assert(check(board) == true);

	board[1][1] = 8;
	assert(check(board) == false);
	system("pause");
}