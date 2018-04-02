
#include <vector>
#include <iostream>
#include <assert.h>
using namespace std;

unsigned total_ways_no_dups(const vector<unsigned>&coins, const unsigned amount) {
	vector<unsigned>ways(amount + 1, 0);
	ways[0] = 1;
	for (const auto c : coins) {
		for (int i = c; i < ways.size(); ++i) {
			ways[i] = ways[i]+ways[i-c];
		}
	}
	return ways.back();
} // time O(amount*c); space O(amount)

unsigned total_ways_dups(const vector<unsigned>&coins, const unsigned amount) {
	vector<unsigned>ways(amount + 1, 0);
	ways[0] = 1;
	for (int i = 1; i < ways.size(); ++i) {
		for (const auto c : coins) {
			if (i - static_cast<int>(c) >= 0) {
				ways[i] += ways[i - c];
			}
		}
	}
	return ways.back();
} // time O(amount*c); space O(amount)

void main() {
	cout << total_ways_no_dups({ 1,2,3,4,5 }, 11) << endl;
	cout << total_ways_dups({ 1,2,3,4,5 }, 11) << endl;
	assert(total_ways_dups({ 1,2 }, 4) == 5);
	assert(total_ways_no_dups({ 1,2 }, 4) == 3);
	system("pause");
}