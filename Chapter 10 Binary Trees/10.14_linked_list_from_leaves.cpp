// Form a linked list from the leaves of a binary tree
#include <memory>
#include <iostream>
#include <assert.h>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;

struct Tree_node {
	int data;
	unique_ptr<Tree_node>left, right;
};

void linked_help(const unique_ptr<Tree_node>&node,list<int>& res);
list<int> linked(const unique_ptr<Tree_node>& root)
{
	list<int>res{};
	linked_help(root, res);
	return res;
} // time O(n) n - nodes; space O(h) h - height
void linked_help(const unique_ptr<Tree_node>&node, list<int>& res)
{
	if (!node)return;
	if (!node->left && !node->right)
	{
		res.emplace_back(node->data);
		return;
	}

	linked_help(node->left,res);
	linked_help(node->right, res);
}

unique_ptr<Tree_node> build_tree()
{
	unique_ptr<Tree_node>root = make_unique<Tree_node>(Tree_node{ 314,nullptr,nullptr });
	root->left = make_unique<Tree_node>(Tree_node{ 6,nullptr,nullptr });
	root->left->left = make_unique<Tree_node>(Tree_node{ 271,nullptr,nullptr });
	root->left->left->left = make_unique<Tree_node>(Tree_node{ 28,nullptr,nullptr });
	root->left->left->right = make_unique<Tree_node>(Tree_node{ 0,nullptr,nullptr });
	root->left->right = make_unique<Tree_node>(Tree_node{ 561,nullptr,nullptr });
	root->left->right->right = make_unique<Tree_node>(Tree_node{ 3,nullptr,nullptr });
	root->left->right->right->left = make_unique<Tree_node>(Tree_node{ 17,nullptr,nullptr });
	root->right = make_unique<Tree_node>(Tree_node{ 6,nullptr,nullptr });
	root->right->left = make_unique<Tree_node>(Tree_node{ 2,nullptr,nullptr });
	root->right->left->right = make_unique<Tree_node>(Tree_node{ 1,nullptr,nullptr });
	root->right->left->right->left = make_unique<Tree_node>(Tree_node{ 401,nullptr,nullptr });
	root->right->left->right->left->right = make_unique<Tree_node>(Tree_node{ 641,nullptr,nullptr });
	root->right->left->right->right = make_unique<Tree_node>(Tree_node{ 257,nullptr,nullptr });
	root->right->right = make_unique<Tree_node>(Tree_node{ 271,nullptr,nullptr });
	root->right->right->right = make_unique<Tree_node>(Tree_node{ 28,nullptr,nullptr });
	return root;
}

void main()
{
	auto l = linked(build_tree());
	list<int>check{ 28,0,17,641,257,28 };
	assert(equal(l.begin(), l.end(), check.begin()));
	system("pause");
}