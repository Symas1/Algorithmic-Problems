/* Solution */
vector<int> tushar_next(const vector<int>&hits, int resist) {
	auto weakest_hit_idx = distance(hits.begin(), min_element(hits.begin(), hits.end()));
	vector<int>result(resist / hits[weakest_hit_idx], weakest_hit_idx);
	resist -= hits[weakest_hit_idx] * result.size();
	for (int i = 0, idx = 0; i < weakest_hit_idx && idx < result.size(); ++i) {
		while (idx < result.size() && resist + hits[result[idx]] >= hits[i]) {
			resist += hits[result[idx]] - hits[i];
			result[idx++] = i;
		}
	}
	return result;
} // time O(2n + n + 2n)=O(5n)=O(n); space O(n)






/* First try - accepted */
void tushar_depth_helper(const map<int, int>&kick_to_idx, list<int>&res, list<int>&curr,
	const map<int, int>::iterator min_kick, const int resist);
bool new_list_better(list<int> curr_best, list<int>new_list);
vector<int> tushar_depth(const vector<int>& kicks, const int resist) {
	map<int, int>kick_to_idx;
	for (int i = 0; i < kicks.size(); ++i) {
		kick_to_idx.emplace(kicks[i], i);
	}
	list<int>result;
	list<int>curr;
	tushar_depth_helper(kick_to_idx, result, curr, kick_to_idx.begin(), resist);
	result.sort();
	return { result.begin(),result.end() };
}
void tushar_depth_helper(const map<int, int>&kick_to_idx, list<int>&res, list<int>&curr,
	const map<int, int>::iterator min_kick, const int resist) {
	if (resist < 0) {
		return;
	}
	if (curr.size() > res.size() || (curr.size() == res.size() && new_list_better(res, curr))) {
		res = curr;
	}
	if (min_kick == kick_to_idx.end()) {
		return;
	}

	int min_hit = min_kick->first;
	int hits_with_kick = resist / min_hit;
	if (hits_with_kick == 0) {
		return;
	}
	for (int i = hits_with_kick; i >= 0; --i) {
		int potential = next(min_kick) != kick_to_idx.end() ?
			(resist - (min_hit*i)) / next(min_kick)->first : 0;
		if ((i + curr.size() + potential) < res.size()) {
			return;
		}
		for (int j = 0; j < i; ++j) {
			curr.emplace_back(min_kick->second);
		}
		tushar_depth_helper(kick_to_idx, res, curr, next(min_kick), resist - (min_hit*i));
		auto it = curr.begin();
		advance(it, curr.size() - i);
		curr.erase(it, curr.end());
	}
}
bool new_list_better(list<int> curr_best, list<int>new_list) {
	new_list.sort();
	curr_best.sort();
	bool new_better = false;
	auto n_it = new_list.begin();
	auto c_it = curr_best.begin();
	for (; c_it != curr_best.end(); ++c_it, ++n_it) {
		if (*c_it != *n_it) {
			new_better = *n_it < *c_it;
			break;
		}
	}
	return new_better;
}