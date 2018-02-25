// compute the lca in a BST
#include <memory>
#include <iostream>
#include <assert.h>
using namespace std;

struct Tree_node {
	Tree_node(int data_, unique_ptr<Tree_node>left_, unique_ptr<Tree_node> right_)
	{
		data = { data_ };
		left = move(left_);
		right = move(right_);
	}
	int data;
	unique_ptr<Tree_node>left, right;
};

Tree_node* lca(const unique_ptr<Tree_node>&root, const unique_ptr<Tree_node>&first, const unique_ptr<Tree_node>&second)
{
	auto iter = root.get();
	while (iter)
	{
		if (first->data < iter->data && second->data < iter->data)
		{
			iter = iter->left.get();
		}
		else if (first->data > iter->data && second->data > iter->data)
		{
			iter = iter->right.get();
		}
		else return iter;
	}
	return nullptr;
} // time O(h); space O(h) h - height

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
	auto root = gen_tree();
	assert(lca(root, root, root->left) == root.get());
	assert(lca(root, root->left->left, root->left->right->right->left) == root->left.get());
	assert(lca(root, root->left, root->right) == root.get());
	system("pause");
}