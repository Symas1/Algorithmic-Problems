
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <iterator>
#include <numeric>
using namespace std;

int egg_drop(const int floor, const int eggs) {
	if (floor == 0 || floor == 1 || eggs==1) {
		return floor;
	}
	
	int m = numeric_limits<int>::max();
	for (int i = 1; i <= floor; ++i) {
		auto res = max(egg_drop(i-1, eggs - 1), egg_drop(floor - i, eggs));
		m = min(m, res);
	}
	return m + 1;
} // time O(exponential); space O(floor)

int egg_drop_mem_helper(vector<int>&cache,const int floor, const int eggs);
int egg_drop_mem(const int floor, const int eggs) {
	if (floor == 0) {
		return 0;
	}
	vector<int>cache(floor+1, -1);
	cache[0] = 0;
	cache[1] = 1;
	return egg_drop_mem_helper(cache, floor, eggs);
} // works only for 2 eggs case
int egg_drop_mem_helper(vector<int>&cache, const int floor, const int eggs) {
	if (eggs == 1) {
		return floor;
	}
	if (cache[floor]!=-1) {
		return cache[floor];
	}

	int m = numeric_limits<int>::max();
	for (int i = 1; i <= floor; ++i) {
		auto res = max(egg_drop_mem_helper(cache, i-1, eggs-1), egg_drop_mem_helper(cache, floor - i, eggs));
		m = min(m, res);
	}
	cache[floor] = m + 1;
	return cache[floor];
}

int egg_drop_dp(const int floor, const int eggs) {
	if (floor == 0) {
		return 0;
	}
	vector<vector<int>>arr(eggs, vector<int>(floor + 1, 0));
	for (int i = 1; i < arr.front().size();++i) {
		arr[0][i] = i;
	}

	for (int egg = 1; egg < arr.size(); ++egg) {
		for (int col = 1; col < arr[egg].size(); ++col) {
			int value = numeric_limits<int>::max();
			for (int curr_floor = 1; curr_floor <= col; ++curr_floor) {
				value = min(value, max(arr[egg - 1][curr_floor - 1], arr[egg][col - curr_floor]));
			}
			arr[egg][col] = value+1;
		}
	}
	return arr.back().back();
} // time O(eggs * floors^2); space O(eggs * floors)

int egg_drop_dp_better(const int floor, const int eggs) {
	if (floor == 0) {
		return 0;
	}
	vector<vector<int>>arr(2, vector<int>(floor + 1, 0));
	for (int i = 1; i < arr.front().size(); ++i) {
		arr[0][i] = i;
	}

	for (int row = 1; row < eggs; ++row) {
		for (int col = 1; col < arr[1].size(); ++col) {
			int value = numeric_limits<int>::max();
			for (int k = 1; k <= col; ++k) {
				value = min(value, max(arr[0][k - 1], arr[1][col - k]));
			}
			arr[1][col] = value + 1;
		}
		swap(arr[0], arr[1]);
	}
	return arr.front().back();
} // time O(eggs * floors^2); space O(floors)

unsigned egg_drop_dp_sclo(const unsigned floors, const unsigned eggs) {
	if (eggs == 1 || floors == 0) {
		return floors;
	}
	vector<unsigned>tries(floors + 1);
	iota(tries.begin(), tries.end(), 0);
	unsigned idx = 0;
	for (int i = 1; i < eggs; ++i) {
		unsigned diagonal = tries[0];
		for (int j = 1; j < tries.size(); ++j) {
			unsigned save = tries[j];
			tries[j] = tries[j-1] + diagonal + 1;
			if (tries[j] >= floors) {
				idx = j;
				break;
			}
			diagonal = save;
		}
	}
	return idx;
} // time O(eggs*floors); space O(floors)


int n_choose_k2(const int n, int k) {
	int res = 0;
	int aux = 1;
	for (double i = 1; i <= k && i <= n; ++i) {
		aux *= (n - (i - 1)) / i;
		res += aux;
	}
	return res;
} // time O(k); space O(1)

int egg_drop_n_logk2(const int floors, const int eggs) {
	if (floors == 0 || eggs == 1) {
		return floors;
	}

	int bottom = 1;
	int up = floors;
	while (up - bottom >1) {
		int middle = bottom + (up - bottom) / 2;
		int result = n_choose_k2(middle, eggs);
		if (result >= floors) {
			up = middle;
		}
		else {
			bottom = middle;
		}
	}
	return up;
} // time (eggs*log(floors)); space O(1)

void test();


void main() {
	test();
	system("pause");
}

void test() {
	for (int i = 0; i < 15; ++i) {
		auto res1 = egg_drop(i, 2);
		auto res2 = egg_drop_mem(i, 2);
		auto res3 = egg_drop_dp(i, 2);
		auto res4 = egg_drop_dp_better(i, 2);
		auto res5 = egg_drop_n_logk2(i, 2);
		auto res6 = egg_drop_dp_sclo(i, 2);
		assert(res1 == res2);
		assert(res2 == res3);
		assert(res3 == res4);
		assert(res5 == res4);
		assert(res6 == res5);
	}
	for (int eggs = 1; eggs <5; ++eggs) {
		for (int floors = 0; floors <= 100; ++floors) {
			cout << "Eggs: " << eggs << "\tFloors: " << floors << '\n';
			auto res3 = egg_drop_dp_sclo(floors, eggs);
			auto res4 = egg_drop_dp_better(floors, eggs);
			auto res6 = egg_drop_n_logk2(floors, eggs);
			cout <<"res3: "<<res3<< "\tres5: " << res4 << "\tres6: " << res6 << '\n';
			assert(res4 == res6);
			assert(res3 == res6);
		}
	}
}