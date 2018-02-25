// compute a shortest path with fewest edges
#include <vector>
#include <iostream>
#include <assert.h>
#include <functional>
#include <algorithm>
#include <numeric>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <random>
#include <numeric>
using namespace std;

struct Graph_vertex {
	char id;
	vector<pair<Graph_vertex*, int>>adjacent_vertices_with_dist;
};

void output_path(const unordered_map<Graph_vertex*, Graph_vertex*>&path, Graph_vertex*end_vertex);
pair<int, int> dijkstra(vector<Graph_vertex>&graph, Graph_vertex* start_vertex, Graph_vertex* end_vertex) {
	// create map of distances and edges to vertices and fill it
	unordered_map<Graph_vertex*, pair<int, int>>dist_and_edges_to_vertex;
	for (auto& vertex : graph) {
		dist_and_edges_to_vertex.emplace(&vertex, pair<int, int>{ numeric_limits<int>::max(), 0 });
	}
	dist_and_edges_to_vertex[start_vertex].first = 0;
	dist_and_edges_to_vertex[start_vertex].second = 0;

	// create set of next vertices
	auto comp = [&dist_and_edges_to_vertex](Graph_vertex* f, Graph_vertex* s) {
		return dist_and_edges_to_vertex[f].first < dist_and_edges_to_vertex[s].first ||
			(dist_and_edges_to_vertex[f].first == dist_and_edges_to_vertex[s].first &&
				dist_and_edges_to_vertex[f].second < dist_and_edges_to_vertex[s].second);
	};
	set<Graph_vertex*, decltype(comp)>next_vertex{ comp };
	next_vertex.emplace(start_vertex);

	// visited virtices for undirected graph
	unordered_set<Graph_vertex*>visited;

	// save path
	unordered_map<Graph_vertex*, Graph_vertex*>path;
	path.emplace(start_vertex, nullptr);

	// dijkstra's algorithm
	while (!next_vertex.empty()) {
		Graph_vertex* current_vertex = *next_vertex.begin();
		visited.emplace(current_vertex);
		next_vertex.erase(current_vertex);
		if (current_vertex == end_vertex) {
			break;
		}

		for (auto& edge : current_vertex->adjacent_vertices_with_dist) {
			if (!visited.count(edge.first)) {
				int possible_dist = dist_and_edges_to_vertex[current_vertex].first + edge.second;
				int possible_edges = dist_and_edges_to_vertex[current_vertex].second + 1;
				if (possible_dist < dist_and_edges_to_vertex[edge.first].first ||
					(possible_dist == dist_and_edges_to_vertex[edge.first].first &&
						possible_edges < dist_and_edges_to_vertex[edge.first].second)) {
					next_vertex.erase(edge.first);
					dist_and_edges_to_vertex[edge.first].first = possible_dist;
					dist_and_edges_to_vertex[edge.first].second = possible_edges;
					next_vertex.emplace(edge.first);

					path[edge.first] = current_vertex;
				}
			}
		}
	}
	output_path(path, end_vertex);

	return dist_and_edges_to_vertex.at(end_vertex);
} // time O((|E|+|V|)log|V|); 
void output_path(const unordered_map<Graph_vertex*, Graph_vertex*>&path, Graph_vertex*end_vertex) {
	if (path.find(end_vertex) == path.end()) {
		cout << "No path found" << endl;
		return;
	}
	auto iter = end_vertex;
	while (iter) {
		cout << iter->id << " ";
		iter = path.at(iter);
	}
	cout << endl;
}

void small_test() {
	vector<Graph_vertex>graph(5);
	graph[0].id = 'A';
	graph[1].id = 'B';
	graph[2].id = 'C';
	graph[3].id = 'D';
	graph[4].id = 'E';

	graph[0].adjacent_vertices_with_dist.emplace_back(&graph[1], 4);
	graph[0].adjacent_vertices_with_dist.emplace_back(&graph[4], 2);

	graph[1].adjacent_vertices_with_dist.emplace_back(&graph[2],6);

	graph[3].adjacent_vertices_with_dist.emplace_back(&graph[2],6);

	graph[4].adjacent_vertices_with_dist.emplace_back(&graph[3], 2);

	auto res = dijkstra(graph, &graph[0], &graph[2]);
	assert(res.first == 10 && res.second == 2);
}

void main() {
	small_test();

	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 1000; ++i) {
		int n = uniform_int_distribution<>{ 2, 26 }(mt);
		vector<Graph_vertex>graph(n);
		for (int i = 0; i < graph.size();++i) {
			graph[i].id = 'a' + i;
		}

		vector<vector<bool>>connected(n, vector<bool>(n, false));
		for (int i = 1; i < graph.size(); ++i) {
			int len = uniform_int_distribution<>{ 1,100 }(mt);
			graph[i].adjacent_vertices_with_dist.emplace_back(&graph[i - 1],len);
			graph[i-1].adjacent_vertices_with_dist.emplace_back(&graph[i],len);
			connected[i][i - 1] = connected[i - 1][i] = true;
		}

		int m = uniform_int_distribution<>{ 1,n*(n - 1) / 2 }(mt);
		m -= (n - 1);
		while (m-- > 0) {
			int a, b;
			uniform_int_distribution<>dis{ 0,n - 1 };
			do {
				a = dis(mt);
				b = dis(mt);
			} while (a == b || connected[a][b]);
			connected[a][b] = connected[b][a] = true;
			int len = uniform_int_distribution<>{ 1,100 }(mt);
			graph[a].adjacent_vertices_with_dist.emplace_back(&graph[b], len);
			graph[b].adjacent_vertices_with_dist.emplace_back(&graph[a], len);
		}
		int start = uniform_int_distribution<>{ 0,n - 1 }(mt);
		int end = uniform_int_distribution<>{ 0,n - 1 }(mt);
		auto res = dijkstra(graph, &graph[start], &graph[end]);
		cout << res.first << " " << res.second << endl;
	}
	system("pause");
}