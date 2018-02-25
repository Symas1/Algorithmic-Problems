// making wired connections (bipartite graph)
#include <vector>
#include <assert.h>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <random>
#include <iostream>
using namespace std;

enum Color { white, black };

struct Graph_vertex{
	Color color{ white };
	vector<Graph_vertex*>edges;
};

bool is_bipartite_bfs_helper(Graph_vertex* start, unordered_set<Graph_vertex*>&visited);
bool is_bipartite_bfs(vector<Graph_vertex>&graph) {
	unordered_set<Graph_vertex*>visited;
	for (auto& vertex : graph) {
		if (!visited.count(&vertex)) {
			if (!is_bipartite_bfs_helper(&vertex, visited)) {
				return false;
			}
		}
	}
	return true;
} // complexity - BFS: time O(|V|+|E|); space O(|V|) V - vertices, E - edges

bool is_bipartite_bfs_helper(Graph_vertex* start, unordered_set<Graph_vertex*>&visited) {
	queue<Graph_vertex*>next_vertex;
	next_vertex.emplace(start);
	visited.emplace(start);
	while (!next_vertex.empty()) {
		for (auto& edge : next_vertex.front()->edges) {
			if (visited.count(edge)) {
				if (edge->color == next_vertex.front()->color){
					return false;
				}
			}
			else {
				visited.emplace(edge);
				next_vertex.emplace(edge);
				edge->color = next_vertex.front()->color == white ? black : white;
			}
		}
		next_vertex.pop();
	}
	return true;
}

void check(const vector<Graph_vertex>&graph) {
	for (const auto& vertex : graph) {
		for (const auto& connected_vertex : vertex.edges) {
			assert(vertex.color != connected_vertex->color);
		}
	}
}

void small_test() {
	// triangle - false
	{
		vector<Graph_vertex>graph(3);
		graph[0].edges.emplace_back(&graph[1]);
		graph[0].edges.emplace_back(&graph[2]);

		graph[1].edges.emplace_back(&graph[0]);
		graph[1].edges.emplace_back(&graph[2]);

		graph[2].edges.emplace_back(&graph[0]);
		graph[2].edges.emplace_back(&graph[1]);

		assert(!is_bipartite_bfs(graph));
	}
	// square - true
	{
		vector<Graph_vertex>graph(4);
		graph[0].edges.emplace_back(&graph[1]);
		graph[0].edges.emplace_back(&graph[2]);

		graph[1].edges.emplace_back(&graph[0]);
		graph[1].edges.emplace_back(&graph[3]);

		graph[2].edges.emplace_back(&graph[0]);
		graph[2].edges.emplace_back(&graph[3]);

		graph[3].edges.emplace_back(&graph[1]);
		graph[3].edges.emplace_back(&graph[2]);

		assert(is_bipartite_bfs(graph));
	}
}

void main() {
	small_test();
	
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 1000; ++i) {
		int graph_size = uniform_int_distribution<>{ 2,100 }(mt);
		vector<Graph_vertex>graph(graph_size);

		vector<vector<bool>>connected(graph_size, vector<bool>(graph_size, false));
		for (int i = 1; i < graph_size; ++i) {
			graph[i].edges.emplace_back(&graph[i - 1]);
			graph[i-1].edges.emplace_back(&graph[i]);
			connected[i][i - 1] = connected[i - 1][i] = true;
		}
		int edges = uniform_int_distribution<>{ 1,graph_size*(graph_size - 1) / 2 }(mt);
		edges -= (graph_size - 1);

		while (edges-- > 0) {
			int a, b;
			uniform_int_distribution<>dis{ 0,graph_size - 1 };
			do{
				a = dis(mt), b = dis(mt);
			} while (a == b || connected[a][b]);
			connected[a][b] = connected[b][a] = true;
			graph[a].edges.emplace_back(&graph[b]);
			graph[b].edges.emplace_back(&graph[a]);
		}

		vector<Graph_vertex>graph2 = graph;

		bool is_bipartite_b = is_bipartite_bfs(graph);
		cout << boolalpha << is_bipartite_b << endl;
		if (is_bipartite_b) {
			check(graph);
		}
	}
	system("pause");
}