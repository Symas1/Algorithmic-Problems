// transform one string to another
#include <unordered_set>
#include <string>
#include <queue>
#include <random>
#include <iostream>
using namespace std;

int transform(unordered_set<string> dict, const string& start, const string&end) {
	struct Candidate {
		Candidate(string s, int d) :candidate{ s }, distance{ d } {};
		string candidate;
		int distance;
	};
	queue<Candidate>next{};
	next.emplace(start, 0);
	dict.erase(start);
	while (!next.empty()) {
		Candidate current_cand = next.front();
		next.pop();

		if (current_cand.candidate == end) {
			return current_cand.distance;
		}

		string str = current_cand.candidate;
		for (int i = 0; i < str.size(); ++i) {
			for (int j = 0; j < 26; ++j) {
				str[i] = 'a' + j;
				if (dict.count(str)) {
					next.emplace(str,current_cand.distance+1);
					dict.erase(str);
				}
			}
			str[i] = current_cand.candidate[i];
		}
	}
	return -1;
} // time O(n*26*n) ~ O(n^2) n - word length; space O(d) d - dict size

string rand_str(const size_t size) {
	string res(size, {});
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < res.size(); ++i) {
		res[i] = uniform_int_distribution<>{ 'a','z' }(mt);
	}
	return res;
}

void main() {
	mt19937 mt{ random_device{}() };
	int len = uniform_int_distribution<>{ 1,5 }(mt);
	auto a = rand_str(len), b = rand_str(len);
	int dict_size = uniform_int_distribution<>{ 1,10000 }(mt);
	unordered_set<string>set{ {a,b} };
	for (int i = 0; i < dict_size; ++i) {
		set.emplace(rand_str(len));
	}
	cout << a << " " << b << endl;
	cout << transform(set, a, b)<<endl;
	system("pause");
}