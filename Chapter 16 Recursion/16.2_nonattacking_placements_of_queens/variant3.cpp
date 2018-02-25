// compute a placement of 32 knights on an 8x8 chessboard in which no two pieces attack each other
#include <array>
#include <iostream>
#include <iomanip>
using namespace std;

array<array<short, 8>, 8> answer_board;

bool variant3_helper(array<array<short, 8>, 8>&current_board,const pair<short,short> piece_pos,
	short& free_cells, short& left_pieces);
void change_board(array<array<short, 8>, 8>&current_board, const pair<short, short>& piece_pos, short& free_cells, bool forward, const short number);
bool in_range_and_free(const array<array<short, 8>, 8>&current_board, const short row,const short col,
	bool forward, const short number);
void variant3() {
	array<array<short, 8>, 8> current_board{0};
	short left_pieces = 32;
	short free_cells = 64;
	for (int row = 0; row < current_board.size(); ++row) {
		for (int col = row%2==0?0:1; col < current_board[row].size(); col=col+2) {
			if (variant3_helper(current_board, { row,col }, free_cells, left_pieces)) {
				answer_board = current_board;
				return;
			}		
		}
	}
} // time O(n^2); space O(n^2)
bool variant3_helper(array<array<short, 8>, 8>&current_board, const pair<short, short> piece_pos,
	short& free_cells, short& left_pieces) {
	change_board(current_board, piece_pos, free_cells,true,left_pieces);
	if (left_pieces-1 == 0) {
		return true;
	}else if (free_cells == 0 || left_pieces-1>free_cells) {
		change_board(current_board, piece_pos, free_cells, false,left_pieces);
		++left_pieces;
		return false;
	}
	for (int row = 0; row < current_board.size(); ++row) {
		for (int col = row % 2 == 0 ? 0 : 1; col < current_board[row].size(); col=col+2) {
			if (current_board[row][col] == 0) {
				if (variant3_helper(current_board, { row ,col }, free_cells, --left_pieces)) {
					return true;
				}
			}
		}
	}
	change_board(current_board, piece_pos,free_cells, false,left_pieces);
	++left_pieces;
	return false;
}
void change_board(array<array<short, 8>, 8>&current_board, const pair<short, short>& piece_pos,
	short& free_cells,bool forward,const short number) {
	const short piece_occupied = forward?number:0;
	const short under_attack = forward?-number:0;
	const short free_cells_add = forward ? -1 : 1;
	current_board[piece_pos.first][piece_pos.second] = piece_occupied;
	free_cells += free_cells_add;

	// height top right
	if (in_range_and_free(current_board,piece_pos.first - 2, piece_pos.second + 1,forward,number)) {
		current_board[piece_pos.first - 2][piece_pos.second + 1] = under_attack;
		free_cells += free_cells_add;
	}
	// height top left
	if (in_range_and_free(current_board, piece_pos.first - 2, piece_pos.second - 1, forward, number)) {
		current_board[piece_pos.first - 2][piece_pos.second - 1] = under_attack;
		free_cells += free_cells_add;
	}
	// height bottom right
	if (in_range_and_free(current_board, piece_pos.first + 2, piece_pos.second + 1, forward, number)) {
		current_board[piece_pos.first + 2][piece_pos.second + 1] = under_attack;
		free_cells += free_cells_add;
	}
	// height bottom left
	if (in_range_and_free(current_board, piece_pos.first + 2, piece_pos.second - 1, forward, number)) {
		current_board[piece_pos.first + 2][piece_pos.second - 1] = under_attack;
		free_cells += free_cells_add;
	}

	// width top right
	if (in_range_and_free(current_board, piece_pos.first - 1, piece_pos.second + 2, forward, number)) {
		current_board[piece_pos.first - 1][piece_pos.second + 2] = under_attack;
		free_cells += free_cells_add;
	}
	// width top left
	if (in_range_and_free(current_board, piece_pos.first - 1, piece_pos.second - 2, forward, number)) {
		current_board[piece_pos.first - 1][piece_pos.second - 2] = under_attack;
		free_cells += free_cells_add;
	}
	// width bottom right
	if (in_range_and_free(current_board, piece_pos.first + 1, piece_pos.second + 2, forward, number)) {
		current_board[piece_pos.first + 1][piece_pos.second + 2] = under_attack;
		free_cells += free_cells_add;
	}
	// width bottom left
	if (in_range_and_free(current_board, piece_pos.first + 1, piece_pos.second - 2, forward, number)) {
		current_board[piece_pos.first + 1][piece_pos.second - 2] = under_attack;
		free_cells += free_cells_add;
	}
}
bool in_range_and_free(const array<array<short, 8>, 8>&current_board,const short row,const short col,
	bool forward,const short number) {
	return row >= 0 && row <= 7 && col >= 0 && col <= 7 && (forward?current_board[row][col]==0:
		current_board[row][col]==-number);
}

void main() {
	variant3();
	for (int i = 0; i < answer_board.size(); ++i) {
		for (int j = 0; j < answer_board[i].size(); ++j) {
			cout <<setw(5)<< answer_board[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	system("pause");
}