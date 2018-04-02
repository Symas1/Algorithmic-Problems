
#include <string>
#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

void all_interleavings_helper(vector<string>&result, const string& current, const string& a, const string&b,
	int a_it, int b_it);
vector<string> all_interleavings(const string& a, const string& b) {
	vector<string>result;
	all_interleavings_helper(result, "", a, b, 0, 0);
	return result;
}
void all_interleavings_helper(vector<string>&result, const string& current, const string& a, const string&b,
	int a_it, int b_it) {
	if (a_it + b_it == a.size() + b.size()) {
		result.emplace_back(current);
		return;
	}

	if (a_it < a.size() && b_it < b.size()) {
		if (a[a_it] == b[b_it]) {
			all_interleavings_helper(result, current + a[a_it]+b[b_it], a, b, a_it + 1, b_it+1);
			return;
		}
	}

	if (a_it < a.size()) {
		all_interleavings_helper(result, current + a[a_it], a, b, a_it + 1, b_it);
	}
	if (b_it < b.size()) {
		all_interleavings_helper(result, current + b[b_it], a, b, a_it, b_it + 1);
	}
} // time O(n2^n); space O(a.size()+b.size()) - recursion

void main() {
	auto res = all_interleavings("AB", "XY");
	sort(res.begin(), res.end());
	vector<string>golden_res{ "ABXY","AXBY","AXYB","XYAB","XAYB","XABY" };
	sort(golden_res.begin(), golden_res.end());
	assert(equal(res.begin(), res.end(), golden_res.begin(), golden_res.end()));
	auto res2 = all_interleavings("BB", "BB");
	assert(res2.size() == 1 && res2[0] == "BBBB");
	system("pause");
}