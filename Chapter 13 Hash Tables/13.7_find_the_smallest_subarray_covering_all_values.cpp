// find the smallest subarray covering all values
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <utility>
#include <assert.h>
#include <string>
#include <list>
#include <sstream>
#include <random>
#include <queue>
#include <functional>
using namespace std;

pair<int, int> smallest(const vector<string>& text, const unordered_set<string>& keywords)
{
	unordered_map<string, int>words_to_find{};
	for (const auto& iter : keywords)
	{
		++words_to_find[iter];
	}

	pair<int, int>result{ -1,-1 };
	int remaining_words = keywords.size();
	for (int left = 0, right = 0; right < text.size(); ++right)
	{
		if (keywords.count(text[right]) && --words_to_find[text[right]] >= 0)
			--remaining_words;

		while (remaining_words == 0)
		{
			if (result.first == -1 && result.second == -1 ||
				result.second - result.first > right - left)
			{
				result.first = left;
				result.second = right;
			}

			if (keywords.count(text[left]) && ++words_to_find[text[left]] > 0)
				++remaining_words;

			++left;
		}
	}
	return result;
} // time O(n); space O(d) d - words to find


pair<int, int> stream_smallest(istringstream& stream, const vector<string>& keywords)
{
	list<int> indexes{};
	unordered_map<string, list<int>::iterator>map{};
	for (const auto& s : keywords)
	{
		map.emplace(s, indexes.end());
	}

	pair<int, int>res{ -1,-1 };
	int ind = 0;
	string s;
	while (stream >> s)
	{
		auto iter = map.find(s);
		if (iter != map.end())
		{
			if (iter->second != indexes.end())
			{
				indexes.erase(iter->second);
			}
			indexes.emplace_back(ind);
			iter->second = prev(indexes.end());
		}

		if (indexes.size() == keywords.size())
		{
			if (res.first == -1 && res.second == -1 ||
				res.second - res.first > ind - indexes.front())
			{
				res.first = indexes.front();
				res.second = ind;
			}
		}
		++ind;
	}
	return res;
} // time O(n); space O(m) m - distinct keywords

pair<int, int> variant1(const vector<int>&arr)
{
	list<int> indexes{};
	unordered_map<int, list<int>::iterator>map{};
	pair<int, int> result{ -1,-1 };
	for (int i = 0; i < arr.size(); ++i)
	{
		auto iter = map.find(arr[i]);
		if (iter != map.end())
		{
			indexes.erase(iter->second);
			indexes.emplace_back(i);
			iter->second = prev(indexes.end());
		}
		else
		{
			indexes.emplace_back(i);
			map.emplace(arr[i], prev(indexes.end()));
			if (result.first == -1 && result.second == -1)
				result.first = i, result.second = i;
			else
				result.second = i;
		}

		if (indexes.back() - indexes.front() < result.second - result.first)
			result.first = indexes.front(), result.second = indexes.back();
	}
	return result;
} // time O(n); space O(d) d - different numbers

bool variant4(vector<int>&arr, int k) // k distance apart
{
	unordered_map<int, int>occurences{};
	for (const auto& x : arr)++occurences[x];
	priority_queue < pair<int, int>, vector<pair<int, int>>, function<bool(const pair<int, int>&, const pair<int, int>&)>>q1
	{ [](const pair<int,int>& first,const pair<int,int>& second) {return first.second < second.second; } };
	for (const auto& x : occurences)
		q1.emplace(x.first, x.second);

	unordered_map<int, int>recent{};
	for (int i = 0; i < arr.size();)
	{
		while (!q1.empty())
		{
			if (recent.count(q1.top().first) && i-recent[q1.top().first] <= k)
				return false;
			arr[i] = q1.top().first;
			recent[arr[i]] = i;
			if (--occurences[arr[i]] == 0)
				occurences.erase(q1.top().first);
			q1.pop();
			++i;
		}
		for (const auto& x : occurences)
			q1.emplace(x.first, x.second);
	}
	return true;
} // time O(n + mlogm) n - size, m - distinct elements (constant); space O(m)

void test_main();

void main()
{
	test_main();
	{
		vector<int>arr{ 1,2,2,3,3,3,4,5,1,2,3,4,5 };
		auto res = variant1(arr);
		cout << res.first << '\t' << res.second << endl;
	}

	{
		vector<int>arr{ 2,2,2,1,1 };
		bool res = variant4(arr, 1);
		assert(res == true && equal(arr.begin(), arr.end(), vector<int>{2, 1, 2, 1, 2}.begin()));
		res = variant4(arr, 2);
		assert(res == false);
		arr = { 1,1,1,2,2,2,3,3 };
		res = variant4(arr, 2);
		assert(res == true && equal(arr.begin(), arr.end(), vector<int>{1, 2, 3, 1, 2,3,1,2}.begin()));
	}
	system("pause");
}

void test_main()
{
	vector<string>arr{ "My", "paramount", "object", "in", "this", "struggle", "is", "to", "save", "the", "Union" };
	auto res1 = smallest(arr, { "save","Union" });
	string str{};
	for (const auto& x : arr)str += x + " ";
	istringstream stream{ str };
	auto res2 = stream_smallest(stream, { "save","Union" });
	assert(res1 == res2);
}
