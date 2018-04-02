bool is_match(const char* t, const char* p) {
	if (!p) {
		return !t;
	}

	bool match = *t == *p || *p == '.' ? true : false;
	if (*(p + 1) == '*') {
		return is_match(t, p + 2) || (match && is_match(t + 1, p));
	}
	return match && is_match(t + 1, p + 1);
}

bool is_match_dp(const string& txt, const string& ptrn) {
	vector<vector<bool>>ways(txt.size() + 1, vector<bool>(ptrn.size() + 1));
	ways[0][0] = true;
	for (int col = 0; col < ways.front().size() - 1; ++col) {
		ways[0][col + 1] = col > 0 && ptrn[col] == '*' && ways[0][col - 1];
	}
	for (int row = 1; row < ways.size(); ++row) {
		ways[row][0] = false;
	}

	for (int row = 1; row < ways.size(); ++row) {
		for (int col = 1; col < ways[row].size(); ++col) {
			if (ptrn[col - 1] != '*') {
				ways[row][col] = (txt[row - 1] == ptrn[col - 1] || ptrn[col - 1] == '.') &&
					ways[row - 1][col - 1];
			}
			else {
				ways[row][col] = ways[row][col - 2] || 
					((ptrn[col - 2] == txt[row - 1] || ptrn[col - 2] == '.') && ways[row - 1][col]);
			}
		}
	}
	return ways.back().back();
} // time O(nm); space O(nm)

bool is_match_dp_better(const string& txt, const string& ptrn) {
	vector<bool>ways(ptrn.size() + 1, false);
	ways[0] = true;

	for (int col = 0; col < ptrn.size(); ++col) {
		ways[col + 1] = col > 0 && ptrn[col] == '*' && ways[col - 1];
	}

	for (int txt_it = 0; txt_it < txt.size(); ++txt_it) {
		bool diag = ways[0];
		ways[0] = false;
		for (int ptrn_it = 0; ptrn_it < ptrn.size(); ++ptrn_it) {
			bool diag_save = ways[ptrn_it + 1];
			if (ptrn[ptrn_it] != '*') {
				ways[ptrn_it + 1] = (ptrn[ptrn_it] == txt[txt_it] || ptrn[ptrn_it] == '.') && diag;
			}
			else {
				ways[ptrn_it + 1] = ways[ptrn_it - 1] ||
					((ptrn[ptrn_it - 1] == txt[txt_it] || ptrn[ptrn_it - 1] == '.') && ways[ptrn_it+1]);
			}
			diag = diag_save;
		}
	}

	return ways.back();
} // time O(nm); space O(m)