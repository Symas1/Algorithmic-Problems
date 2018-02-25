// find anagrams
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
using namespace std;

vector<vector<string>> find_anagrams(const vector<string>& arr)
{
	unordered_map<string, vector<string>>map{};
	for (const string& str : arr)
	{
		string sorted_str = str;
		sort(sorted_str.begin(), sorted_str.end());
		map[sorted_str].emplace_back(str);
	}

	vector<vector<string>>result{};
	for (const auto& x : map)
	{
		if (x.second.size() >= 2)result.emplace_back(x.second);
	}
	return result;
} // time O(nmlogm) n - strings, m - max string size; space O(nm)

int main(int argc, char* argv[])
{
	vector<string> D = { "debit card",
		"bad credit",
		"the morse code",
		"here come dots",
		"the eyes",
		"they see",
		"THL" };
	auto result = find_anagrams(D);
	// 3 nontrivial groups:
	// {"debit card", "bad credit"},
	// {"the morse code", "here come dots"}
	// {"the eyes",   "they see"
	// Since the string "THL" has no anagrams in D, the result
	// contains 3 entries
	assert(result.size() == 3);
	system("pause");
	return 0;
}