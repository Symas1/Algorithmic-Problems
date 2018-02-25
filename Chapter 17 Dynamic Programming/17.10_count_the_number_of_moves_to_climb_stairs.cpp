// count the number of moves to climb stairs
#include <vector>
#include <assert.h>
#include <algorithm>
#include <iostream>
using namespace std;

int stairs_helper(vector<int>&ways, const int n, const int k);
int stairs(const int n, const int k) {
	vector<int>ways(n + 1, 0);
	return stairs_helper(ways, n, k);
} // time O(nk); space O(n)
int stairs_helper(vector<int>&ways, const int n, const int k) {
	if (n <= 1) {
		return 1;
	}

	if (ways[n] == 0) {
		for (int i = 1; i <= k&&n-i>=0; ++i) {
			ways[n] += stairs_helper(ways, n - i, k);
		}
	}
	return ways[n];
}

void main() {
	assert(5 == stairs(4, 2));
	assert(1 == stairs(1, 2));
	assert(1 == stairs(0, 3));
	cout << stairs(4, 2) << endl;
	cout << stairs(5, 2) << endl;
	cout << stairs(20, 10) << endl;
	system("pause");
}