// rotate 2d array NxN
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <assert.h>
using namespace std;

void rotate(vector<vector<int>>&arr)
{
	int n = arr.size();
	for (int j = 0, level = 0; j < (0.5*n); ++j, ++level)
	{
		for (int i = 0; i < n - 2*level - 1; ++i)
		{
			swap(arr[level][level+i], arr[n - 1 - level - i][level]); // top left - bottom left
			swap(arr[n - 1 - level -i][level], arr[n - 1 - level][n - 1 - level-i]); // bottom left - bottom right
			swap(arr[n - 1 - level][n - 1 - level-i], arr[level+i][n - 1 - level]); // bottom right - top right
		}
	}
} // time O(n^2), space O(1)

class Rotated {
public:
	Rotated(vector<vector<int>>&arr) :arr_{ arr } {};
	int read(int i, int j) { return arr_[arr_.size() - 1 - j][i]; };
private:
	vector<vector<int>>&arr_;
}; // O(1) O(1)

vector<vector<int>> fill(unsigned size)
{
	vector<vector<int>>arr{size, vector<int>(size) };
	int i = 1;
	for (auto iter = arr.begin(); iter < arr.end(); ++iter)
	{
		iota(iter->begin(), iter->end(), i);
		i += size;
	}
	return arr;
}
void print(const vector<vector<int>>&arr)
{
	for (auto iter = arr.begin(); iter < arr.end(); ++iter)
	{
		copy(iter->begin(), iter->end(), ostream_iterator<int>{ cout, " " });
		cout << endl;
	}
}

void reflect_horizontal(vector<vector<int>>&arr)
{
	for (int i = 0; i < arr.size()*0.5; ++i)
	{
		for (int j = 0; j < arr.size(); ++j)
		{
			swap(arr[i][j], arr[arr.size() - 1 - i][j]);
		}
	}
}
int reflect_horizontal_c(const vector<vector<int>>&arr, int i, int j)
{
	return arr[arr.size()-1-i][j];
}

void reflect_vertical(vector<vector<int>>&arr)
{
	for (int i = 0; i < arr.size()*0.5; ++i)
	{
		for (int j = 0; j < arr.size(); ++j)
		{
			swap(arr[j][i], arr[j][arr.size() - 1 - i]);
		}
	}
}
int reflect_vertical_c(const vector<vector<int>>&arr, int i, int j)
{
	return arr[i][arr.size()-1-j];
}

void reflect_diagonal_tleft_bright(vector<vector<int>>&arr)
{
	for (int i = 0; i < arr.size(); ++i)
	{
		for (int j = i+1; j < arr.size(); ++j)
		{
			swap(arr[i][j], arr[j][i]);
		}
	}
}
int reflect_diagonal_tleft_bright_c(const vector<vector<int>>&arr, int i, int j)
{
	return arr[j][i];
}

void reflect_diagonal_tright_bleft(vector<vector<int>>&arr)
{
	for (int i = 0; i < arr.size(); ++i)
	{
		for (int j = 0; j < arr.size()-i; ++j)
		{
			swap(arr[i][j], arr[arr.size()-1-j][arr.size()-1-i]);
		}
	}
}
int reflect_diagonal_tright_bleft_c(const vector<vector<int>>&arr, int i, int j)
{
	return arr[arr.size()-1-j][arr.size()-1-i];
}

void test_rotate();
void test_reflect_horizontal();
void test_reflect_vertical();
void test_reflect_diagonal_tleft_bright();
void test_reflect_diagonal_tright_bleft();

void main()
{
	test_rotate();
	test_reflect_horizontal();
	test_reflect_vertical();
	test_reflect_diagonal_tleft_bright();
	test_reflect_diagonal_tright_bleft();
	system("pause");
}

void test_rotate()
{
	for (int i = 1; i <= 10; ++i)
	{
		auto arr = fill(i);
		auto arr_copy{ arr };
		rotate(arr);
		Rotated a{ arr_copy };
		for (int i = 0; i < arr.size(); ++i)
		{
			for (int j = 0; j < arr.size(); ++j)
			{
				assert(arr[i][j] == a.read(i, j));
			}
		}
	}
}

void test_reflect_horizontal()
{
	for (int i = 1; i <= 10; ++i)
	{
		auto arr = fill(i);
		auto arr_copy{ arr };
		reflect_horizontal(arr);
		for (int i = 0; i < arr.size(); ++i)
		{
			for (int j = 0; j < arr.size(); ++j)
			{
				assert(arr[i][j] == reflect_horizontal_c(arr_copy,i,j));
			}
		}
	}
}

void test_reflect_vertical()
{
	for (int i = 1; i <= 10; ++i)
	{
		auto arr = fill(i);
		auto arr_copy{ arr };
		reflect_vertical(arr);
		for (int i = 0; i < arr.size(); ++i)
		{
			for (int j = 0; j < arr.size(); ++j)
			{
				assert(arr[i][j] == reflect_vertical_c(arr_copy, i, j));
			}
		}
	}
}

void test_reflect_diagonal_tleft_bright()
{
	for (int i = 1; i <= 10; ++i)
	{
		auto arr = fill(i);
		auto arr_copy{ arr };
		reflect_diagonal_tleft_bright(arr);
		for (int i = 0; i < arr.size(); ++i)
		{
			for (int j = 0; j < arr.size(); ++j)
			{
				assert(arr[i][j] == reflect_diagonal_tleft_bright_c(arr_copy, i, j));
			}
		}
	}
}

void test_reflect_diagonal_tright_bleft()
{
	for (int i = 1; i <= 10; ++i)
	{
		auto arr = fill(i);
		auto arr_copy{ arr };
		reflect_diagonal_tright_bleft(arr);
		for (int i = 0; i < arr.size(); ++i)
		{
			for (int j = 0; j < arr.size(); ++j)
			{
				assert(arr[i][j] == reflect_diagonal_tright_bleft_c(arr_copy, i, j));
			}
		}
	}
}