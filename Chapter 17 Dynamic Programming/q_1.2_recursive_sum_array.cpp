#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;

void update(vector<int>&arr, size_t index) {
	if (index >= arr.size()) {
		return;
	}
	arr[index] = index == 0 ? arr[index] : arr[index] + arr[index - 1];
	update(arr, index + 1);
} // time O(n); space O(n) - recursion

void main() {
	vector<int>arr{ 1,2,3,4,5,6 };
	copy(arr.begin(), arr.end(), ostream_iterator<int>{cout, " "});
	cout << endl;
	update(arr, 0);
	copy(arr.begin(), arr.end(), ostream_iterator<int>{cout, " "});
	cout << endl;
	system("pause");
}