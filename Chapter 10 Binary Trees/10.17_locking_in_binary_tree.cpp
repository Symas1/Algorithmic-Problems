// implement locking in a binary tree
#include <memory>
#include <iostream>
#include <assert.h>
using namespace std;

struct Tree_node {
	int data;
	bool locked;
	unique_ptr<Tree_node>left, right;
	Tree_node* parent;
	int counter_locked;
}; // space O(n) for counter_locked

bool is_locked(const unique_ptr<Tree_node>&node)
{
	return node->locked;
} // time O(1), space O(1)

bool lock(const unique_ptr<Tree_node>&node)
{
	if (is_locked(node))return true;
	if (node->counter_locked == 0)
	{
		auto iter = node->parent;
		while (iter)
		{
			if (iter->locked)return false;
			iter = iter->parent;
		}
	}
	else return false;
	node->locked = true;
	auto iter = node->parent;
	while (iter)
	{
		++iter->counter_locked;
		iter = iter->parent;
	}
	return true;
} // time O(h) h - height, space O(1)

void unlock(const unique_ptr<Tree_node>&node)
{
	if (!is_locked(node))return;
	node->locked = false;
	auto iter = node->parent;
	while (iter)
	{
		--iter->counter_locked;
		iter = iter->parent;
	}
} // time O(h) h - height, space O(1)

void main()
{
	auto root = make_unique<Tree_node>(Tree_node());
	root->left = make_unique<Tree_node>(Tree_node());
	root->left->parent = root.get();
	root->right = make_unique<Tree_node>(Tree_node());
	root->right->parent = root.get();
	root->left->left= make_unique<Tree_node>(Tree_node());
	root->left->left->parent = root->left.get();
	root->left->right = make_unique<Tree_node>(Tree_node());
	root->left->right->parent = root->left.get();

	assert(!is_locked(root));
	cout << boolalpha << is_locked(root) << endl;

	assert(lock(root));
	assert(is_locked(root));
	cout << boolalpha << is_locked(root) << endl;
	assert(!lock(root->left));
	assert(!is_locked(root->left));
	assert(!lock(root->right));
	assert(!is_locked(root->right));
	assert(!lock(root->left->left));
	assert(!is_locked(root->left->left));
	assert(!lock(root->left->right));
	assert(!is_locked(root->left->right));

	unlock(root);
	assert(lock(root->left));
	assert(!lock(root));
	assert(!lock(root->left->left));
	assert(!is_locked(root));

	cout << boolalpha << is_locked(root) << endl;
	assert(lock(root->right));
	assert(is_locked(root->right));
	cout << boolalpha <<is_locked(root->right) << endl;
	system("pause");
}