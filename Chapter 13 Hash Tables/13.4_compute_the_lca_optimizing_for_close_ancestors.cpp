// compute the lca optimizing for close ancestors
#include <unordered_set>
#include <memory>
#include <iostream>
#include <assert.h>
using namespace std;

struct Tree_node {
	unique_ptr<Tree_node>left, right;
	Tree_node* parent;
};

Tree_node* lca(const unique_ptr<Tree_node>& first, const unique_ptr<Tree_node>& second)
{
	unordered_set<const Tree_node*>set{};
	auto first_iter = first.get();
	auto second_iter = second.get();
	while (first_iter || second_iter)
	{
		if (first_iter)
		{
			if (set.count(first_iter))return first_iter;
			else
			{
				set.emplace(first_iter);
				first_iter = first_iter->parent;
			}
		}
		if (second_iter)
		{
			if (set.count(second_iter))return second_iter;
			else
			{
				set.emplace(second_iter);
				second_iter = second_iter->parent;
			}
		}
	}
	return nullptr;
} // time O(h) h - height of the tree;space worst-case O(h), average O(d1+d2) d* - distances from lca to node

int main(int argc, char* argv[])
{
	auto root = make_unique<Tree_node>(Tree_node{nullptr,nullptr,nullptr});
	root->left= make_unique<Tree_node>(Tree_node{ nullptr,nullptr, root.get()});
	root->right = make_unique<Tree_node>(Tree_node{ nullptr,nullptr, root.get() });
	root->right->left = make_unique<Tree_node>(Tree_node{ nullptr,nullptr, root->right.get() });
	root->right->left->left = make_unique<Tree_node>(Tree_node{ nullptr,nullptr, root->right->left.get() });
	root->right->right = make_unique<Tree_node>(Tree_node{ nullptr,nullptr, root->right.get() });

	assert(lca(root, root) == root.get()); // the same element
	assert(lca(root->left, root->right) == root.get()); // the same depth
	assert(lca(root->right->left->left, root->right->right) == root->right.get()); // left node deeper
	assert(lca(root->right->right, root->left) == root.get()); // right node deeper
	system("pause");
	return 0;
}