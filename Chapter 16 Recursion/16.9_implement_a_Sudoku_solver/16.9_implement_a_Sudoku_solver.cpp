// implement a Sudoku solver
#include <vector>
#include <assert.h>
#include <iostream>
#include <unordered_set>
#include <iterator>
#include <algorithm>
using namespace std;

bool solve_sudoku_helper(vector<vector<int>>&game,int row,int column);
unordered_set<int> impossible_values(const vector<vector<int>>&game, int row, int column);
void solve_sudoku(vector<vector<int>>&game)
{
	solve_sudoku_helper(game, 0, 0);
} // coplexity for desk nXn - O(2^n) as NP complete; space O(n*n) - function stack
bool solve_sudoku_helper(vector<vector<int>>&game, int row, int column)
{
	if (row == game.size())
	{
		row = 0;
		if (++column == game.front().size()) {
			return true;
		}
	}
	if (game[row][column] == 0)
	{
		auto imp = impossible_values(game, row, column);
		for (int i = 1; i <= 9; ++i)
		{
			if (!imp.count(i))
			{
				game[row][column] = i;
				auto res = solve_sudoku_helper(game, row+1, column);
				if (res)return true;
				else game[row][column] = 0;
			}
		}
		return false;
	}
	else
	{
		solve_sudoku_helper(game, row+1, column);
	}
}
unordered_set<int> impossible_values(const vector<vector<int>>&game, int row, int column)
{
	unordered_set<int>res{};
	// add numbers in rows
	for (int i = 0; i < game.size(); ++i)
	{
		if (game[i][column] != 0)res.emplace(game[i][column]);
	}

	// add numbers in cols
	for (int i = 0; i < game[row].size(); ++i)
	{
		if (game[row][i] != 0)res.emplace(game[row][i]);
	}

	// add squares
	int start_row = row - (row % 3);
	int start_col = column - (column % 3);
	for (int i = start_row; i < start_row + 3; ++i)
	{
		for (int j = start_col; j < start_col + 3; ++j)
		{
			if (game[i][j] != 0)res.emplace(game[i][j]);
		}
	}
	return res;
}

void print_table(const vector<vector<int>>&game)
{
	for (int i = 0; i < game.size(); ++i)
	{
		for (int j = 0; j < game.front().size(); ++j)
		{
			cout << game[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}

void check_row(const vector<vector<int>>&game,int row);
void check_col(const vector<vector<int>>&game, int col);
void check_square(const vector<vector<int>>&game, int row, int col);
void is_valid_sudoku(const vector<vector<int>>&game)
{
	for (int i = 0; i < 9; ++i)
	{
		check_row(game, 0);
		check_col(game, 0);
	}
	for (int i = 0; i < 9; i += 3)
	{
		for (int j = 0; j < 9; j += 3)
		{
			check_square(game, i, j);
		}
	}
}
void check_row(const vector<vector<int>>&game, int row)
{
	vector<bool>used(9, false);
	for (int i = 0; i < 9; ++i)
	{
		if (game[row][i] == 0)continue;
		assert(!used[game[row][i]-1]);
		used[game[row][i]-1].flip();
	}
}
void check_col(const vector<vector<int>>&game, int col)
{
	vector<bool>used(9, false);
	for (int i = 0; i < 9; ++i)
	{
		if (game[i][col] == 0)continue;
		assert(!used[game[i][col]-1]);
		used[game[i][col]-1].flip();
	}
}
void check_square(const vector<vector<int>>&game, int row, int col)
{
	vector<bool>used(9, false);
	{
		for (int i = row; i < row + 3; ++i)
		{
			for (int j = col; j < col + 3; ++j)
			{
				if (game[i][j] == 0)continue;
				assert(!used[game[i][j]-1]);
				used[game[i][j]-1].flip();
			}
		}
	}
}


void main()
{
	vector<vector<int>> A(9, vector<int>(9, 0));
	A[0] = { 0, 2, 6, 0, 0, 0, 8, 1, 0 };
	A[1] = { 3, 0, 0, 7, 0, 8, 0, 0, 6 };
	A[2] = { 4, 0, 0, 0, 5, 0, 0, 0, 7 };
	A[3] = { 0, 5, 0, 1, 0, 7, 0, 9, 0 };
	A[4] = { 0, 0, 3, 9, 0, 5, 1, 0, 0 };
	A[5] = { 0, 4, 0, 3, 0, 2, 0, 5, 0 };
	A[6] = { 1, 0, 0, 0, 3, 0, 0, 0, 2 };
	A[7] = { 5, 0, 0, 2, 0, 4, 0, 0, 9 };
	A[8] = { 0, 3, 8, 0, 0, 0, 4, 6, 0 };
	is_valid_sudoku(A);
	print_table(A);
	solve_sudoku(A);
	print_table(A);
	is_valid_sudoku(A);
	vector<vector<int>>game{
		{0,4,0,7,0,3,0,0,5},
		{7,0,0,4,5,0,0,2,3},
		{0,9,0,1,0,8,0,0,0},
		{5,1,2,0,0,0,0,6,0},
		{4,0,0,2,0,1,0,0,8},
		{0,7,0,0,0,0,1,4,2},
		{0,0,0,6,0,4,0,8,0},
		{8,2,0,0,1,5,0,0,6},
		{1,0,0,3,0,2,0,9,0}
	};
	is_valid_sudoku(game);
	print_table(game);
	solve_sudoku(game);
	print_table(game);
	is_valid_sudoku(game);
	system("pause");
}