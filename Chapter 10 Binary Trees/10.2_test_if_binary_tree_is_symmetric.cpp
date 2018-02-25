// test if a binary tree is symmetric
#include <memory>
#include <iostream>
#include <assert.h>
using namespace std;

struct Tree_node {
	int data;
	unique_ptr<Tree_node>left, right;
};

bool helper(const unique_ptr<Tree_node>&left, const unique_ptr<Tree_node>&right);
bool symmetric(const unique_ptr<Tree_node>&root)
{

	return !root || helper(root->left, root->right);
} // time O(n) n - number of nodes; space O(h) h - height of the tree

bool helper(const unique_ptr<Tree_node>&left, const unique_ptr<Tree_node>&right)
{
	if (!left && !right)return true;
	else if (left && right)
	{
		return left->data == right->data &&
			helper(left->left, right->right) &&
			helper(left->right, right->left);
	}
	return false;
}

void main()
{
	auto root = make_unique<Tree_node>(Tree_node{ 1 });

	root->left = make_unique<Tree_node>(Tree_node{ 2 });
	root->right = make_unique<Tree_node>(Tree_node{ 2 });

	root->left->right = make_unique<Tree_node>(Tree_node{ 3 });
	root->right->left = make_unique<Tree_node>(Tree_node{ 3 });

	root->left->right->right = make_unique<Tree_node>(Tree_node{ 4 });
	root->right->left->left = make_unique<Tree_node>(Tree_node{ 4 });

	assert(symmetric(root));
	system("pause");
}