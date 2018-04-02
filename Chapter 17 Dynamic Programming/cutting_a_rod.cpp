
#include <vector>
#include <iostream>
#include <assert.h>
#include <random>
#include <algorithm>
#include <functional>
#include <memory>
#include <iterator>
#include <numeric>
using namespace std;

void cutting_rod_brute_helper(const vector<unsigned>&length,
	const vector<unsigned>&price, pair<vector<unsigned>, unsigned>&result,
	vector<unsigned>&curr_cuts, unsigned curr_price, unsigned curr_length);
pair<vector<unsigned>, unsigned> cutting_rod_brute(const vector<unsigned>&length,
	const vector<unsigned>&price) {
	pair<vector<unsigned>, unsigned>result{ {},0 };
	vector<unsigned>curr;
	cutting_rod_brute_helper(length, price, result,curr, 0, length.size());
	return result;
} // time exponential; space O(length)
void cutting_rod_brute_helper(const vector<unsigned>&length,
	const vector<unsigned>&price, pair<vector<unsigned>, unsigned>&result,
	vector<unsigned>&curr_cuts, unsigned curr_price,unsigned curr_length) {
	if (curr_length == 0 && curr_price > result.second) {
		result = { curr_cuts,curr_price };
	}
	for (int i = 0; i < length.size(); ++i) {
		if (length[i] <= curr_length) {
			curr_cuts.emplace_back(length[i]);
			cutting_rod_brute_helper(length, price, result, curr_cuts, curr_price + price[i],
				curr_length - length[i]);
			curr_cuts.pop_back();
		}
	}
}


pair<vector<unsigned>, unsigned> cutting_rod_dp(const vector<unsigned>&length, const vector<unsigned>&price) {
	vector<pair<vector<unsigned>, unsigned>>arr(length.size()+1, { {},0 });
	for (int i = 0; i < length.size(); ++i) {
		for (int j = length[i]; j < arr.size(); ++j) {
			if (arr[j - length[i]].second + price[i] > arr[j].second) {
				arr[j].first = arr[j - length[i]].first;
				arr[j].first.emplace_back(length[i]);
				arr[j].second = arr[j - length[i]].second + price[i];
			}
		}
	}
	return arr.back();
} // time O(length.size()*max_length); space O(length*length.size()) or O(n) (without vector)


void print_result_pair(const pair<vector<unsigned>, unsigned>&result) {
	cout <<"Profit: "<< result.second << '\n';
	cout << "Length: ";
	copy(result.first.begin(), result.first.end(), ostream_iterator<unsigned>{cout, " "});
	cout << '\n';
}

/*
It is also possible to write solution using branch and bound search or BFS
*/

void golden_test();

void main(){
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 100; ++times) {
		vector<unsigned>length(uniform_int_distribution<>{1, 10}(mt));
		iota(length.begin(), length.end(), 1);
		vector<unsigned>price(length.size());
		generate(price.begin(), price.end(), [&mt]() {return uniform_int_distribution<>{1,100}(mt); });

		auto res1 = cutting_rod_brute(length, price);
		auto res2 = cutting_rod_dp(length, price);
		assert(res1.second == res2.second);
		print_result_pair(res1);
		print_result_pair(res2);
		cout << "\n\n";
	}
	system("pause");
}

void golden_test() {
	vector<unsigned>test_length{ 1,2,3,4 };
	vector<unsigned>test_price{ 1,5,8,9 };
	auto res1 = cutting_rod_brute(test_length, test_price);
	auto res2 = cutting_rod_dp(test_length, test_price);
	assert(res1.second == res2.second);
}