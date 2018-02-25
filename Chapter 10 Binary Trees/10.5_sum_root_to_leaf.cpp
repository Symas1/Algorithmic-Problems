// sum the root-to-leaf paths in a binary tree
#include <memory>
#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

struct Tree_node {
	bool data;
	unique_ptr<Tree_node> left, right;
};

void sum_helper(const unique_ptr<Tree_node>&node, int& sum, int& current);
int sum(const unique_ptr<Tree_node>&root)
{
	int res = 0;
	int current = 0;
	sum_helper(root, res, current);
	return res;
} // time O(n) n - nodes, space O(h) h - height

void sum_helper(const unique_ptr<Tree_node>&node, int& sum, int& current)
{
	if (!node || !node->left && !node->right)
	{
		current = (current << 1) | node->data;
		sum += current;
		return;
	}
	current = (current << 1) | node->data;
	if (node->left)
	{
		sum_helper(node->left, sum, current);
		current = current >> 1;
	}
	if (node->right)
	{
		sum_helper(node->right, sum, current);
		current = current >> 1;
	}
}

void main()
{
	unique_ptr<Tree_node>root = make_unique<Tree_node>(Tree_node{ 1 });
	root->left= make_unique<Tree_node>(Tree_node{ 0 });
	root->left->left = make_unique<Tree_node>(Tree_node{ 0 });
	root->left->left->left = make_unique<Tree_node>(Tree_node{ 0 });
	root->left->left->right = make_unique<Tree_node>(Tree_node{ 1 });
	root->left->right  = make_unique<Tree_node>(Tree_node{ 1 });
	root->left->right->right = make_unique<Tree_node>(Tree_node{ 1 });
	root->left->right->right->left = make_unique<Tree_node>(Tree_node{ 0 });

	root->right = make_unique<Tree_node>(Tree_node{ 1 });
	root->right->left = make_unique<Tree_node>(Tree_node{ 0 });
	root->right->left->right = make_unique<Tree_node>(Tree_node{ 0 });
	root->right->left->right->left = make_unique<Tree_node>(Tree_node{ 1 });
	root->right->left->right->left->right = make_unique<Tree_node>(Tree_node{ 1 });
	root->right->left->right->right = make_unique<Tree_node>(Tree_node{ 0 });
	root->right->right = make_unique<Tree_node>(Tree_node{ 0 });
	root->right->right->right = make_unique<Tree_node>(Tree_node{ 0 });
	assert(sum(root) == 126);
	system("pause");
}