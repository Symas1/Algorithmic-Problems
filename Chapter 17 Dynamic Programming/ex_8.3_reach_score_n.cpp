// number of ways to reach score n (3,5,10 in one move)
#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;

unsigned number_of_ways(int n) {
	if (n < 0) {
		return 0;
	}
	if (n == 0) {
		return 1;
	}
	return number_of_ways(n - 3) +
		number_of_ways(n - 5) +
		number_of_ways(n - 10);
} // time O(3^n); space O(n) - for recursion

unsigned number_of_ways_dp(int n) {
	if (n == 0) {
		return 1;
	}
	vector<unsigned>arr(n + 1, 0);
	arr[0] = 1;
	for (int i = 1; i <= n; ++i) {
		if (i - 3 >= 0) {
			arr[i] += arr[i - 3];
		}
		if (i - 5 >= 0) {
			arr[i] += arr[i - 5];
		}
		if (i - 10 >= 0) {
			arr[i] += arr[i - 10];
		}
	}
	return arr.back();
} // time O(n); space O(n)

unsigned number_of_ways_no_repetitions(int n) {
	if (n == 0) {
		return 1;
	}
	vector<unsigned>ways(n + 1, 0);
	ways[0] = 1;
	vector<unsigned>nums{ 3,5,10 };
	for (const auto& num : nums) {
		for (int i = num; i < ways.size(); ++i) {
			ways[i] += ways[i - num];
		}
	}
	return ways.back();
} // time O(n); space O(n)

void main() {
	cout << number_of_ways(13) << endl;
	cout << number_of_ways_dp(13) << endl;
	cout << number_of_ways_no_repetitions(13) << endl;
	cout << find_arr({ -2,-3,4,-1,-2,1,5,-3 }) << endl;
	system("pause");
}