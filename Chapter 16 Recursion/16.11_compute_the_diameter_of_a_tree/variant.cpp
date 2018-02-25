// Thoughts on how real program would work.
// We would have a thread pool. Threads would get nodes from sychronized_priority_queue of Tree_nodes* 
	// with top element with the most kids
// We would push root node to this s_p_queue. Some thread would work for root node and would push its kids to 
	// our sychronized_priority_queue and so on until empty
// One thing to remember is that after starting to work for new node thread would have to wait for 1 sec as
	// written in task

#include <vector>
#include <memory>
#include <iostream>
#include <map>
#include <stack>
#include <functional>
#include <queue>
#include <algorithm>
using namespace std;

struct Tree_node {
	Tree_node(char iden, int k) :identificator{ iden }, kids{ k }{}
	struct Edge {
		unique_ptr<Tree_node> root;
	};
	char identificator;
	int kids;
	vector<Edge>edges;
};

struct Comparator {
	bool operator()(const Tree_node* a, const Tree_node* b) {
		return less<>{}(a->kids, b->kids);
	}
};

void add_kids_to_priority_queue(priority_queue<Tree_node*, vector<Tree_node*>, Comparator>&p_queue,
	const Tree_node* node);
void compute_sequence_helper(queue<Tree_node*>&result,
	priority_queue<Tree_node*, vector<Tree_node*>, Comparator>&p_queue);
queue<Tree_node*> compute_sequence(const unique_ptr<Tree_node>&root) {
	if (!root) {
		return{};
	}

	queue<Tree_node*>result{};
	priority_queue<Tree_node*, vector<Tree_node*>, Comparator>most_kids;
	most_kids.emplace(root.get());

	compute_sequence_helper(result, most_kids);

	return result;
} // time O(n) n - nodes in tree; space O(n)
void compute_sequence_helper(queue<Tree_node*>&result,
	priority_queue<Tree_node*, vector<Tree_node*>, Comparator>&p_queue) {
	while (!p_queue.empty()) {
		auto most_kids = p_queue.top();
		p_queue.pop();

		result.emplace(most_kids);
		add_kids_to_priority_queue(p_queue, most_kids);
	}
}
void add_kids_to_priority_queue(priority_queue<Tree_node*, vector<Tree_node*>, Comparator>&p_queue,
	const Tree_node* node) {
	for (const auto& edge : node->edges) {
		p_queue.emplace(edge.root.get());
	}
}

void test();

void main() {
	test();
	system("pause");
}

void test() {
	auto root = make_unique<Tree_node>('a', 6);

	root->edges.emplace_back(Tree_node::Edge{ make_unique<Tree_node>('b', 4) });
	root->edges.emplace_back(Tree_node::Edge{ make_unique<Tree_node>('c', 0) });

	root->edges[0].root->edges.emplace_back(Tree_node::Edge{ make_unique<Tree_node>('d', 1) });
	root->edges[0].root->edges.emplace_back(Tree_node::Edge{ make_unique<Tree_node>('e', 1) });
	root->edges[0].root->edges.emplace_back(Tree_node::Edge{ make_unique<Tree_node>('g', 1) });

	root->edges[0].root->edges[0].root->edges.emplace_back(Tree_node::Edge{ make_unique<Tree_node>('k', 0) });

	auto res = compute_sequence(root);
	// a b d ...
	while (!res.empty()) {
		cout << res.front()->identificator << endl;
		res.pop();
	}
}