// compute all string decompositions
#include <unordered_map>
#include <vector>
#include <string>
#include <assert.h>
#include <iostream>
using namespace std;

vector<size_t> compute(const string& str, const vector<string>& words)
{
	unordered_map<string, int>words_map{};
	vector<size_t>res{};
	for (const auto& w : words)++words_map[w];
	int word_len = words.front().size();
	int total_len = word_len*words.size();
	for (size_t i = 0; i <= (str.size() - total_len); ++i)
	{
		unordered_map<string, int>used{};
		int current_len = 0;
		while (current_len < total_len)
		{
			string sub = str.substr(i + current_len, word_len);
			if (words_map.count(sub))
			{
				if (used[sub] < words_map[sub])
				{
					++used[sub];
					current_len += word_len;
				}
				else break;

				if (current_len == total_len)res.emplace_back(i);
			}
			else break;
		}
	}
	return res;
} // time O(Nmn) N - sentence length, nm - total length; space O(m) m - words

void main()
{
	const string str{ "amanaplanacanal" };
	vector<string>words{ "can","apl","ana" };
	auto res = compute(str, words);
	for (const auto& x : res)cout << x << " ";
	cout << endl;
	system("pause");
}