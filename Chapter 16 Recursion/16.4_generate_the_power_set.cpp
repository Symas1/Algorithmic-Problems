// power set
#include <vector>
#include <iostream>
#include <assert.h>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <unordered_map>
#include <random>
using namespace std;

void recursive_power_set_helper(vector<vector<int>>&result, const vector<int>&numbers, 
	vector<int>&currently_selected, int select);
vector<vector<int>> recursive_power_set(const vector<int>&numbers) {
	vector<vector<int>>result{};
	vector<int>currently_selected;
	recursive_power_set_helper(result, numbers, currently_selected,0);
	return result;
} // time O(n2^n); space O(n2^n)
void recursive_power_set_helper(vector<vector<int>>&result, const vector<int>&numbers,
	vector<int>&currently_selected, int select) {
	if (select==numbers.size()) {
		result.emplace_back(currently_selected);
		return;
	}

	currently_selected.emplace_back(numbers[select]);
	recursive_power_set_helper(result, numbers, currently_selected, select + 1);
	currently_selected.pop_back();
	recursive_power_set_helper(result, numbers, currently_selected, select + 1);
}

vector<vector<int>> iterative_power_set(const vector<int>&numbers) {
	vector<vector<int>>result;
	for (int i = 0; i < (1 << numbers.size()); ++i) {
		vector<int>new_set;
		int i_copy = i;
		while (i_copy>0) {
			new_set.emplace_back(numbers[log2(i_copy&(~(i_copy - 1)))]);
			i_copy = i_copy&(i_copy - 1);
		}
		result.emplace_back(move(new_set));
	}
	return result;
} // time O(n2^n); space O(n2^n)

void power_set_duplicates_recursive_helper(vector<vector<int>>&result,const vector<int>&numbers, vector<int>&current_set, 
	int select);
vector<vector<int>>power_set_duplicates_recursive(vector<int>numbers) {
	vector<vector<int>>result;
	vector<int>current_set;

	sort(numbers.begin(), numbers.end());
	power_set_duplicates_recursive_helper(result,numbers, current_set, 0);

	return result;
} // time O(n*(n1+1)*(n2+1)*(nk+1)); space O(n*(n1+1)*(n2+1)*(nk+1)) + recursion O(n)
void power_set_duplicates_recursive_helper(vector<vector<int>>&result, const vector<int>&numbers, vector<int>&current_set,
	int select) {
	result.emplace_back(current_set);
	for (int i = select; i < numbers.size(); ++i) {
		if (i != select && numbers[i] == numbers[i - 1]) {
			continue;
		}
		current_set.emplace_back(numbers[i]);
		power_set_duplicates_recursive_helper(result, numbers, current_set, i + 1);
		current_set.pop_back();
	}
}

vector<vector<int>>power_set_duplicates_iterative(vector<int>numbers) {
	vector<vector<int>>result{ {} };

	sort(numbers.begin(), numbers.end());
	for (int i = 0; i < numbers.size();) {
		unsigned equal = 1;
		while ((i+equal<numbers.size())&&numbers[i + equal] == numbers[i]) {
			++equal;
		}
		auto res_size = result.size();
		for (int j = 0; j < res_size; ++j) {
			vector<int>current_set = result[j];
			for (int k = 0; k < equal; ++k) {
				current_set.emplace_back(numbers[i]);
				result.emplace_back(current_set);
			}
		}
		i += equal;
	}
	return result;
} // time O(n*(n1+1)*(n2+1)*(nk+1)); space O(n*(n1+1)*(n2+1)*(nk+1))

void test_main();
void test_variant();
vector<int> random_set_with_duplicates(const int size);

void main() {
	test_main();
	test_variant();
	system("pause");
}

void test_main() {
	for (int i = 0; i < 10; ++i) {
		vector<int>numbers(i);
		iota(numbers.begin(), numbers.end(), 0);
		auto res1 = iterative_power_set(numbers);
		auto res2 = recursive_power_set(numbers);
		sort(res1.begin(), res1.end());
		sort(res2.begin(), res2.end());
		assert(equal(res1.begin(), res1.end(), res2.begin(), res2.end()));
	}
}

void test_variant() {
	for (int i = 0; i < 10; ++i) {
		auto vec = random_set_with_duplicates(i);
		auto res1 = power_set_duplicates_iterative(vec);
		auto res2 = power_set_duplicates_recursive(vec);
		sort(res1.begin(), res1.end());
		sort(res2.begin(), res2.end());
		assert(equal(res1.begin(), res1.end(), res2.begin(), res2.end()));
	}
}

vector<int> random_set_with_duplicates(const int size) {
	mt19937 mt{ random_device{}() };
	vector<int>result(size);
	for (int i = 0; i < size; ++i) {
		result[i] = uniform_int_distribution<>{ 1,size / 2 + 1 }(mt);
	}
	return result;
}