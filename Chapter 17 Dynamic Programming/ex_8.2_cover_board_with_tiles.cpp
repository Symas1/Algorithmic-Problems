// cover the 2xn board with tiles 1x2 and 2x1
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

unsigned cover_recursive(unsigned n) {
	if (n == 0 || n == 1 || n == 2) {
		return n;
	}
	unsigned vertical_tile = cover_recursive(n - 1);
	unsigned horizontal_tiles =  cover_recursive(n - 2);
	return vertical_tile + horizontal_tiles;
} // time O(2^n); space O(n) for recursion

void cover_recursive_mem_helper(vector<unsigned>&covered, unsigned n);
unsigned cover_recursive_mem(unsigned n) {
	if (n == 0 || n == 1 || n == 2) {
		return n;
	}
	vector<unsigned>covered(n+1, 0);
	covered[0] = 0;
	covered[1] = 1;
	covered[2] = 2;
	cover_recursive_mem_helper(covered, n);
	return covered.back();
} // time O(n^2); space O(n) for recursion + O(n) for array
void cover_recursive_mem_helper(vector<unsigned>&covered, unsigned n) {
	if (n <= 2 || covered[n]!=0) {
		return;
	}
	cover_recursive_mem_helper(covered, n - 1);
	cover_recursive_mem_helper(covered, n - 2);
	covered[n] = covered[n - 1] + covered[n - 2];
}

unsigned cover_dp(unsigned n) {
	if (n == 0 || n == 1 || n == 2) {
		return n;
	}
	unsigned n_1 = 2;
	unsigned n_2 = 1;
	for (int i = 3; i <= n; ++i) {
		unsigned n = n_1 + n_2;
		n_2 = n_1;
		n_1 = n;
	}
	return n_1;
} // time O(n); space O(1)

void main() {
	// as recurrence relation T(n)=T(n-1)+T(n-2) for T(0)=1 and T(1)=1 we see that this is Fibonacci numbers
	// we can further improve algorithms to complexities: time O(logn), space O(1); time(1), space O(1)
	for (int i = 0; i < 10; ++i) {
		auto res1 = cover_recursive(i);
		auto res2 = cover_recursive_mem(i);
		auto res3 = cover_dp(i);
		assert(res1 == res2);
		assert(res2 == res3);
	}
	system("pause");
}