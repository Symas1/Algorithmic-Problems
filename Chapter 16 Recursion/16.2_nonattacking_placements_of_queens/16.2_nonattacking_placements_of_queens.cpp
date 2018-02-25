
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <math.h>
using namespace std;

bool is_valid_board(const vector<int>&board);
void queens_helper(vector<vector<int>>&result, vector<int>&board, const int n);
vector<vector<int>> queens(int n) {
	vector<vector<int>>result;
	vector<int>board;
	queens_helper(result, board, n);
	return result;
} // F(n)~n!/c^n c=2.54
void queens_helper(vector<vector<int>>&result, vector<int>&board, const int n) {
	if (board.size() == n) {
		result.emplace_back(board);
		return;
	}
	for (int i = 0; i < n; ++i) {
		board.emplace_back(i);
		if (is_valid_board(board)) {
			queens_helper(result, board, n);
		}
		board.pop_back();
	}
}
bool is_valid_board(const vector<int>&board) {
	for (int i = board.size() - 2; i >= 0; --i) {
		if (board.back() == board[i]
			|| abs(board.back() - board[i]) == board.size() - 1 - i) {
			return false;
		}
	}
	return true;
}

void print_result(const vector<vector<int>>&result) {
	for (int row = 0; row < result.size(); ++row) {
		for (int col = 0; col < result[row].size(); ++col) {
			string line = string(result[row].size(), '*');
			line[result[row][col]] = '@';
			cout << line << endl;
		}
		cout << endl;
	}
}

int variant1(const vector<vector<int>>&res) {
	int res_number = 0;
	for (const auto&row : res) {
		vector<int>perm(res.front().size());
		iota(perm.begin(), perm.end(), 1);
		do {
			//int iter = 0;
			//for (const auto& col : row) {
			//	string line = string(row.size(), '*');
			//	line[col] = static_cast<char>(perm[iter++] + 'a');
			//	cout << line << endl;
			//}
			//cout << endl;
			++res_number;
		} while (next_permutation(perm.begin(), perm.end()));
	}
	return res_number;
} // time O(n!*res.size()*8n); space O(n)

void variant2_helper(vector<vector<int>>board, pair<int, int>queen_position,
	int free_cells,int queens,int& min_q);
void change_board(vector<vector<int>>&board, const pair<int, int>&queen_position, int& free_cells);
int variant2(int n) {
	if (n == 1) {
		return 1;
	}
	int min_queens = n - 1; // queens on the diagonal
	vector<vector<int>>board(n, vector<int>(n, 0));
	for (int row = 0; row < board.size() / 2; ++row) {
		for (int col = row; col < board[row].size() - (row + 1); ++col) {
			variant2_helper(board, { row,col }, n*n, 1, min_queens);
		}
	}
	if (n % 2) {
		variant2_helper(board, { board.size()/2,board.size()/2 }, n*n, 1, min_queens);
	}
	return min_queens;
} // time O((n^2,n))=O((en)^n)=O(e^(n*(1+ln(n)))); space O(n*n^2)
void variant2_helper(vector<vector<int>>board, pair<int, int>queen_position,
	int free_cells, int queens,int&min_q) {
	if (queens >= min_q) {
		return;
	}
	change_board(board, queen_position, free_cells);
	if (free_cells == 0) {
		min_q = min(min_q, queens);
		return;
	}

	if (queens + 1 >= min_q) {
		return;
	}
	for (int row = 0; row < board.size(); ++row) {
		for (int col = 0; col < board.front().size(); ++col) {
				variant2_helper(board, { row,col }, free_cells, queens + 1, min_q);
		}
	}
}
void change_board(vector<vector<int>>&board, const pair<int, int>&queen_position, int& free_cells) {
	board[queen_position.first][queen_position.second] = 1;
	--free_cells;
	const int occupied = -1;
	const int free_cell = 0;
	// queen row and column
	for (int col = 0; col < board.size(); ++col) {
		if (board[queen_position.first][col] == free_cell) {
			board[queen_position.first][col] = occupied;
			--free_cells;
		}
		if (board[col][queen_position.second] == free_cell) {
			board[col][queen_position.second] = occupied;
			--free_cells;
		}
	}

	// top right diagonal
	for (int row = queen_position.first - 1, col = queen_position.second + 1;
		row >= 0 && col < board.front().size(); --row, ++col) {
		if (board[row][col] == free_cell) {
			board[row][col] = occupied;
			--free_cells;
		}
	}

	// top left diagonal
	for (int row = queen_position.first - 1, col = queen_position.second - 1;
		row >= 0 && col >= 0; --row, --col) {
		if (board[row][col] == free_cell) {
			board[row][col] = occupied;
			--free_cells;
		}
	}

	// bottom right diagonal
	for (int row = queen_position.first + 1, col = queen_position.second + 1;
		row <board.size() && col < board.front().size(); ++row, ++col) {
		if (board[row][col] == free_cell) {
			board[row][col] = occupied;
			--free_cells;
		}
	}

	// bottom left diagonal
	for (int row = queen_position.first + 1, col = queen_position.second - 1;
		row <board.size() && col >= 0; ++row, --col) {
		if (board[row][col] == free_cell) {
			board[row][col] = occupied;
			--free_cells;
		}
	}
}

void test_main();
void test_variant1();
void test_variant2();

void main() {
	//test_main();
	//test_variant1();
	test_variant2();
	system("pause");
}

void test_main() {
	vector<int>corrent_answer{ 1,0,0,2,10,4,40,92,352,724 };
	for (int i = 1; i <= 10; ++i) {
		assert(queens(i).size() == corrent_answer[i - 1]);
	}
}

void test_variant1() {
	for (int i = 1; i <= 6; ++i) {
		auto boards = queens(i);
		assert(variant1(boards) == tgamma(i + 1)*boards.size());
	}
}

void test_variant2() {
	vector<int>correct_answer{ 1, 1, 1, 2, 3, 3, 4, 5, 5, 5, 5, 6, 7, 8, 9, 9, 9, 9, 10 };
	for (int i = 1; i < 10; ++i) {
		assert(variant2(i) == correct_answer[i - 1]);
	}
}