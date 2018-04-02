
#include <vector>
#include <algorithm>
#include <assert.h>
#include <string>
#include <iostream>
#include <numeric>
#include <random>
#include <cmath>
using namespace std;

unsigned edit_distance_exp_helper(const string& from, const string& to, int from_start, int to_start);
unsigned edit_distance_exp(const string& from, const string& to) {
	return edit_distance_exp_helper(from, to, 0, 0);
} // time O(3^n); space O(max_size)
unsigned edit_distance_exp_helper(const string& from, const string& to, int from_start, int to_start) {
	if (from_start >= from.size()) {
		int s = to.size();
		return fabs(s - to_start);

	}
	if (to_start >= to.size()) {
		int s = from.size();
		return abs(s - from_start);
	}

	if (from[from_start] == to[to_start]) {
		return edit_distance_exp_helper(from, to, from_start + 1, to_start + 1);
	}
	else {
		return min({
			edit_distance_exp_helper(from,to,from_start + 1,to_start + 1),
			edit_distance_exp_helper(from,to,from_start + 1,to_start),
			edit_distance_exp_helper(from,to,from_start,to_start + 1)
			}) + 1;
	}
}

unsigned edit_distance_n2_n2(const string& from, const string& to) {
	if (from.empty()) {
		return to.size();
	}
	vector<vector<unsigned>>dist(to.size() + 1, vector<unsigned>(from.size() + 1, 0));
	for (int i = 0; i < dist.front().size(); ++i) {
		dist[0][i] = i;
	}
	for (int i = 0; i < dist.size(); ++i) {
		dist[i][0] = i;
	}
	for (int i = 1; i <= to.size(); ++i) {
		for (int j = 1; j <= from.size(); ++j) {
			if (from[j-1] == to[i-1]) {
				dist[i][j] = dist[i - 1][j - 1];
			}
			else {
				dist[i][j] = min({ dist[i - 1][j - 1],dist[i][j - 1],dist[i - 1][j] })+1;
			}
		}
	}
	return dist.back().back();
} // time O(n*m); space O(n*m)

unsigned edit_distance_n2_n(const string& from, const string&to) {
	if (from.empty()) {
		return to.size();
	}
	vector<unsigned>dist(from.size() + 1, 0);
	iota(dist.begin(), dist.end(), 0);

	for (int i = 1; i <= to.size(); ++i) {
		unsigned prev = i-1;
		for (int j = 1; j <= from.size(); ++j) {
			unsigned save = dist[j];
			if (from[j - 1] == to[i - 1]) {
				dist[j] = prev;
			}
			else {
				dist[j] = min({ prev,dist[j],(j - 1 < 0 ? i : dist[j - 1]) }) + 1;
			}
			prev = save;
		}
		dist[0] = i+1;
	}
	return dist.back();
} // time O(n*m); space O(from.size())

string rand_str(size_t size) {
	mt19937 mt{ random_device{}() };
	string res(size, '\0');
	for (int i = 0; i < size; ++i) {
		res[i] = uniform_int_distribution<>{ 'a','z' }(mt);
	}
	return res;
}

void main() {
	assert(edit_distance_exp("caa", "ca") == 1);
	assert(edit_distance_exp("sunday", "saturday") == 3);
	assert(edit_distance_n2_n2("caa", "ca") == 1);
	assert(edit_distance_n2_n2("sunday", "saturday") == 3);
	assert(edit_distance_n2_n("caa", "ca") == 1);
	assert(edit_distance_n2_n("sunday", "saturday") == 3);

	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times) {
		auto from = rand_str(uniform_int_distribution<>{0, 10}(mt));
		auto to = rand_str(uniform_int_distribution<>{0, 10}(mt));
		auto res1 = edit_distance_n2_n2(from, to);
		auto res2 = edit_distance_n2_n(from, to);
		//auto res3 = edit_distance_exp(from, to);
		assert(res1 == res2);
		//assert(res2 == res3);
	}
	system("pause");
}