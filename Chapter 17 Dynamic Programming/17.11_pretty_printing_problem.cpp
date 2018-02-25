// the pretty printing problem
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <numeric>
using namespace std;

int pretty_printing(vector<string>&words, const int line_length) {
	vector<int>messiness(words.size(), numeric_limits<int>::max());
	int remaining_blanks = line_length - words[0].size();
	messiness[0] = remaining_blanks * remaining_blanks;
	for (int i = 1; i < words.size(); ++i) {
		remaining_blanks = line_length - words[i].size();
		messiness[i] = remaining_blanks*remaining_blanks + messiness[i-1];
		for (int j = i - 1; j >= 0; --j) {
			remaining_blanks -= (words[j].size() + 1);
			if (remaining_blanks < 0) {
				break;
			}
			int line_j_mess = j - 1 < 0 ? 0 : messiness[j - 1];
			messiness[i] = min(messiness[i], line_j_mess + remaining_blanks*remaining_blanks);
		}
	}
	return messiness.back();
} // time O(nL) L - line length; space O(n)

void small_test() {
	vector<string>words{ "a","b","c","d" };
	assert(pretty_printing(words, 5) == 8);
	assert(pretty_printing(vector<string>{ "aaa", "bbb", "c", "d", "ee", "ff", "gggggg" },
		11) == 45);
	assert(pretty_printing(vector<string>{ "a", "b", "c", "d" }, 5) == 8);
}

void main() {
	small_test();
	system("pause");
}