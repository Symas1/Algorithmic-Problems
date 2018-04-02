// Longest Even Length Substring such that Sum of First and Second Half is same
#include <string>
#include <vector>
#include <iostream>
#include <assert.h>
#include <random>
#include <numeric>
using namespace std;

unsigned longest_n3(const string& str) {
	unsigned res = 0;
	for (int i = 0; i < str.size(); ++i) {
		for (int step = res==0?1:res; step < str.size() - i; step+=2) {
				unsigned left = 0;
				unsigned right = 0;
				for (int k = 0; k <= step; ++k) {
					if (k < (step + 1) / 2) {
						left += str[k+i] - '0';
					}
					else {
						right += str[k+i] - '0';
					}
				}
				if (left == right && step>res) {
					res = step;
				}
		}
	}
	return res==0?0:res+1;
} // time O(n^3); space O(1)

unsigned longest_n2_n2(const string& str) {
	vector<vector<unsigned>>nums(str.size(), vector<unsigned>(str.size(), 0));
	for (int i = 0; i < str.size(); ++i) {
		nums[0][i] = str[i]-'0';
	}
	int res = 0;
	for (int i = 2; i <= str.size(); ++i) {
		for (int start = i - 1; start < str.size(); ++start) {
			nums[i - 1][start] = nums[i - 2][start - 1] + nums[0][start];
			if (i% 2 == 0) {
				if (nums[i / 2 -1][start] == nums[i / 2 -1][start - (i / 2)] && i>res) {
					res = i;
				}
			}
		}
	}
	return res;
} // time O(n^2); space O(n^2)

unsigned longest_n2_n(const string& str) {
	vector<unsigned>arr(str.size());
	for (int i = 0; i < str.size(); ++i) {
		arr[i] = i == 0 ? str[i] - '0' : arr[i - 1] + str[i] - '0';
	}
	unsigned res = 0;
	for (int i = 2; i <= str.size(); i += 2) {
		for (int start = i - 1; start < str.size(); ++start) {
			auto first = arr[start] - arr[start - i / 2];
			auto second = arr[start - i / 2] - (start - i >= 0 ? arr[start - i] : 0);
			if (first==second && i>res) {
				res = i;
			}
		}
	}
	return res;
} // time O(n^2); space O(n)

unsigned longest_n2_1(const string& str) {
	unsigned res = 0;
	for (int i = 0; i <= str.size(); ++i) {
		unsigned left = 0;
		unsigned right = 0;
		for (int k = 0; k + i + 1 < str.size() && i - k >= 0; ++k) {
			left += str[i - k] - '0';
			right += str[k + i + 1] - '0';
			if (left == right && (k+1)*2>res) {
				res = (k + 1) * 2;
			}
		}
	}
	return res;
} // time O(n^2); space O(1)

string random_sequence(size_t size) {
	mt19937 mt{ random_device{}() };
	string res(size,' ');
	for (int i = 0; i < size; ++i) {
		char num = uniform_int_distribution<>{ '0','9' }(mt);
		if (i == 0 && num == '0') {
			--i;
			continue;
		}
		res[i] = num;
	}
	return res;
}

void main() {
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times) {
		auto str = random_sequence(uniform_int_distribution<>{0, 100}(mt));
		cout << str<<"   ";
		auto res_n3 = longest_n3(str);
		auto res_n2_n2 = longest_n2_n2(str);
		auto res_n2_n = longest_n2_n(str);
		auto res_n2_1 = longest_n2_1(str);
		cout << res_n3 << "   " << res_n2_n2 << "   " << res_n2_n << "   "<<res_n2_1<<endl;
		assert(res_n3 == res_n2_n2);
		assert(res_n2_n2==res_n2_n);
		assert(res_n2_n == res_n2_1);
	}
	system("pause");
}