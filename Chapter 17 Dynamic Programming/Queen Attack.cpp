#include <vector>
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <functional>
#include <cmath>
#include <random>
#include <assert.h>
#include <unordered_set>
#include <unordered_map>
#include <string>
using namespace std;

enum dir{right,b_r_diag,bottom,b_l_diag,left,t_l_diag,top,t_r_diag};

struct Cell_and_dir {
	int row;
	int col;
	dir direction;
	bool operator==(const Cell_and_dir& comp)const {
		return this->row == comp.row && this->col == comp.col && this->direction == comp.direction;
	}
};

struct Hash {
	size_t operator()(const Cell_and_dir& curr)const {
		return hash<int>{}(curr.row ^ curr.col * 997 ^ curr.direction * 15486469);
	}
};

using my_map = unordered_map<Cell_and_dir,bool, Hash>;

void explore_direction(const vector<string>&board, my_map& hash,
	const int curr_row, const int curr_col, const dir direction);
dir opposite_direction(const dir direction);
pair<int, int> previous_coords(const dir direction, const int curr_row, const int curr_col);
pair<int, int>next_coords(const dir direction, const int curr_row, const int curr_col);
bool is_legal_position(const vector<string>&board, const int curr_row, const int curr_col);
vector<vector<int>> queens(const vector<string>&board) {
	vector<vector<int>>result(board.size(), vector<int>(board.front().size(), 0));
	my_map hash;
	for (int row = 0; row < board.size(); ++row) {
		for (int col = 0; col < board[row].size(); ++col) {
			if (!hash.count({ row,col,dir::right })) {
				explore_direction(board, hash, row, col, dir::right);
			}
			if (!hash.count({ row,col,dir::b_r_diag })) {
				explore_direction(board, hash, row, col, dir::b_r_diag);
			}
			if (!hash.count({ row,col,dir::bottom })) {
				explore_direction(board, hash, row, col, dir::bottom);
			}
			if (!hash.count({ row,col,dir::b_l_diag })) {
				explore_direction(board, hash, row, col, dir::b_l_diag);
			}

			result[row][col] += hash[{row, col, dir::right}];
			result[row][col] += hash[{row, col, dir::b_r_diag}];
			result[row][col] += hash[{row, col, dir::bottom}];
			result[row][col] += hash[{row, col, dir::b_l_diag}];
			result[row][col] += hash[{row, col, dir::left}];
			result[row][col] += hash[{row, col, dir::t_l_diag}];
			result[row][col] += hash[{row, col, dir::top}];
			result[row][col] += hash[{row, col, dir::t_r_diag}];
		}
		if (row > 0) {
			for (int col = 0; col < board[row].size(); ++col) {
				for (int k = 0; k <= 7; ++k) {
					hash.erase(Cell_and_dir{ row - 1,col,(dir)k });
				}
			}
		}
	}
	return result;
} // time O(16*(n*m)); space O(8*(n*m))
void explore_direction(const vector<string>&board, my_map& hash,
	const int curr_row, const int curr_col, const dir direction) {
	if (!is_legal_position(board, curr_row, curr_col) || hash.count({curr_row,curr_col,direction})) {
		return;
	}

	auto prev_coords = previous_coords(direction, curr_row, curr_col);
	if (is_legal_position(board, prev_coords.first, prev_coords.second)) {
		bool queen = board[prev_coords.first][prev_coords.second] == '1' ||
			hash[{prev_coords.first, prev_coords.second, opposite_direction(direction)}];
		hash.emplace(Cell_and_dir{ curr_row,curr_col,opposite_direction(direction) }, queen);
	}
	else {
		hash.emplace(Cell_and_dir{ curr_row,curr_col,opposite_direction(direction) }, false);
	}

	auto next = next_coords(direction, curr_row, curr_col);
	explore_direction(board, hash, next.first, next.second, direction);

	if (is_legal_position(board, next.first, next.second)) {
		bool queen = board[next.first][next.second] == '1' ||
			hash[{next.first, next.second, direction}];
		hash.emplace(Cell_and_dir{ curr_row,curr_col,direction}, queen);
	}
	else {
		hash.emplace(Cell_and_dir{ curr_row,curr_col,direction }, false);
	}
}
dir opposite_direction(const dir direction) {
	if (direction == dir::right) {
		return dir::left;
	}
	else if (direction == dir::b_r_diag) {
		return dir::t_l_diag;
	}
	else if (direction == dir::bottom) {
		return dir::top;
	}
	else if (direction == dir::b_l_diag) {
		return dir::t_r_diag;
	}
}
pair<int, int> previous_coords(const dir direction, const int curr_row, const int curr_col) {
	if (direction == dir::right) {
		return { curr_row ,curr_col - 1};
	}
	else if (direction == dir::b_r_diag) {
		return { curr_row -1,curr_col - 1 };
	}
	else if (direction == dir::bottom) {
		return { curr_row - 1,curr_col };
	}
	else if (direction == dir::b_l_diag) {
		return { curr_row - 1,curr_col+1 };
	}
}
pair<int, int>next_coords(const dir direction, const int curr_row, const int curr_col) {
	if (direction == dir::right) {
		return { curr_row ,curr_col + 1 };
	}
	else if (direction == dir::b_r_diag) {
		return { curr_row + 1,curr_col + 1 };
	}
	else if (direction == dir::bottom) {
		return { curr_row + 1,curr_col };
	}
	else if (direction == dir::b_l_diag) {
		return { curr_row + 1,curr_col - 1 };
	}
}
bool is_legal_position(const vector<string>&board, const int curr_row, const int curr_col) {
	if (curr_row >= board.size() || curr_col >= board[curr_row].size()) {
		return false;
	}
	return true;
}


void test();

void main() {
	vector<string>board{
		"010",
		"100",
		"001"
	};
	cout << "BOARD:\n";
	for (const auto& str:board) {
		cout << str << endl;
	}
	cout << endl;

	auto res = queens(board);
	cout << "RESULT:\n";
	for (auto iter = res.begin(); iter != res.end(); ++iter) {
		copy(iter->begin(), iter->end(), ostream_iterator<int>{cout, " "});
		cout << endl;
	}
	cout << endl;

	system("pause");
}

void test() {

}