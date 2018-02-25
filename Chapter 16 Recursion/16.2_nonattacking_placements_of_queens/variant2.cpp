// find the smallest number of queens that can be placed to attack each uncovered square
// http://www.sciencedirect.com/science/article/pii/S0166218X09003722
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <iostream>
#include <assert.h>
using namespace std;

struct My_hash {
	size_t operator()(const pair<int, int>&a)const {
		return hash<int>{}(a.first) * 997 ^ hash<int>{}(a.second);
	}
};

void variant2_helper(unordered_set<pair<int, int>, My_hash>board, pair<int, int>queen_position,
	int free_cells, int queens, int& min_q,const int&n);
void change_board(unordered_set<pair<int, int>, My_hash>&board, const pair<int, int>&queen_position,
	int& free_cells,const int& n);
int variant2(int n) {
	if (n == 1) {
		return 1;
	}
	unordered_set<pair<int, int>, My_hash>board;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			board.emplace(i, j);
		}
	}

	int min_queens = n - 1; // queens on the diagonal
	if (n % 2) {
		variant2_helper(board, { n / 2,n / 2 }, n*n, 1, min_queens, n);
	}
	for (int row = n/2-1; row >=0; --row) {
		for (int col = row; col < n - (row + 1); ++col) {
			variant2_helper(board, { row,col }, n*n, 1, min_queens,n);
		}
	}

	return min_queens;
} // time O((n^2,n))=O((en)^n)=O(e^(n*(1+ln(n)))); space O(n*n^2)
void variant2_helper(unordered_set<pair<int, int>, My_hash>board, pair<int, int>queen_position,
	int free_cells, int queens, int& min_q,const int&n) {
	if (queens >= min_q) {
		return;
	}
	change_board(board, queen_position, free_cells,n);
	if (free_cells == 0) {
		min_q = min(min_q, queens);
		return;
	}

	if (queens + 1 >= min_q) {
		return;
	}
	for(int i=0;i<n;++i){
			for (int j = 0; j < n; ++j) {
				variant2_helper(board, { i,j }, free_cells, queens + 1, min_q, n);
			}
	}
}
void change_board(unordered_set<pair<int, int>, My_hash>&board, const pair<int, int>&queen_position,
	int& free_cells,const int&n) {
	if (board.count({ queen_position.first,queen_position.second })) {
		board.erase({ queen_position.first,queen_position.second });
		--free_cells;
	}
	// queen row and column
	for (int col = 0; col < n; ++col) {
		if (board.count({ queen_position.first,col })) {
			board.erase({ queen_position.first,col });
			--free_cells;
		}
		if (board.count({ col,queen_position.second })) {
			board.erase({ col,queen_position.second });
			--free_cells;
		}
	}

	// top right diagonal
	for (int row = queen_position.first - 1, col = queen_position.second + 1;
		row >= 0 && col < n; --row, ++col) {
		if (board.count({ row,col })) {
			board.erase({ row,col });
			--free_cells;
		}
	}

	// top left diagonal
	for (int row = queen_position.first - 1, col = queen_position.second - 1;
		row >= 0 && col >= 0; --row, --col) {
		if (board.count({ row,col })) {
			board.erase({ row,col });
			--free_cells;
		}
	}

	// bottom right diagonal
	for (int row = queen_position.first + 1, col = queen_position.second + 1;
		row <n && col < n; ++row, ++col) {
		if (board.count({ row,col })) {
			board.erase({ row,col });
			--free_cells;
		}
	}

	// bottom left diagonal
	for (int row = queen_position.first + 1, col = queen_position.second - 1;
		row <n && col >= 0; ++row, --col) {
		if (board.count({ row,col })) {
			board.erase({ row,col });
			--free_cells;
		}
	}
}

void test_variant2();

void main() {
	test_variant2();
	system("pause");
}

void test_variant2() {
	vector<int>correct_answer{ 1, 1, 1, 2, 3, 3, 4, 5, 5, 5, 5, 6, 7, 8, 9, 9, 9, 9, 10 };
	for (int i = 1; i < 10; ++i) {
		assert(variant2(i) == correct_answer[i - 1]);
	}
}