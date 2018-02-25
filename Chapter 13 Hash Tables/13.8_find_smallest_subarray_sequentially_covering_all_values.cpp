// find the smallest subarray sequentially covering all values
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include <utility>
#include <numeric>
#include <random>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include <unordered_set>
using namespace std;

pair<int,int> subarray(const vector<string>&text, const vector<string>&query)
{
	pair<int, int>result{ -1,-1 };
	unordered_map<string, int>key_to_ind{};
	for (int i = 0; i < query.size(); ++i)
		key_to_ind.emplace(query[i], i);
	vector<int>latest(query.size(), -1);
	vector<int>shortest(query.size(), numeric_limits<int>::max());

	int shortest_dist = numeric_limits<int>::max();
	for (int i = 0; i < text.size(); ++i)
	{
		if (key_to_ind.count(text[i]))
		{
			int query_ind = key_to_ind[text[i]];
			if (query_ind == 0)
			{
				shortest[query_ind] = 1;
			}
			else if (shortest[query_ind - 1] != numeric_limits<int>::max())
			{
					shortest[query_ind] = shortest[query_ind - 1] + (i - latest[query_ind - 1]);
			}
			latest[query_ind] = i;

			if (query_ind == query.size() - 1 &&
				shortest.back() < shortest_dist)
			{
				result.first = latest.front();
				result.second = latest.back();
				shortest_dist = latest.back() - latest.front();
			}
		}
	}
	return result;
} // time O(n); space O(m) m - query words

string r_str(const int size)
{
	mt19937 mt{ random_device{}() };
	string res( size,{} );
	for (int i = 0; i < size; ++i)
	{
		res[i] = uniform_int_distribution<int>{ 'a','z' }(mt);
	}
	return res;
}

void small_test();

void main()
{
	small_test();
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 1000; ++i)
	{
		vector<string>text(uniform_int_distribution<int>{1, 5}(mt));
		generate(text.begin(), text.end(), [&mt]() {return r_str(uniform_int_distribution<int>{1, 5}(mt)); });
		unordered_set<string>set{ text.begin(),text.end() };
		vector<string>query{ set.begin(),set.end()};
		if (query.size() > 1)
		{
			auto n = uniform_int_distribution<int>{ 0,(int)query.size() - 1 }(mt);
			for (int i = 0; i < n; ++i)
			{
				int er = uniform_int_distribution<int>{ 0,(int)query.size() - 1 }(mt);
				query.erase(query.begin() + er);
			}
		}
		auto res = subarray(text, query);
		if (res.first != -1 && res.second != -1)
		{
			int query_ind = 0;
			for (int i = res.first; i <= res.second; ++i)
			{
				if (text[i] == query[query_ind])++query_ind;
			}
			assert(query_ind == query.size());
		}
	}
	system("pause");
}


void small_test()
{
	vector<string>arr{ "My", "paramount", "object", "in", "this", "struggle", "is", "to", "save", "the", "Union",
		",","and", "is", "not", "either", "to", "save", "or" ,"to","destroy", "slavery","." };
	auto res = subarray(arr, { "Union","save" });
	assert(res.first == 10 && res.second == 17);
}