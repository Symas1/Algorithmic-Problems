// team photo day 2
#include <stack>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <iostream>
using namespace std;

struct Graph_vertex {
	vector<Graph_vertex*>edges;
	int distance = 0;
};


void dfs(Graph_vertex* vertex, stack<Graph_vertex*>& stack);
stack<Graph_vertex*> topological_sort(vector<Graph_vertex>&vertices) {
	stack<Graph_vertex*>res{};
	for (int i = 0; i < vertices.size(); ++i) {
		if (vertices[i].distance == 0) {
			dfs(&vertices[i], res);
		}
	}
	return res;
}
void dfs(Graph_vertex* vertex, stack<Graph_vertex*>& stack) {
	vertex->distance = 1;
	for (auto& v : vertex->edges) {
		if (v->distance == 0) {
			dfs(v, stack);
		}
	}
	stack.emplace(vertex);
}

int longest_path(stack<Graph_vertex*>&s) {
	int max_distance = 0;
	while (!s.empty()) {
		Graph_vertex* u = s.top();
		max_distance = max(max_distance, u->distance);
		for (auto& v : u->edges) {
			v->distance = max(v->distance, u->distance+1);
		}
		s.pop();
	}
	return max_distance;
}

int teams(vector<Graph_vertex>&graph) {
	auto s = topological_sort(graph);
	return longest_path(s);
} // time O(|V|+|E|); space O(|V|)

void main() {
	vector<Graph_vertex> G(3);
	G[0].edges.emplace_back(&G[2]);
	G[1].edges.emplace_back(&G[2]);
	assert(2 == teams(G));
	system("pause");
}