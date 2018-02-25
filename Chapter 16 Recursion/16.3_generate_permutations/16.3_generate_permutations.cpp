// generate permutations for sequences with duplicates and without duplicates
#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <iterator>
#include <random>
#include <unordered_set>
using namespace std;

void perm_helper(vector<vector<int>>&result, vector<int>&numbers, int depth);
vector<vector<int>> perm(vector<int>numbers) {
	vector<vector<int>>result;
	perm_helper(result, numbers, 0);
	return result;
} // time O(n!*n); space O(n) - for recursion
void perm_helper(vector<vector<int>>&result, vector<int>&numbers, int depth) {
	if (depth == numbers.size()) {
		result.emplace_back(numbers);
		return;
	}
	for (int i = depth; i < numbers.size(); ++i) {
		swap(numbers[i], numbers[depth]);
		perm_helper(result, numbers, depth + 1);
		swap(numbers[i], numbers[depth]);
	}
}

vector<vector<int>>perm2(vector<int>numbers) {
	sort(numbers.begin(), numbers.end());
	vector<vector<int>>result;
	do {
		result.emplace_back(numbers);
	} while (next_permutation(numbers.begin(), numbers.end()));
	return result;
} // // time O(n!/(n1!*n2!*...*nk!)*2n); space O(1)

vector<int> rand_vector_unique(size_t size) {
	mt19937 mt{ random_device{}() };
	vector<int>result(size, 0);
	unordered_set<int>used;
	for (int i = 0; i < size; ++i) {
		int new_num = uniform_int_distribution<>{ numeric_limits<int>::min(),numeric_limits<int>::max() }(mt);
		if (used.emplace(new_num).second == false) {
			--i;
			continue;
		}
		result[i] = new_num;
	}
	return result;
}
vector<int> rand_vector(size_t size) {
	mt19937 mt{ random_device{}() };
	vector<int>result(size, 0);
	for (int i = 0; i < size; ++i) {
		int new_num = uniform_int_distribution<>{ 0,4 }(mt);
		result[i] = new_num;
	}
	return result;
}


void variant1_helper(vector<vector<int>>&result, vector<int>&numbers, int depth);
vector<vector<int>> variant1(vector<int>numbers) {
	vector<vector<int>>result;
	variant1_helper(result, numbers, 0);
	return result;
} // time O(n!/(n1!*n2!*...*nk!)*n); space(n^2)
void variant1_helper(vector<vector<int>>&result, vector<int>&numbers, int depth) {
	if (depth == numbers.size()) {
		result.emplace_back(numbers);
		return;
	}
	int equal_counter = 0;
	unordered_set<int>used;
	for (int i = depth; i < numbers.size(); ++i) {
		if (!used.emplace(numbers[i]).second) {
			continue;
		}
		swap(numbers[i], numbers[depth]);
		variant1_helper(result, numbers, depth + 1);
		swap(numbers[i], numbers[depth]);
	}
}

void var11_helper(vector<vector<int>>&result, vector<int>&numbers, int depth);
vector<vector<int>> var11(vector<int>numbers) {
	vector<vector<int>>result;
	var11_helper(result, numbers, 0);
	return result;
} // time O(n!*n^3); space O(n) - recursion
void var11_helper(vector<vector<int>>&result, vector<int>&numbers, int depth) {
	if (depth == numbers.size()) {
		result.emplace_back(numbers);
		return;
	}
	for (int i = depth; i < numbers.size(); ++i) {
		{
			bool found = false;
			for (int j = depth; j < i; ++j) {
				if (numbers[j] == numbers[i]) {
					found = true;
					break;
				}
			}
			if (found) {
				continue;
			}
		}
		swap(numbers[i], numbers[depth]);
		var11_helper(result, numbers, depth + 1);
		swap(numbers[i], numbers[depth]);
	}
}

void heaps_algorithm_helper(vector<vector<int>>&result, vector<int>&numbers, int n);
vector<vector<int>> heaps_algorithm(vector<int>numbers) {
	if (numbers.empty()) {
		return{ {} };
	}
	vector<vector<int>>result;
	heaps_algorithm_helper(result, numbers,numbers.size());
	return result;
} // time O(n!*n); space O(n) - recursion; swaps (n!-1)
void heaps_algorithm_helper(vector<vector<int>>&result, vector<int>&numbers, int n) {
	if (n == 1) {
		result.emplace_back(numbers);
		return;
	}

	for (int i = 0; i < n - 1; ++i) {
		heaps_algorithm_helper(result, numbers, n - 1);
		if (n % 2 == 0) {
			swap(numbers[i], numbers[n - 1]);
		}
		else {
			swap(numbers[0], numbers[n - 1]);
		}
	}
	heaps_algorithm_helper(result, numbers, n - 1);
}

void test_main();
void test_variant1();

void main() {
	test_main();
	test_variant1();
	system("pause");
}

void test_main() {
	// duplicates not allowed
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 100; ++times) {
		auto vec = rand_vector_unique(uniform_int_distribution<>{0, 5}(mt));
		auto res1 = perm(vec);
		auto res2 = perm2(vec);
		auto res3 = heaps_algorithm(vec);
		sort(res1.begin(), res1.end());
		sort(res2.begin(), res2.end());
		sort(res3.begin(), res3.end());
		assert(equal(res1.begin(), res1.end(), res2.begin(), res2.end()));
		assert(equal(res1.begin(), res1.end(), res3.begin(), res3.end()));
	}
}

void test_variant1() {
	// duplicates allowed
	// 2,2,2,2
	{
		vector<vector<int>>golden_res{ {2,2,2,2} };
		vector<int>res{ 2,2,2,2 };
		auto res1 = variant1(res);
		auto res2 = perm2(res);
		auto res3 = var11(res);
		assert(equal(res1.begin(), res1.end(), golden_res.begin(), golden_res.end()));
		assert(equal(res2.begin(), res2.end(), golden_res.begin(), golden_res.end()));
		assert(equal(res3.begin(), res3.end(), golden_res.begin(), golden_res.end()));
	}
	// 2,2,3,0
	{
		vector<vector<int>>golden_res{ {2,2,3,0},{2,2,0,3},{2,0,2,3},{2,0,3,2},{2,3,2,0},{2,3,0,2},{0,2,2,3},
		{0,2,3,2},{0,3,2,2},{3,2,2,0},{3,2,0,2},{3,0,2,2} };
		sort(golden_res.begin(), golden_res.end());
		vector<int>vec{ 2,2,3,0 };
		auto res1 = variant1(vec);
		auto res2 = perm2(vec);
		auto res3 = var11(vec);
		sort(res1.begin(), res1.end());
		sort(res2.begin(), res2.end());
		sort(res3.begin(), res3.end());
		assert(equal(res1.begin(), res1.end(), golden_res.begin(), golden_res.end()));
		assert(equal(res2.begin(), res2.end(), golden_res.begin(), golden_res.end()));
		assert(equal(res3.begin(), res3.end(), golden_res.begin(), golden_res.end()));
	}

	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 100; ++times) {
		auto vec = rand_vector(uniform_int_distribution<>{0, 5}(mt));
		auto res1 = variant1(vec);
		auto res2 = perm2(vec);
		auto res3 = var11(vec);
		sort(res1.begin(), res1.end());
		sort(res2.begin(), res2.end());
		sort(res3.begin(), res3.end());
		assert(equal(res1.begin(), res1.end(), res2.begin(), res2.end()));
		assert(equal(res2.begin(), res2.end(), res3.begin(), res3.end()));
	}
}