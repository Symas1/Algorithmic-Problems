// test if a binary tree satisfies the BST property
#include <memory>
#include <iostream>
#include <utility>
#include <algorithm>
#include <numeric>
#include <queue>
#include <assert.h>
using namespace std;

struct Tree_node {
	Tree_node(int data_, unique_ptr<Tree_node>left_, unique_ptr<Tree_node>right_)
	{
		data={ data_ };
		left = move(left_);
		right = move(right);
	}
	int data;
	unique_ptr<Tree_node>left, right;
};

struct Range
{
	Range(int lower_, int upper_) :lower{ lower_ }, upper{ upper_ } {};
	int lower;
	int upper;
};

bool is_bst_first_helper(const unique_ptr<Tree_node>&node, pair<int, int>interval);
bool is_bst_first(const unique_ptr<Tree_node>& root)
{
	return is_bst_first_helper(root, { numeric_limits<int>::min(),numeric_limits<int>::max() });
} // time O(n) n - nodes; space O(h) h - height
bool is_bst_first_helper(const unique_ptr<Tree_node>&node, pair<int, int>interval)
{
	if (!node)return true;
	if (node->data<interval.first || node->data > interval.second)return false;

	return is_bst_first_helper(node->left, { interval.first,node->data }) && is_bst_first_helper(node->right, { node->data,interval.second });
}

bool is_bst_better(const unique_ptr<Tree_node>&root)
{
	if (!root)return true;
	queue<pair<const Tree_node*, Range>>q{};
	q.emplace(root.get(), Range{ numeric_limits<int>::min(),numeric_limits<int>::max() });
	while (!q.empty())
	{
		auto top = q.front();
		q.pop();
		if (top.first != nullptr)
		{
			if (top.first->data<top.second.lower || top.first->data>top.second.upper)return false;
			q.emplace(top.first->left.get(), Range{ top.second.lower,top.first->data });
			q.emplace(top.first->right.get(), Range{ top.first->data ,top.second.upper });
		}
	}
	return true;
} // time O(n); space O(n)

bool is_bst_third_helper(const unique_ptr<Tree_node>&node, int& last_visited);
bool is_bst_third(const unique_ptr<Tree_node>&root)
{
	int last_visited = numeric_limits<int>::min();
	return is_bst_third_helper(root,last_visited);
} // time O(n) n - nodes; space O(h) h - height
bool is_bst_third_helper(const unique_ptr<Tree_node>&node,int& last_visited)
{
	if (!node)
	{
		return true;
	}

	if (!is_bst_third_helper(node->left, last_visited))return false;
	if (last_visited > node->data)return false;

	last_visited = node->data;

	if (!is_bst_third_helper(node->right, last_visited))return false;

	return true;
}

unique_ptr<Tree_node> gen_tree()
{
	auto head = make_unique<Tree_node>(19, nullptr, nullptr);
	head->left = make_unique<Tree_node>(7, nullptr, nullptr);
	head->left->left = make_unique<Tree_node>(3, nullptr, nullptr);
	head->left->left->left = make_unique<Tree_node>(2, nullptr, nullptr);
	head->left->left->right = make_unique<Tree_node>(5, nullptr, nullptr);
	head->left->right = make_unique<Tree_node>(11, nullptr, nullptr);
	head->left->right->right = make_unique<Tree_node>(17, nullptr, nullptr);
	head->left->right->right->left = make_unique<Tree_node>(13, nullptr, nullptr);

	head->right = make_unique<Tree_node>(43, nullptr, nullptr);
	head->right->left = make_unique<Tree_node>(23, nullptr, nullptr);
	head->right->left->right = make_unique<Tree_node>(37, nullptr, nullptr);
	head->right->left->right->left = make_unique<Tree_node>(29, nullptr, nullptr);
	head->right->left->right->left->right = make_unique<Tree_node>(31, nullptr, nullptr);
	head->right->left->right->right = make_unique<Tree_node>(41, nullptr, nullptr);
	head->right->right = make_unique<Tree_node>(47, nullptr, nullptr);
	head->right->right->right = make_unique<Tree_node>(53, nullptr, nullptr);

	return head;
}

void main()
{
	auto head = gen_tree();
	assert(is_bst_first(head));
	assert(is_bst_third(head));
	assert(is_bst_better(head));
	head->data = 100;
	assert(!is_bst_first(head));
	assert(!is_bst_third(head));
	assert(!is_bst_better(head));
	system("pause");
}