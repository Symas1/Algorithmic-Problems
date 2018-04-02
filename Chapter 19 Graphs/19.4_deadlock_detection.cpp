// deadlock detection
#include <vector>
#include <algorithm>
#include <random>
#include <assert.h>
#include <iostream>
#include <functional>
using namespace std;

struct Graph_vertex {
	enum Color{white,gray,black}color=white;
	vector<reference_wrapper<Graph_vertex>>edges{};
};

bool has_cylce(Graph_vertex& vertex);
bool is_deadlocked(vector<Graph_vertex>&vertices) {
	return any_of(vertices.begin(), vertices.end(), [](Graph_vertex& v) {
		return v.color == Graph_vertex::Color::white && has_cylce(v);
	});
} // DFS complexity: time O(|V|+|E|); space O(|V|) V - vertices, E - edges

bool has_cylce(Graph_vertex & vertex)
{
	if (vertex.color == Graph_vertex::Color::gray) {
		return true;
	}

	vertex.color = Graph_vertex::Color::gray;
	for (auto& v:vertex.edges) {
		if (v.get().color != Graph_vertex::Color::black && has_cylce(v.get())) {
			return true;
		}
	}
	vertex.color = Graph_vertex::Color::black;
	return false;
}

bool has_cycle_exclusion(Graph_vertex& vertex) {
	if (vertex.color == Graph_vertex::black) {
		return true;
	}
	vertex.color = Graph_vertex::black;
	for (auto& v:vertex.edges) {
		if (has_cycle_exclusion(v.get())) {
			return true;
		}
	}
	return true;
}
bool check_answer(vector<Graph_vertex>&vertices) {
	for (auto& v : vertices) {
		v.color = Graph_vertex::white;
	}

	for (auto &v : vertices) {
		if (has_cycle_exclusion(v)) {
			return true;
		}

		for (auto&n : vertices) {
			n.color = Graph_vertex::white;
		}
	}
	return false;
} // O(n^2)

void small_test() {
	vector<Graph_vertex>arr(4, {});
	arr[0].edges.emplace_back(arr[1]);
	arr[0].edges.emplace_back(arr[2]);
	arr[1].edges.emplace_back(arr[3]);
	arr[3].edges.emplace_back(arr[2]);
	arr[2].edges.emplace_back(arr[0]);
	assert(is_deadlocked(arr));
	assert(check_answer(arr));
}

void main() {
	small_test();
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 10000; ++i) {
		vector<Graph_vertex>vertices(uniform_int_distribution<>{2, 20}(mt));
		vector<vector<bool>>edge_exists(vertices.size(), vector<bool>(vertices.size(), false));
		for (int i = 1; i < vertices.size(); ++i) {
			vertices[i - 1].edges.emplace_back(vertices[i]);
			vertices[i].edges.emplace_back(vertices[i - 1]);
			edge_exists[i - 1][i] = edge_exists[i][i-1] = true;
		}
		int edges = uniform_int_distribution<>( 1,2 )(mt);
		edges -= vertices.size() - 1;
		while (edges-- > 0) {
			int a, b;
			do {
				uniform_int_distribution<>dis( 0,vertices.size() - 1 );
				a = dis(mt);
				b = dis(mt);
			} while (a == b || edge_exists[a][b]);
			edge_exists[a][b] = true;
			vertices[a].edges.emplace_back(vertices[b]);
			vertices[b].edges.emplace_back(vertices[a]);
		}
		bool res = is_deadlocked(vertices);
		if(!res)cout << boolalpha << res << endl;
		assert(check_answer(vertices) == res);
	}
	system("pause");
}