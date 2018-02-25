// search a maze
#include <vector>
#include <assert.h>
#include <iostream>
#include <unordered_set>
#include <array>
#include <random>
#include <algorithm>
#include <iterator>
#include <queue>
using namespace std;

struct Coord {
	int row, col;
};

bool operator==(const Coord&a, const Coord&b) {
	return a.row == b.row&& a.col == b.col;
}

struct Coord_hash {
	size_t operator()(const Coord&c)const {
		return hash<int>()(c.row ^ c.col * 1021);
	}
};

bool search_maze_helper(const vector<vector<int>>&maze, vector<Coord>&path,
	unordered_set<Coord, Coord_hash>&visited, const Coord&start, const Coord&end);
vector<Coord> search_maze(const vector<vector<int>>&maze, const Coord& start, const Coord&end) {
	unordered_set<Coord, Coord_hash>visited{};
	vector<Coord>path{};
	search_maze_helper(maze, path, visited, start, end);
	return path;
} // time and space as for DFS O(|V|+|E|) and O(|V|) V - vertices, E - edges
bool search_maze_helper(const vector<vector<int>>&maze, vector<Coord>&path,
	unordered_set<Coord, Coord_hash>&visited, const Coord&start, const Coord&end) {
	if (start.row < 0 || start.row >= maze.size() || start.col < 0 || start.col >= maze[start.row].size()||
		visited.count(start) || maze[start.row][start.col] == 1) {
		return false;
	}
	if (start == end) {
		path.emplace_back(start);
		return true;
	}

	visited.emplace(start);
	path.emplace_back(start);
	array<array<int, 2>, 4>shift{ {{0,1},{0,-1},{1,0},{-1,0} } };
	for (const auto& s : shift) {
		if (search_maze_helper(maze, path, visited, { start.row + s[0] ,start.col + s[1] }, end)) {
			return true;
		}
	}
	path.pop_back();
	return false;
}


bool is_feasible(const vector<vector<int>>&maze, const unordered_set<Coord, Coord_hash>&visited, const Coord& cell);
vector<Coord> search_maze_bfs(const vector<vector<int>>& maze, const Coord& start, const Coord& end) {
	unordered_set<Coord, Coord_hash>visited{ {start} };
	queue<Coord>que{ {start} };
	vector<Coord>res{};
	array<array<int, 2>, 4>shift{ { { 0,1 },{ 0,-1 },{ 1,0 },{ -1,0 } } };
	while (!que.empty()) {
		auto current_cell = que.front();
		que.pop();
		if (current_cell == end) {
			res.emplace_back(current_cell);
			return res;
		}
		res.emplace_back(current_cell);
		for (const auto& s : shift) {
			if (is_feasible(maze, visited,{current_cell.row+s[0],current_cell.col+s[1]})) {
				que.emplace(current_cell.row + s[0],current_cell.col + s[1]);
				visited.emplace(current_cell.row + s[0], current_cell.col + s[1]);
			}
		}
	}
	return{};
}
bool is_feasible(const vector<vector<int>>& maze, const unordered_set<Coord, Coord_hash>& visited, const Coord & cell)
{
	if (cell.row < 0 || cell.row >= maze.size() || cell.col < 0 || cell.col >= maze[cell.row].size() ||
		visited.count(cell) || maze[cell.row][cell.col] == 1) {
		return false;
	}
	return true;
}

void small_test() {
	vector<vector<int>>maze{
		{ 1,0,0,0 },
		{ 0,0,1,0 },
		{ 1,0,1,0 },
		{ 0,0,0,1 }
	};
	auto res = search_maze(maze, { 3,0 }, { 0,3 });
	assert(res.size() == 7);
	for (const auto& x : res) {
		cout << x.row << " " << x.col << endl;
	}

	maze[2][1] = 1, maze[2][3] = 1; // block one line
	res = search_maze(maze, { 3,0 }, { 0,3 });
	assert(res.size() == 0);

	res = search_maze(maze, { 3,0 }, { 3,2 });
	assert(res.size() == 3);
}

void main() {
	small_test();
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 1000; ++i) {
		const int rows= uniform_int_distribution<>{ 1,30 }(mt);
		const int cols = uniform_int_distribution<>{ 1,30 }(mt);
		vector<vector<int>>maze(rows, vector<int>(cols, 0));
		for (auto iter = maze.begin(); iter != maze.end(); ++iter) {
			generate(iter->begin(), iter->end(), [&mt]() {return uniform_int_distribution<>{0, 1}(mt); });
		}
		int start_row = uniform_int_distribution<>{ 0,rows-1 }(mt);
		int start_col = uniform_int_distribution<>{ 0,cols-1 }(mt);

		int end_row = uniform_int_distribution<>{ 0,rows-1 }(mt);
		int end_col = uniform_int_distribution<>{ 0,cols-1 }(mt);

		Coord start = { start_row, start_col };
		Coord end = { end_row, end_col };

		maze[start_row][start_col] = 0, maze[end_row][end_col] = 0;

		auto path = search_maze(maze, start, end);
		if (!path.empty()) {
			assert(path.front() == start && path.back()== end);
			for (int i = 1; i < path.size(); ++i) {
				assert(abs(path[i - 1].row - path[i].row) +
					abs(path[i - 1].col - path[i].col) == 1);
			}
		}
	}
	system("pause");
}