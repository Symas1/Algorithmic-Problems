// compute the LCA when nodes have parent pointers
#include <memory>
#include <iostream>
#include <assert.h>
using namespace std;

struct Tree_node {
	int data;
	unique_ptr<Tree_node>left, right;
	Tree_node* parent;
};


int height(const unique_ptr<Tree_node>&node)
{
	auto current = node.get();
	int res = 0;
	while (current->parent)
	{
		++res;
		current = current->parent;
	}
	return res;
}
Tree_node* lca(const unique_ptr<Tree_node>&first, const unique_ptr<Tree_node>&second)
{
	auto first_height = height(first);
	auto second_height = height(second);
	auto first_iter = first.get();
	auto second_iter = second.get();
	while (first_height != second_height)
	{
		if (first_height > second_height)first_iter = first_iter->parent, first_height--;
		else if (first_height < second_height) second_iter = second_iter->parent, second_height--;
	}

	while (first_iter != second_iter && first_iter->parent)
	{
		first_iter = first_iter->parent;
		second_iter = second_iter->parent;
	}
	return first_iter;
} // time O(h), space O(1)

void main()
{
	{
		unique_ptr<Tree_node>root = make_unique<Tree_node>(Tree_node{ 0 });
		root->left = make_unique<Tree_node>(Tree_node{ 1,nullptr,nullptr,root.get() });
		root->left->left = make_unique<Tree_node>(Tree_node{ 2,nullptr,nullptr,root->left.get() });
		root->right = make_unique<Tree_node>(Tree_node{ 3,nullptr,nullptr,root.get() });
		assert(lca(root->left->left, root->right) == root.get());
	}

	{
		unique_ptr<Tree_node>root = make_unique<Tree_node>(Tree_node{ 0 });
		root->left = make_unique<Tree_node>(Tree_node{ 1,nullptr,nullptr,root.get() });
		root->left->left = make_unique<Tree_node>(Tree_node{ 2,nullptr,nullptr,root->left.get() });
		root->left->right = make_unique<Tree_node>(Tree_node{ 3,nullptr,nullptr,root->left.get() });
		assert(lca(root->left->left, root->left->right) == root->left.get());
	}


	system("pause");
}