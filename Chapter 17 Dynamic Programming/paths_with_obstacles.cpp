// https://leetcode.com/problems/unique-paths-ii/description/

class Solution {
public:
	int uniquePathsWithObstacles(vector<vector<int>>& obstacle) {
		auto rows = obstacle.size();
		auto cols = obstacle.front().size();
		vector<int>paths(cols, 0);
		if (obstacle[0][0]) {
			return 0;
		}
		paths[0] = 1;
		for (int i = 0; i<rows; ++i) {
			for (int j = 0; j<cols; ++j) {
				paths[j] = obstacle[i][j] == 1 ? 0 : ((j - 1 >= 0 ? paths[j - 1] : 0) + paths[j]);
			}
		}
		return paths.back();
	}
}; // time O(rows*cols); space O(cols)

class Solution {
public:
	int uniquePathsWithObstacles(vector<vector<int>>& obstacle) {
		auto rows = obstacle.size();
		auto cols = obstacle.front().size();
		bool swapped = false;
		if (cols>rows) {
			swap(cols, rows);
			swapped = true;
		}
		vector<int>paths(cols, 0);
		if (obstacle[0][0]) {
			return 0;
		}
		paths[0] = 1;
		for (int i = 0; i<rows; ++i) {
			for (int j = 0; j<cols; ++j) {
				if (!swapped) {
					paths[j] = obstacle[i][j] == 1 ? 0 : ((j - 1 >= 0 ? paths[j - 1] : 0) + paths[j]);
				}
				else {
					paths[j] = obstacle[j][i] == 1 ? 0 : ((j - 1 >= 0 ? paths[j - 1] : 0) + paths[j]);
				}

			}
		}
		return paths.back();
	}
}; // time O(rows*cols); space O(min(rows,cols))