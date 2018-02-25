// subsets of size k
#include<vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <assert.h>
using namespace std;

void subsets_helper(vector<vector<int>>&result,vector<int>&new_vec, int n, int k, int current);
vector<vector<int>> subsets_recursive(int n,int k){
	if (n == 0 || k > n) {
		return{ {} };
	}

	vector<vector<int>>result;
	vector<int>new_vec;
	subsets_helper(result, new_vec, n, k, 1);
	return result;
} // time O(k*C(k,n)); space O(C(k,n)*k)
void subsets_helper(vector<vector<int>>&result, vector<int>&new_vec, int n, int k, int current) {
	if (new_vec.size() == k) {
		result.emplace_back(new_vec);
		return;
	}
	for (int i = current; n - i + 1 >= k - new_vec.size(); ++i) {
		new_vec.emplace_back(i);
		subsets_helper(result, new_vec, n, k, i + 1);
		new_vec.pop_back();
	}
}

//vector<vector<int>> subsets_iterative(int n, int k) {
//	vector<vector<int>>result;
//	for (int i = 0; n - i >= k;++i) {
//		for (int start = i + 1; n - start >= k - 1; ++start) {
//			result.emplace_back(vector<int>{i + 1});
//			for (int j = 0; j < k - 1; ++j) {
//				result.back().emplace_back(start + j+1);
//			}
//		}
//	}
//	return result;
//}

void main() {
	auto res = subsets_recursive(5, 3);
	for (auto iter = res.begin(); iter != res.end(); ++iter) {
		copy(iter->begin(), iter->end(), ostream_iterator<int>{cout, " "});
		cout << endl;
	}
	system("pause");
}