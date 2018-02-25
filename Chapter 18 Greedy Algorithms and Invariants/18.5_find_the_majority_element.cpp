// find the majority element
#include <string>
#include <assert.h>
#include <iostream>
#include <random>
#include <unordered_map>
#include <algorithm>
using namespace std;

char majority(const string& str) {
	if (str.empty()) {
		return '\0';
	}
	char majority = {};
	int cnt = 0;
	for (const auto c : str) {
		if (cnt == 0) {
			majority = c;
			cnt = 1;
		}
		else if (c == majority) {
			++cnt;
		}
		else {
			--cnt;
		}
	}
	return majority;
} // time O(n); space O(1)

char majority_hash(const string&str) {
	if (str.empty()) {
		return '\0';
	}
	unordered_map<char, int>map{ {str[0],0} };
	char majority = str[0];
	int cnt = 0;
	for (const auto c : str) {
		++map[c];
		if (map[c] > cnt) {
			cnt = map[c];
			majority = c;
		}
	}
	return majority;
} // time O(n); space O(n)

void small_test() {
	string str{ "bacaabaaca" };
	assert(majority(str) == 'a'&&majority_hash(str) == 'a');
	str = "";
	assert(majority(str) == '\0'&&majority_hash(str) == '\0');
}

string rand_str_with_majority(int size) {
	string res( size,{} );
	mt19937 mt{ random_device{}() };
	char majority = uniform_int_distribution<>{ 'a','z' }(mt);
	int majority_number = uniform_int_distribution<>{ (size + 2) / 2,size }(mt);
	fill_n(res.begin(), majority_number, majority);
	generate(res.begin() + majority_number, res.end(), [&mt]() {
		return uniform_int_distribution<>{'a', 'z'}(mt);
	});
	shuffle(res.begin(), res.end(), mt);
	return res;
}

void main() {
	small_test();
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 1000; ++i) {
		auto str = rand_str_with_majority(uniform_int_distribution<>{1, 100}(mt));
		assert(majority(str) == majority_hash(str));
	}
	system("pause");
}