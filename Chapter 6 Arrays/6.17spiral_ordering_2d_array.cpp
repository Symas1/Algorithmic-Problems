// compute spiral ordering of 2d array
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <string>
#include <array>
#include <numeric>
#include <utility>
#include <assert.h>
using namespace std;

void spiral_helper(const vector<vector<int>>&arr, int offset);

void spiral(const vector<vector<int>>& arr)
{
	for (int i = 0; i < ceil(0.5*arr.size()); ++i)
	{
		spiral_helper(arr, i);
	}
} // O(n^2), O(1)

void spiral_helper(const vector<vector<int>>&arr, int offset)
{
	if (offset == arr.size() - offset - 1) // center of odd matrix
	{
		cout << arr[offset][offset] << " ";
		return;
	}

	for (int i = offset; i < arr[0].size() - offset; ++i) // top
	{
		cout << arr[offset][i] << " ";
	}

	for (int i = offset + 1; i < arr.size() - offset; ++i) // right
	{
		cout << arr[i][arr.size() - 1 - offset] << " ";
	}

	for (int i = arr[0].size() - 2 - offset; i >= offset; --i) // bottom
	{
		cout << arr[arr.size() - 1 - offset][i] << " ";
	}

	for (int i = arr.size() - 2 - offset; i > offset; --i) // left
	{
		cout << arr[i][offset] << " ";
	}
}

vector<int> spiral_second(vector<vector<int>>arr)
{
	const array<array<int, 2>, 4>shift{ {{0,1},{1,0},{0,-1},{-1,0} } };
	int dir = 0, x = 0, y = 0;

	vector<int>res{};

	for (int i = 0; i < arr.size()*arr.size(); ++i)
	{
		res.emplace_back(arr[x][y]);
		cout << arr[x][y] << " ";
		arr[x][y] = 0;
		int next_x = x + shift[dir][0];
		int next_y = y + shift[dir][1];
		if (next_x < 0 || next_x >= arr.size() || next_y < 0 || next_y >= arr.size() || arr[next_x][next_y] == 0)
		{
			dir = (dir + 1) % 4;
			next_x = x + shift[dir][0];
			next_y = y + shift[dir][1];
		}
		x = next_x;
		y = next_y;
	}
	return res;
} // O(n^2), O(1)

vector<vector<int>> variant1(int dimension)
{
	const array<array<int, 2>, 4>shift{ {{0,1},{1,0},{0,-1},{-1,0}} };
	int x = 0, y = 0, dir = 0;

	vector<vector<int>>res(dimension, vector<int>(dimension, 0));
	for (int i = 1; i <= dimension*dimension; ++i)
	{
		res[x][y] = i;
		int next_x = x + shift[dir][0];
		int next_y = y + shift[dir][1];
		if (next_x < 0 || next_x >= res.size() || next_y < 0 || next_y >= res.size() || res[next_x][next_y] != 0)
		{
			dir = (dir + 1) % 4;
			next_x = x + shift[dir][0];
			next_y = y + shift[dir][1];
		}
		x = next_x;
		y = next_y;
	}
	return res;
}

vector<vector<int>> variant2(const vector<int>&seq)
{
	vector < vector<int>>res(sqrt(seq.size()), vector<int>(sqrt(seq.size()), numeric_limits<int>::min()));
	int x = 0, y = 0, dir = 0;
	const array<array<int, 2>, 4>shift{ {{0,1},{1,0},{0,-1},{-1,0}} };
	for (int i = 0; i < seq.size(); ++i)
	{
		res[x][y] = seq[i];
		int next_x = x + shift[dir][0];
		int next_y = y + shift[dir][1];
		if (next_x < 0 || next_x >= res.size() || next_y < 0 || next_y >= res.size() || res[next_x][next_y] != numeric_limits<int>::min())
		{
			dir = (dir + 1) % 4;
			next_x = x + shift[dir][0];
			next_y = y + shift[dir][1];
		}
		x = next_x;
		y = next_y;
	}
	return res;
}

void variant3(int pairs)
{
	const array<array<int, 2>, 4>shift{ { { 1,0 },{ 0,-1 },{ -1,0 },{ 0,1 } } };
	int x = 0, y = 0, dir = 0, size = 1;

	cout << "(" << x++ << "," << y << ") ";
	for (int i = 1, counter = 0; i < pairs; ++i)
	{
		cout << "(" << x << "," << y << ") ";
		++counter;
		if (dir == 0 && counter == size)
		{
			dir = 1;
			counter = 0;
		}
		else if (dir == 1 && counter == size)
		{
			dir = 2;
			counter = 0;
		}
		else if (dir == 2 && counter == size + 1)
		{
			dir = 3;
			counter = 0;
		}
		else if (dir == 3 && counter == size + 1)
		{
			dir = 0;
			counter = 0;
			size += 2;
		}
		x = x + shift[dir][0];
		y = y + shift[dir][1];
	}
}

vector<int> variant4(vector<vector<int>>arr)
{
	array<array<int, 2>, 4>shift{ {{0,1},{1,0},{0,-1},{-1,0}} };
	int x = 0, y = 0, dir = 0;
	vector<int>res{};
	for (int i = 0; i < arr.size()*arr.begin()->size(); ++i)
	{
		res.emplace_back(arr[x][y]);
		cout << arr[x][y] << " ";
		arr[x][y] = 0;
		int next_x = x + shift[dir][0];
		int next_y = y + shift[dir][1];
		if (next_x < 0 || next_x >= arr.size() || next_y < 0 || next_y >= arr.begin()->size() || arr[next_x][next_y] == 0)
		{
			dir = (dir + 1) % 4;
			next_x = x + shift[dir][0];
			next_y = y + shift[dir][1];
		}
		x = next_x;
		y = next_y;
	}
	return res;
}

pair<int, int> variant5(int n, int m) // rows cols
{
	if (n >= m)
	{
		if (m % 2 == 0)return make_pair(((m - 1) / 2) + 1, (m / 2) - 1);
		else return make_pair(n - 1 - (m / 2), m / 2);
	}
	else
	{
		if (n % 2 == 0)return make_pair(((n - 1) / 2) + 1, (n / 2) - 1);
		else return make_pair(n / 2, m - 1 - (n / 2));
	}
}

int variant6(const vector<vector<int>>&arr, int k)
{
	int cols = arr[0].size();
	int rows = arr.size();

	int level = 0;
	for (; ; ++level)
	{
		if (cols - 2 * level >= k)return arr[level][k - 1 + level]; // top
		else k -= cols - 2 * level;
		if (rows - 1 - 2 * level >= k)return arr[k + level][cols - 1 - level]; // right
		else k -= rows - 1 - 2 * level;
		if (cols - 1 - 2 * level >= k)return arr[rows - 1 - level][cols - 1 - k - level]; // bottom
		else k -= cols - 1 - 2 * level;
		if (rows - 2 - 2 * level >= k)return arr[rows - 1 - level - k][level]; // left
		else k -= rows - 2 - 2 * level;
	}
	return -1;
} // time O(c) c -number of outer rings, space O(1)

void test_spiral();
void test_variant1();
void test_variant2();
void test_variant3();
void test_variant4();
void test_variant5();
void test_variant6();
vector<vector<int>> fill(int rows, int cols);

void main()
{
	test_spiral();
	test_variant1();
	test_variant2();
	test_variant3();
	test_variant4();
	test_variant5();
	test_variant6();
	system("pause");
}

void test_spiral()
{
	const int n = 7;
	vector<vector<int>>arr(n, vector<int>(n));

	int i = 1;
	for (auto iter = arr.begin(); iter != arr.end(); ++iter)
	{
		iota(iter->begin(), iter->end(), i);
		i += iter->size();
	}


	for (auto iter = arr.begin(); iter != arr.end(); ++iter)
	{
		copy(iter->begin(), iter->end(), ostream_iterator<int>{cout, "    " });
		cout << endl;
	}

	spiral_second(arr);
	cout << endl;
	spiral(arr);
	cout << endl;
}

void test_variant1()
{
	const int d = 4;
	auto res = variant1(d);
	for (auto iter = res.begin(); iter != res.end(); ++iter)
	{
		copy(iter->begin(), iter->end(), ostream_iterator<int>{cout, "    " });
		cout << endl;
	}
}

void test_variant2()
{
	vector<int>seq{ 1,2,3,4,5,6,7,8,9 };
	auto res = variant2(seq);
	for (auto i = res.begin(); i < res.end(); ++i)
	{
		copy(i->begin(), i->end(), ostream_iterator<int>{ cout, " " });
		cout << endl;
	}
}

void test_variant3()
{
	variant3(10);
}

void test_variant4()
{
	int rows = 1;
	int cols = 10;
	vector<vector<int>>arr(rows, vector<int>(cols));
	int i = 1;
	for (auto iter = arr.begin(); iter != arr.end(); ++iter)
	{
		iota(iter->begin(), iter->end(), i);
		i += arr[0].size();
	}
	for (auto iter = arr.begin(); iter != arr.end(); ++iter)
	{
		copy(iter->begin(), iter->end(), ostream_iterator<int>{cout, "    " });
		cout << endl;
	}
	variant4(arr);
}

void test_variant5()
{
	assert(variant5(10, 1).first == 9 && variant5(10, 1).second == 0);
	assert(variant5(10, 2).first == 1 && variant5(10, 2).second == 0);
	assert(variant5(10, 3).first == 8 && variant5(10, 3).second == 1);
	assert(variant5(10, 4).first == 2 && variant5(10, 4).second == 1);
	assert(variant5(10, 5).first == 7 && variant5(10, 5).second == 2);

	assert(variant5(1, 1).first == 0 && variant5(1, 1).second == 0);
	assert(variant5(2, 2).first == 1 && variant5(2, 2).second == 0);
	assert(variant5(3, 3).first == 1 && variant5(3, 3).second == 1);
	assert(variant5(4, 4).first == 2 && variant5(4, 4).second == 1);

	assert(variant5(1, 10).first == 0 && variant5(1, 10).second == 9);
	assert(variant5(2, 10).first == 1 && variant5(2, 10).second == 0);
	assert(variant5(3, 10).first == 1 && variant5(3, 10).second == 8);
	assert(variant5(4, 10).first == 2 && variant5(4, 10).second == 1);
	assert(variant5(5, 10).first == 2 && variant5(5, 10).second == 7);
}

void test_variant6()
{
	auto a = fill(4, 4);
	cout << variant6(a, 16) << endl;
	for (int i = 1; i <= 32; ++i)
	{
		for (int j = 1; j <= 32; ++j)
		{
				auto arr = fill(i, j);
				auto check = variant4(arr);
				vector<int>res{};
				for (int k = 1; k <= i*j; ++k)
				{
					res.emplace_back(variant6(arr, k));
				}
				assert(equal(check.begin(), check.end(), res.begin(), res.end()));
		}
	}
}

vector<vector<int>> fill(int rows, int cols)
{
	vector<vector<int>>arr(rows, vector<int>(cols));
	int i = 1;
	for (auto iter = arr.begin(); iter != arr.end(); ++iter)
	{
		iota(iter->begin(), iter->end(), i);
		i += arr[0].size();
	}
	//for (auto iter = arr.begin(); iter != arr.end(); ++iter)
	//{
	//	copy(iter->begin(), iter->end(), ostream_iterator<int>{cout, "    " });
	//	cout << endl;
	//}
	return arr;
}