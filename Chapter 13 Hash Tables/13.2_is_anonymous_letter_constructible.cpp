// check whether anonymous letter is constructible
#include <unordered_map>
#include <string>
#include <iostream>
#include <assert.h>
using namespace std;

bool is_construcitble(const string& magazine, const string& letter)
{
	unordered_map<char, unsigned>letter_letters{};
	for (const auto& c : letter)
	{
		++letter_letters[c];
	}
	for (const auto& c : magazine)
	{
		auto iter = letter_letters.find(c);
		if (iter != letter_letters.end())
		{
			if (--iter->second == 0)letter_letters.erase(iter);
		}
		if (letter_letters.empty())return true;
	}
	return false;
} // time O(n+m) n - magazine size, m - letter size; space O(m)

int main(int agrc, char* argv[])
{
	assert(is_construcitble("aaaa bb c zzzz", "aaa bb c zzzz"));
	assert(!is_construcitble("aa bb c zzzz", "aaa bb c zzzz"));
	system("pause");
	return 0;
}
