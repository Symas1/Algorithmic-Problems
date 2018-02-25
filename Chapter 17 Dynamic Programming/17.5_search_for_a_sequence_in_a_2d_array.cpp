// search for a sequence in a 2d array
#include <vector>
#include <unordered_set>
#include <iostream>
#include <assert.h>
#include <tuple>
#include <algorithm>
#include <random>
#include <iterator>
using namespace std;

struct Hash_for_tuple {
	size_t operator()(const tuple<int, int, int>&t)const {
		return hash<int>()(get<0>(t) ^ get<1>(t) * 1021 ^ get<2>(t) * 998537);
	}
};

bool sequence_exists_starting_from_this_point(const vector<vector<int>>&grid, const vector<int>&sequence,
	int offset, int row, int col, unordered_set<tuple<int, int, int>, Hash_for_tuple>&previous_attempts);
bool grid_contains_sequence(const vector<vector<int>>& grid, const vector<int>&sequence) {
	unordered_set<tuple<int, int, int>, Hash_for_tuple>previous_attempts{};

	for (int row = 0; row < grid.size(); ++row) {
		for (int col = 0; col < grid[row].size(); ++col) {
			if (sequence_exists_starting_from_this_point(grid, sequence, 0, row, col, previous_attempts)) {
				return true;
			}
		}
	}
	return false;
} // time O(nm|S|) - n rows, m cols, S sequence length; space O(nm|S|)
bool sequence_exists_starting_from_this_point(const vector<vector<int>>&grid, const vector<int>&sequence,
	int offset, int row, int col, unordered_set<tuple<int, int, int>, Hash_for_tuple>&previous_attempts) {
	if (offset == sequence.size()) {
		return true;
	}
	if (row < 0 || row >= grid.size() || col<0 || col>=grid[row].size() ||
		grid[row][col] != sequence[offset] || previous_attempts.count({ row,col,offset })) {
		return false;
	}

	if (sequence_exists_starting_from_this_point(grid, sequence, offset + 1, row - 1, col, previous_attempts) ||
		sequence_exists_starting_from_this_point(grid, sequence, offset + 1, row, col + 1, previous_attempts) ||
		sequence_exists_starting_from_this_point(grid, sequence, offset + 1, row + 1, col, previous_attempts) ||
		sequence_exists_starting_from_this_point(grid, sequence, offset + 1, row, col - 1, previous_attempts)) {
		return true;
	}

	previous_attempts.emplace(row, col, offset);
	return false;
}

vector<vector<int>>rand_matrix(int rows, int cols) {
	vector<vector<int>>res(rows, vector<int>(cols, 0));
	mt19937 mt{ random_device{}() };
	for (auto i = res.begin(); i != res.end(); ++i) {
		generate(i->begin(), i->end(), [&mt]() {
			return uniform_int_distribution<>{0, 9}(mt);
		});
	}
	return res;
}

vector<int> rand_sequence(int size) {
	mt19937 mt{ random_device{}() };
	vector<int>res(size, 0);
	generate(res.begin(), res.end(), [&mt]() {
		return uniform_int_distribution<>{0, 9}(mt);
	});
	return res;
}

void small_test() {
	vector<vector<int>>grid{
		{1,2,3},
		{3,4,5},
		{5,6,7}
	};
	vector<int>sequence{ 1,3,4,6 };
	assert(grid_contains_sequence(grid, sequence));
	sequence={ 1,2,3,4 };
	assert(!grid_contains_sequence(grid, sequence));
}

void main() {
	small_test();

	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 100; ++i)
	{
		const int rows = uniform_int_distribution<>{ 0,10 }(mt);
		const int cols = uniform_int_distribution<>{ 0,10 }(mt);
		auto grid = rand_matrix(rows, cols);
		const int seq_size = uniform_int_distribution<>{ 0,10 }(mt);
		auto sequence = rand_sequence(seq_size);

		cout << "Grid: " << endl;
		for (auto i = grid.begin(); i != grid.end(); ++i) {
			copy(i->begin(), i->end(), ostream_iterator<int>{cout, " "});
			cout << endl;
		}
		cout << "Sequence: " << endl;
		copy(sequence.begin(), sequence.end(), ostream_iterator<int>{cout, " "});
		cout << endl;

		cout << boolalpha << grid_contains_sequence(grid, sequence) << endl;
	}
	system("pause");
}