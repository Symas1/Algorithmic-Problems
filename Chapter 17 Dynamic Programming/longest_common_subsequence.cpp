
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <random>
using namespace std;

void print_lsc(const vector < vector<unsigned>>&lsc, const string&a, const string&b);

void lca_recursive(const string& a, const string&b, const unsigned a_it, const unsigned b_it,
	unsigned& answer, unsigned curr_lca);
unsigned lca_recursive(const string&a, const string&b) {
	unsigned answer = 0;
	lca_recursive(a, b, 0, 0, answer, 0);
	return answer;
} // time O(2^n); space O(a.size()+b.size()) for recursion
void lca_recursive(const string& a, const string&b, const unsigned a_it, const unsigned b_it,
	unsigned& answer, unsigned curr_lca) {
	if (curr_lca > answer) {
		answer = curr_lca;
	}
	if (a_it >= a.size() || b_it >= b.size()) {
		return;
	}

	if (a[a_it] == b[b_it]) {
		lca_recursive(a, b, a_it + 1, b_it + 1, answer, curr_lca + 1);
		return;
	}

	lca_recursive(a, b, a_it + 1, b_it, answer, curr_lca);
	lca_recursive(a, b, a_it, b_it + 1, answer, curr_lca);
}

unsigned lca_dp(const string& a, const string&b) {
	vector<vector<unsigned>>lca(a.size() + 1, vector<unsigned>(b.size() + 1, 0));
	for (int i = 1; i < lca.size(); ++i) {
		for (int j = 1; j < lca[i].size(); ++j) {
			if (a[i - 1] == b[j - 1]) {
				lca[i][j] = lca[i - 1][j - 1] + 1;
			}
			else {
				lca[i][j] = max({ lca[i - 1][j],lca[i][j - 1] });
			}
		}
	}
	print_lsc(lca, a, b);
	return lca.back().back();
} // time O(n*m); space O(n*m)

unsigned lca_dp_better(const string&a, const string&b) {
	if (a.size() == 0 || b.size() == 0) {
		return 0;
	}
	bool a_smaller = a.size() <= b.size() ? true : false;
	const string real_a = a_smaller ? a : b;
	const string real_b = a_smaller ? b : a;

	vector<unsigned> lca(real_a.size()+1, 0);

	for (int i = 0; i < real_b.size(); ++i) {
		unsigned diagonal = lca.front();
		for (int j = 1; j < lca.size(); ++j) {
			unsigned diagonal_save = lca[j];
			if (real_a[j-1] == real_b[i]) {
				lca[j] = diagonal + 1;
			}
			else {
				lca[j] = max({ lca[j - 1],lca[j]});
			}
			diagonal = diagonal_save;
		}
	}
	return lca.back();
} // time O(n*m); space O(min(n,m))

void print_lsc(const vector < vector<unsigned>>&lsc,const string&a,const string&b) {
	int i = lsc.size() - 1;
	int j = lsc[i].size() - 1;
	while (i > 0 && j > 0) {
		if (a[i - 1] == b[j - 1]) {
			cout << a[i - 1];
			--i;
			--j;
		}
		else {
			if (lsc[i - 1][j] > lsc[i][j - 1]) {
				--i;
			}
			else {
				--j;
			}
		}
	}
	cout << endl;
} // time O(n+m); space O(1)

string random_str(const unsigned size) {
	mt19937 mt{ random_device{}() };
	string res(size, '\0');
	for (int i = 0; i < size; ++i) {
		res[i] = uniform_int_distribution<>{ 'A','D' }(mt);
	}
	return res;
}

void golden_test();
void test();

void main() {
	golden_test();
	test();
	system("pause");
}

void golden_test() {
	assert(lca_recursive("ABCD", "AEBD") == 3);
	assert(lca_dp("ABCD", "AEBD") == 3);
	assert(lca_dp_better("ABCD", "AEBD") == 3);
}

void test() {
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 100; ++times) {
		auto str1 = random_str(uniform_int_distribution<>{0, 10}(mt));
		auto str2 = random_str(uniform_int_distribution<>{0, 10}(mt));

		auto res1 = lca_recursive(str1, str2);
		auto res2 = lca_dp(str1, str2);
		auto res3 = lca_dp_better(str1, str2);
		assert(res1 == res2);
		assert(res2 == res3);
	}
}