// compute enclosed regions
#include <vector>
#include <array>
#include <algorithm>
#include <assert.h>
#include <unordered_set>
using namespace std;

struct Coord {
	bool operator==(const Coord&that)const {
		return this->x == that.x && this->y == that.y;
	}
	int x, y;
};

struct Coord_hash {
	size_t operator()(const Coord&c)const {
		return hash<int>()(c.x^c.y * 1021);
	}
};

enum Color { W, B };

unordered_set<Coord, Coord_hash> boundary_elements(const vector<vector<Color>>&matrix);
void boundary_elements_helper(const vector<vector<Color>>&matrix, unordered_set<Coord, Coord_hash>&visited, const Coord& curr);
void enclosed_regions(vector<vector<Color>>&matrix) {
	auto visited = boundary_elements(matrix);
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix[i].size(); ++j) {
			if (!visited.count({ i,j })) {
				matrix[i][j] = B;
			}
		}
	}
} // time O(nm); space O(nm) (can do better if make array of chars and mark cell as for change)

unordered_set<Coord, Coord_hash> boundary_elements(const vector<vector<Color>>& matrix)
{
	unordered_set<Coord, Coord_hash>visited{};

	// top
	for (int i = 0; i < matrix.front().size(); ++i) {
		boundary_elements_helper(matrix, visited, { 0,i });
	}

	// right
	for (int i = 1; i < matrix.size(); ++i) {
		boundary_elements_helper(matrix, visited, { i,static_cast<int>(matrix[i].size() - 1) });
	}

	// bottom
	for (int i = 0; i < matrix.back().size() - 1; ++i) {
		boundary_elements_helper(matrix, visited, { static_cast<int>(matrix.size() - 1),i });
	}

	// left
	for (int i = 1; i < matrix.size() - 1; ++i) {
		boundary_elements_helper(matrix, visited, { i,0 });
	}

	return visited;
}

void boundary_elements_helper(const vector<vector<Color>>& matrix, unordered_set<Coord, Coord_hash>&visited, const Coord& curr)
{
	if (curr.x < 0 || curr.x >= matrix.size() || curr.y < 0 || curr.y >= matrix[curr.x].size() ||
		matrix[curr.x][curr.y] == Color::B || visited.count(curr)) {
		return;
	}

	visited.emplace(curr);
	const array<array<int, 2>, 4>shift{ {{0,1},{0,-1},{1,0},{-1,0} } };
	for (const auto& s : shift) {
		boundary_elements_helper(matrix, visited, { curr.x + s[0],curr.y + s[1] });
	}
}

void main() {
	vector<vector<Color>>matrix{
		{B,B,B,B},
		{W,B,W,B},
		{B,W,W,B},
		{B,B,B,B}
	};
	enclosed_regions(matrix);
	vector<vector<Color>> check{
		{B,B,B,B},
		{W,B,B,B},
		{B,B,B,B},
		{B,B,B,B}
	};
	assert(equal(matrix.begin(), matrix.end(), check.begin(), check.end()));


	system("pause");
}
