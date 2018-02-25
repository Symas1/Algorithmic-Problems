// find the longest nondecreasing subsequence
#include <vector>
#include <iostream>
#include <assert.h>
#include <functional>
#include <algorithm>
using namespace std;

int longest(const vector<int>sequence) {
	vector<int>longest_subsequence(sequence.size(),1); // length, biggest element
	for (int i = 1; i < sequence.size(); ++i) {
		for (int j = 0; j < i; ++j) {
			if (sequence[j] <= sequence[i]) {
				longest_subsequence[i] = max(longest_subsequence[i], longest_subsequence[j] + 1);
			}
		}
	}
	return longest_subsequence.back();
} // time O(n^2); space O(n)

void main() {
	vector<int>seq{ 0,8,4,12,2,10,6,14,1,9 };
	cout << longest(seq) << endl;
	system("pause");
}