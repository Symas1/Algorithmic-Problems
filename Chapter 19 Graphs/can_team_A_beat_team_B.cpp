// given teams A and B, is there a sequence of teams starting with A and ending with B such that each
// team in the sequence has beaten the next team in the sequence
#include <string>
#include <assert.h>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
using namespace std;

struct Match_result {
	string winning_team;
	string losing_team;
};

unordered_map<string, unordered_set<string>> build_graph(const vector<Match_result>&matches) {
	unordered_map<string, unordered_set<string>>res{};
	for (const auto& x : matches) {
		res[x.winning_team].emplace(x.losing_team);
	}
	return res;
}

bool can_team_a_beat_team_b_dfs_helper(const unordered_map<string, unordered_set<string>>&matches,
	unordered_set<string>&visited, const string& curr, const string& dest);
bool can_team_a_beat_team_b_dfs(const vector<Match_result>&matches, const string& a_team, const string& b_team) {
	unordered_set<string>visited{};
	return can_team_a_beat_team_b_dfs_helper(build_graph(matches), visited, a_team, b_team);
} // time O(E); space O(E) E - number of outcomes
bool can_team_a_beat_team_b_dfs_helper(const unordered_map<string, unordered_set<string>>&matches,
	unordered_set<string>&visited, const string& curr, const string& dest) {
	if (curr == dest) {
		return true;
	}
	if (visited.count(curr) || !matches.count(curr)) {
		return false;
	}
	visited.emplace(curr);
	const auto& defeated_teams = matches.at(curr);
	return any_of(defeated_teams.begin(), defeated_teams.end(), [&](const string&team) {
		return can_team_a_beat_team_b_dfs_helper(matches, visited, team, dest);
	});
}

bool can_team_a_beat_team_b_bfs_helper(const unordered_map<string, unordered_set<string>>&matches,
	const string& curr, const string& dest);
bool can_team_a_beat_team_b_bfs(const vector<Match_result>&matches, const string&a_team, const string& b_team) {
	return can_team_a_beat_team_b_bfs_helper(build_graph(matches), a_team, b_team);
} // time O(E); space O(E) E - number of outcomes
bool can_team_a_beat_team_b_bfs_helper(const unordered_map<string, unordered_set<string>>&matches,
	const string& curr, const string& dest) {
	unordered_set<string>visited{curr};
	queue<string>q{ {curr} };
	while (!q.empty()) {
		auto current_team = q.front();
		q.pop();
		if (current_team == dest) {
			return true;
		}
		else if (matches.count(current_team)) {
			for (const auto& defeated : matches.at(current_team)) {
				if (!visited.count(defeated))
				{
					q.emplace(defeated);
					visited.emplace(defeated);
				}
			}
		}

	}
	return false;
}

void check(const vector<Match_result>&results,const string& a_team,const string&b_team) {
	assert(can_team_a_beat_team_b_dfs(results, a_team, b_team) ==
		can_team_a_beat_team_b_bfs(results, a_team, b_team));
}

void main() {
	vector<Match_result> matches = { { "Texas", "Cal" },{ "Cal", "Stanford" },
	{ "Stanford", "Texas" },{ "Stanford", "MIT" },
	{ "Stanford", "CIT" },{ "UCLA", "USC" } };
	assert(can_team_a_beat_team_b_dfs(matches, "Texas", "MIT"));
	assert(can_team_a_beat_team_b_bfs(matches, "Texas", "MIT"));
	assert(!can_team_a_beat_team_b_dfs(matches, "Cal", "UCLA"));
	assert(!can_team_a_beat_team_b_bfs(matches, "Cal", "UCLA"));
	check(matches, "Texas", "MIT");
	check(matches, "Cal", "UCLA");
	system("pause");
}