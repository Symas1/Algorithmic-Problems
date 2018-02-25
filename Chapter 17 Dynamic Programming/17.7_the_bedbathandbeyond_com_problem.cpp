// the bedbathandbeyond.com problem
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <random>
using namespace std;


vector<string> decompose_into_dictionary_words(const string& str, const unordered_set<string>&dict) {
	vector<int>arr(str.size(), -1); // length of the word is saved here

	for (int i = 0; i < str.size(); ++i) {
		if (dict.count(str.substr(0, i + 1))) {
			arr[i] = i + 1;
		}

		if (arr[i] == -1) {
			for (int j = 0; j < i; ++j) {
				if (arr[j] != -1 && dict.count(str.substr(j+1,i-j))) {
					arr[i] = i - j;
				}
			}
		}
	}

	vector<string>res{};
	if (!arr.empty()&&arr.back() != -1) {
		int indx = str.size() - 1;
		while (indx >= 0) {
			res.emplace_back(str.substr(indx + 1 - arr[indx], arr[indx]));
			indx -= arr[indx];
		}
		reverse(res.begin(), res.end());
	}
	return res;
} // time O(n^3); space O(n) n - length of the target word

vector<string> decompose_into_dictionary_words2(const string& str, const unordered_set<string>&dict,int max_length) {
	vector<int>arr(str.size(), -1); // length of the word is saved here

	for (int i = 0; i < str.size(); ++i) {
		if (dict.count(str.substr(0, i + 1))) {
			arr[i] = i + 1;
		}

		if (arr[i] == -1) {
			for (int j = i-max_length<0?0:i-max_length; j < i; ++j) {
				if (arr[j] != -1 && dict.count(str.substr(j + 1, i - j))) {
					arr[i] = i - j;
				}
			}
		}
	}

	vector<string>res{};
	if (!arr.empty() && arr.back() != -1) {
		int indx = str.size() - 1;
		while (indx >= 0) {
			res.emplace_back(str.substr(indx + 1 - arr[indx], arr[indx]));
			indx -= arr[indx];
		}
		reverse(res.begin(), res.end());
	}
	return res;
} // time O(n^2*W); space O(n) n - length of the target word, W - length of the longest word in dictionary

void small_test() {
	vector<string> res{};
	unordered_set<string>dict{ "i","a","am","ace" };
	res= decompose_into_dictionary_words("iamace", dict);
	assert(equal(res.begin(), res.end(), vector<string>{ "i","am","ace" }.begin()));

	dict = { "bed","bath","and","hand","beyond" };
	res = decompose_into_dictionary_words("bedbathandbeyond", dict);
	assert(equal(res.begin(), res.end(), vector<string>{ "bed", "bath", "and", "beyond" }.begin()));

	dict = { "b" };
	res = decompose_into_dictionary_words("b", dict);
	assert(equal(res.begin(), res.end(), vector<string>{ "b" }.begin()));

	dict = { "c","cc" };
	res= decompose_into_dictionary_words("ccc", dict);
	assert(equal(res.begin(), res.end(), vector<string>{ "cc" ,"c"}.begin()));

	dict = {};
	res = decompose_into_dictionary_words("ccc", dict);
	assert(equal(res.begin(), res.end(), vector<string>{ }.begin()));
}

void check_answer(const string& target, const vector<string>&res) {
	string temp{};
	for (int i = 0; i < res.size(); ++i) {
		temp += res[i];
	}

	assert(!res.size() || !target.compare(temp));
}

string rand_str(size_t size) {
	string res(size, {});
	mt19937 mt{ random_device{}() };
	for (auto i = 0; i < size; ++i) {
		res[i] = uniform_int_distribution<>{ 'a','z' }(mt);
	}
	return res;
}

void main()
{
	small_test();

	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 10000; ++i) {
		unordered_set<string>dict{};
		int longest{};
		int dict_size = uniform_int_distribution<>{ 0,50 }(mt);
		for (int i = 0; i < dict_size; ++i) {
			int size = uniform_int_distribution<>{ 1, 15 }(mt);
			longest = max(longest, size);
			dict.emplace(rand_str(size));
		}
		string target = rand_str(uniform_int_distribution<>{0, 20}(mt));

		auto result = decompose_into_dictionary_words(target, dict);
		auto result2 = decompose_into_dictionary_words2(target, dict, longest);
		check_answer(target, result);
		check_answer(target, result2);
		assert(equal(result.begin(), result.end(), result2.begin(), result2.end()));
	}
	system("pause");
}