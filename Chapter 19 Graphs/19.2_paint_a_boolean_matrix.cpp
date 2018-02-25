// paint a boolean matrix
#include <vector>
#include <unordered_set>
#include <array>
#include <iostream>
#include <assert.h>
#include <algorithm>
using namespace std;

struct Coord {
	bool operator==(const Coord& that)const {
		return this->x == that.x && this->y == that.y;
	}
	int x, y;
};

struct Coord_hash {
	size_t operator()(const Coord&c)const {
		return hash<int>()(c.x^c.y * 1021);
	}
};

void paint_helper(vector<vector<int>>&matrix, unordered_set<Coord, Coord_hash>&visited, 
	const Coord&curr,const int& color);
void paint(vector<vector<int>>&matrix, const Coord& start) {
	unordered_set<Coord, Coord_hash>visited{};
	paint_helper(matrix,visited, start, matrix[start.x][start.y]);
} // complexity - DFS time O(|V|+|E|); space O(|V|) V - vertices, E - edges
void paint_helper(vector<vector<int>>&matrix, unordered_set<Coord, Coord_hash>&visited,
	const Coord&curr, const int& color) {
	if (curr.x < 0 || curr.x >= matrix.size() || curr.y < 0 || curr.y >= matrix[curr.x].size() || visited.count(curr) ||
		matrix[curr.x][curr.y] != color) {
		return;
	}
	visited.emplace(curr);
	array<array<int, 2>, 4>shift{ {{0,1},{0,-1},{1,0},{-1,0}} };
	for (const auto& c : shift) {
		paint_helper(matrix, visited, { curr.x + c[0],curr.y + c[1] }, color);
	}
	matrix[curr.x][curr.y] = color==1?0:1;
}

void print_matrix(const vector<vector<int>>&matrix) {
	for (const auto& row : matrix) {
		cout << "{";
		for (const auto& col : row) {
			cout << col << ",";
		}
		cout <<"}"<< endl;
	}
}

void main() {
	vector<vector<int>>matrix{
		{1,0,1,0,0,0,1,1,1,1},
		{0,0,1,0,0,1,0,0,1,1},
		{1,1,1,0,0,1,1,0,1,1},
		{0,1,0,1,1,1,1,0,1,0},
		{1,0,1,0,0,0,0,1,0,0},
		{1,0,1,0,0,1,0,1,1,1},
		{0,0,0,0,1,0,1,0,0,1},
		{1,0,1,0,1,0,1,0,0,0},
		{1,0,1,1,0,0,0,1,1,1},
		{0,0,0,0,0,0,0,1,1,0}
	};
	vector<vector<int>>res{
	{ 1,0,1,0,0,0,1,1,1,1, },
	{0,0,1,0,0,1,0,0,1,1,},
	{1,1,1,0,0,1,1,0,1,1,},
	{0,1,0,1,1,1,1,0,1,0,},
	{1,1,1,1,1,1,1,1,0,0,},
	{1,1,1,1,1,1,1,1,1,1,},
	{1,1,1,1,1,1,1,0,0,1,},
	{1,1,1,1,1,1,1,0,0,0,},
	{1,1,1,1,1,1,1,1,1,1,},
	{1,1,1,1,1,1,1,1,1,0,}
	};
	paint(matrix, { 5,4 });
	assert(equal(matrix.begin(), matrix.end(), res.begin(), res.end()));
	paint(matrix, { 3,6 });
	res = {
	{ 1,0,0,0,0,0,1,1,1,1, },
	{0,0,0,0,0,0,0,0,1,1,},
	{0,0,0,0,0,0,0,0,1,1,},
	{0,0,0,0,0,0,0,0,1,0,},
	{0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,0,}
	};
	assert(equal(matrix.begin(), matrix.end(), res.begin(), res.end()));
	system("pause");
}
