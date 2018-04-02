
#include <vector>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <array>
using namespace std;

struct Pos {
	int row;
	int col;
};

bool operator==(const Pos& a, const Pos& b) {
	return a.row == b.row && a.col == b.col;
}

struct Pos_hash {
	size_t operator()(const Pos& a)const {
		return hash<int>{}(a.row * 997 + a.col);
	}
};

void min_moves_helper(vector<vector<unsigned>>&min_board, unordered_set<Pos, Pos_hash>&used,
	const Pos& start,const Pos& end, unsigned cost);

bool approved_move(const vector<vector<unsigned>>&min_board, const unordered_set<Pos, Pos_hash>&used,
	const Pos& next, unsigned next_cost);

unsigned min_moves(unsigned rows, unsigned cols, const Pos& start, const Pos& end) {
	vector<vector<unsigned>>min_board(rows, vector<unsigned>(cols, numeric_limits<unsigned>::max()));
	unordered_set<Pos, Pos_hash>used;
	min_moves_helper(min_board, used, start,end, 0);
	return min_board[end.row][end.col];
}
void min_moves_helper(vector<vector<unsigned>>&min_board, unordered_set<Pos, Pos_hash>&used,
	const Pos& start,const Pos& end, unsigned cost) {
	min_board[start.row][start.col] = cost;
	if (start == end) {
		return;
	}
	used.emplace(start);

	// Knight moves
	array<array<int, 2>, 4>moves{ { { -1,-2 },{ -2,-1 },{ -2,1 },{ -1,2 } } };
	for (const auto& move : moves) {
		Pos next_cell = { start.row + move[0],start.col + move[1] };
		if (approved_move(min_board, used, next_cell, cost + 1)) {
			min_moves_helper(min_board, used, next_cell,end, cost + 1);
		}
		next_cell = { start.row - move[0],start.col - move[1] };
		if (approved_move(min_board, used, next_cell, cost + 1)) {
			min_moves_helper(min_board, used, next_cell, end, cost + 1);
		}
	}

	// King moves
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (i != 0 || j != 0) {
				Pos next_cell{ start.row + i ,start.col + j };
				if (approved_move(min_board, used, next_cell, cost + 1)) {
					min_moves_helper(min_board, used, next_cell, end, cost + 1);
				}
			}
		}
	}

	used.erase(start);
}
bool approved_move(const vector<vector<unsigned>>&min_board, const unordered_set<Pos, Pos_hash>&used,
	const Pos& next,unsigned next_cost) {
	return (next.row >= 0 && next.row < min_board.size() && next.col >= 0 && next.col < min_board.front().size()) && (used.count(next) == 0) &&
		(next_cost < min_board[next.row][next.col]);
}

void main() {
	assert(min_moves(8, 8, { 0,0 }, { 7,7 }) == 5);
	assert(min_moves(7, 7, { 0,0 }, { 6,6 }) == 4);
	assert(min_moves(6, 6, { 0,0 }, { 5,5 }) == 4);
	assert(min_moves(5, 5, { 0,0 }, { 4,4 }) == 3);
	assert(min_moves(4, 4, { 0,0 }, { 3,3 }) == 2);
	assert(min_moves(3, 3, { 0,0 }, { 2,2 }) == 2);
	assert(min_moves(2, 2, { 0,0 }, { 1,1 }) == 1);
	assert(min_moves(1, 1, { 0,0 }, { 0,0 }) == 0);
	system("pause");
}