
#include <string>
#include <random>
#include <assert.h>
#include <iostream>
#include <unordered_map>
using namespace std;

bool interleave_rec_helper(const string& a, const string& b, const string&c, int a_it, int b_it);
bool interleave_rec(const string& a, const string& b, const string&c) {
	if (a.size() + b.size() != c.size()) {
		return false;
	}
	return interleave_rec_helper(a, b, c, 0, 0);
} // time O(2^n); space O(c.size()) - recursion
bool interleave_rec_helper(const string& a, const string& b, const string&c, int a_it, int b_it) {
	auto c_it = a_it + b_it;
	if (c_it == c.size()) {
		return true;
	}
	bool res1 = false;
	bool res2 = false;
	if (a_it < a.size() && c[c_it] == a[a_it]) {
		res1 = interleave_rec_helper(a, b, c, a_it + 1, b_it);
		if (res1) {
			return true;
		}
	}
	if (b_it < b.size() && c[c_it] == b[b_it]) {
		res2 =interleave_rec_helper(a, b, c, a_it, b_it + 1);
	}
	return res2;
}

struct My_hash {
	size_t operator()(const pair<int, int>&a)const {
		return hash<int>{}(a.first ^ (a.second * 997));
	}
};

using Hash = unordered_map<pair<int, int>, bool, My_hash>;

bool interleave_recursive_mem_helper(Hash& cache, const string& a, const string& b, const string& c, int a_it, int b_it);

bool interleave_recursive_mem(const string& a, const string& b, const string& c) {
	if (a.size() + b.size() != c.size()) {
		return false;
	}
	Hash cache;
	return interleave_recursive_mem_helper(cache, a, b, c, 0, 0);
} // time O(n^2); space O(n^2)

bool interleave_recursive_mem_helper(Hash& cache, const string& a, const string& b, const string& c, int a_it, int b_it) {
	if (a_it + b_it >= c.size()) {
		return true;
	}
	if (cache.count({ a_it,b_it })) {
		return cache.at({ a_it,b_it });
	}
	auto c_it = a_it + b_it;
	if (a_it < a.size() && c[c_it] == a[a_it]) {
		auto result = interleave_recursive_mem_helper(cache, a, b, c, a_it + 1, b_it);
		cache.emplace(pair<int, int>{a_it, b_it}, result);
		if (result) {
			return result;
		}
	}
	if (b_it < b.size() && c[c_it] == b[b_it]) {
		auto result = interleave_recursive_mem_helper(cache, a, b, c, a_it, b_it + 1);
		cache[pair<int, int>{a_it, b_it}] = result;
		return result;
	}

	cache.emplace(pair<int, int>{a_it, b_it}, false);
	return false;
}

bool interleave_dp(const string& a, const string& b, const string& c) {
	if (a.size() + b.size() != c.size()) {
		return false;
	}
	vector<vector<bool>>arr(a.size() + 1, vector<bool>(b.size() + 1));
	arr[0][0] = true;
	// first row
	for (int i = 1; i < arr.front().size();++i) {
		if (b[i - 1] == c[i - 1]) {
			arr[0][i] = arr[0][i - 1];
		}
		else {
			arr[0][i] = false;
		}
	}
	// first column
	for (int i = 1; i < arr.size(); ++i) {
		if (a[i - 1] == c[i - 1]) {
			arr[i][0] = arr[i - 1][0];
		}
		else {
			arr[i][0] = false;
		}
	}

	for (int i = 1; i < arr.size(); ++i) {
		for (int j = 1; j < arr[i].size(); ++j) {
			if (a[i - 1] == c[i + j - 1] && b[j - 1] == c[i + j - 1]) {
				arr[i][j] = arr[i][j - 1] || arr[i-1][j];
			}
			else if(a[i - 1] == c[i + j - 1]){
				arr[i][j] = arr[i - 1][j];
			}
			else if (b[j - 1] == c[i + j - 1]) {
				arr[i][j] = arr[i][j - 1];
			}
			else {
				arr[i][j] = false;
			}
		}
	}
	return arr.back().back();
} // time O(n^2); space O(n^2)

string generate_inerleaving_string(const string& a, const string&b) {
	mt19937 mt{ random_device{}() };
	string result(a.size() + b.size(), '\0');
	auto a_it = 0;
	auto b_it = 0;
	int i = 0;
	for (;a_it<a.size() && b_it<b.size()&& i < result.size(); ++i) {
		bool choose_a = uniform_int_distribution<>{ 0,1 }(mt);
		if (choose_a) {
			result[i] = a[a_it++];
		}
		else {
			result[i] = b[b_it++];
		}
	}
	while (a_it != a.size()) {
		result[i++] = a[a_it++];
	}
	while (b_it != b.size()) {
		result[i++] = b[b_it++];
	}
	return result;
}

string random_string(const unsigned size) {
	mt19937 mt{ random_device{}() };
	string result(size, '\0');
	for (int i = 0; i < result.size(); ++i) {
		result[i] = uniform_int_distribution<>{ 'a','c' }(mt);
	}
	return result;
}

void golden_test();
void test();

void main() {
	interleave_dp("a", "ca", "1aa");
	//golden_test();
	test();

	system("pause");
}

void golden_test() {
	assert(interleave_recursive_mem("xzy", "abcd", "xabzcyd"));
	assert(interleave_recursive_mem("aaa", "aaaa", "aaaaaaa"));
	assert(interleave_rec("xzy", "abcd", "xabzcyd"));
	assert(interleave_rec("aaa", "aaaa", "aaaaaaa"));
	assert(interleave_dp("xzy", "abcd", "xabzcyd"));
	assert(interleave_dp("aaa", "aaaa", "aaaaaaa"));
}

void test() {
	mt19937 mt{ random_device{}() };

	for (int times = 0; times < 1000; ++times) {
		cout << times << '\n';
		auto str1 = random_string(uniform_int_distribution<>{1, 100}(mt));
		auto str2 = random_string(uniform_int_distribution<>{1, 100}(mt));
		auto str3 = generate_inerleaving_string(str1, str2);
		if (uniform_int_distribution<>{ 0, 1 }(mt)) {
			str3[uniform_int_distribution<>(0, str3.size() - 1)(mt)] = '1';
		}
		//auto res_exp = interleave_rec(str1, str2, str3);
		auto res_rec_mem = interleave_recursive_mem(str1, str2, str3);
		auto res_dp = interleave_dp(str1, str2, str3);
		//assert(res_exp == res_rec_mem);
		assert(res_rec_mem == res_dp);
	}
}