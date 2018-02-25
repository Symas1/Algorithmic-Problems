// clone a graph
#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>
using namespace std;

struct Graph_vertex {
	Graph_vertex(int d_) :data{ d_ } {};
	int data;
	vector<Graph_vertex*>edges;
};

pair<Graph_vertex*, unordered_map<Graph_vertex*, unique_ptr<Graph_vertex>>> copy_graph(Graph_vertex* start_vertex) {
	if (!start_vertex) {
		return{};
	}
	unordered_map<Graph_vertex*, unique_ptr<Graph_vertex>>visited_vertices{};
	visited_vertices.emplace(start_vertex,make_unique<Graph_vertex>(start_vertex->data));
	queue<Graph_vertex*>next_vertices{ {start_vertex} };
	while (!next_vertices.empty()) {
		auto current_vertex = next_vertices.front();
		next_vertices.pop();
		for (Graph_vertex* edge : current_vertex->edges) {
			if (!visited_vertices.count(edge)) {
				visited_vertices.emplace(edge, make_unique<Graph_vertex>(edge->data));
				next_vertices.emplace(edge);
			}
			visited_vertices[current_vertex]->edges.emplace_back(visited_vertices[edge].get());
		}
	}
	return {visited_vertices[start_vertex].get(),move(visited_vertices)};
} // complexity BFS - time O(|V|+|E|); space O(|V|)

vector<int> copy_labels(const vector<Graph_vertex*>&edges) {
	vector<int>res;
	for (const auto& x : edges) {
		res.emplace_back(x->data);
	}
	return res;
}

void check_answer(Graph_vertex* copy_start, const vector<Graph_vertex>&original) {
	unordered_set<Graph_vertex*>visited;
	queue<Graph_vertex*>next;
	next.emplace(copy_start);
	visited.emplace(copy_start);
	while (!next.empty()) {
		auto curr = next.front();
		next.pop();
		auto res_labels = copy_labels(curr->edges);
		auto original_labels = copy_labels(original[curr->data].edges);
		sort(res_labels.begin(), res_labels.end());
		sort(original_labels.begin(), original_labels.end());
		assert(equal(res_labels.begin(), res_labels.end(), original_labels.begin(), original_labels.end()));
		for (const auto& e : curr->edges) {
			if (!visited.count(e)) {
				visited.emplace(e);
				next.emplace(e);
			}
		}
	}
}

void main() {
	auto res = copy_graph(nullptr);
	assert(res.first == nullptr && res.second.empty());
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 100; ++i) {
		int n = uniform_int_distribution<>{ 2,101 }(mt);
		vector<Graph_vertex>graph;
		for (int i = 0; i < n; ++i) {
			graph.emplace_back(i);
		}

		vector<vector<bool>>edges_connected(n, vector<bool>(n, false));
		for (int i = 1; i < n; ++i) {
			graph[i - 1].edges.emplace_back(&graph[i]);
			graph[i].edges.emplace_back(&graph[i - 1]);
			edges_connected[i - 1][i] = edges_connected[i][i - 1] = true;
		}

		int m = uniform_int_distribution<>{ 1,n*(n - 1) / 2 }(mt);
		m -= (n - 1);

		while (m-- > 0) {
			int a, b;
			uniform_int_distribution<>dis{ 0, n - 1 };
			do {
				a = dis(mt), b = dis(mt);
			} while (a == b || edges_connected[a][b]);
			edges_connected[a][b] = edges_connected[b][a] = true;
			graph[a].edges.emplace_back(&graph[b]);
			graph[b].edges.emplace_back(&graph[a]);
		}
		auto res = copy_graph(&graph[0]);
		check_answer(res.first, graph);
	}
	system("pause");
}