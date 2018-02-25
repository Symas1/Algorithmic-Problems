// compute the successor
#include <memory>
#include <iostream>
#include <assert.h>
#include <functional>
#include <vector>
using namespace std;

struct Tree_node {
	int data;
	unique_ptr<Tree_node>left, right;
	Tree_node* parent;
};

Tree_node* successor(const unique_ptr<Tree_node>&node)
{
	if (node->right)
	{
		auto iter = node->right.get();
		while (iter->left)iter = iter->left.get();
		return iter;
	}
	else
	{
		auto prev = node.get();
		auto iter = node->parent;
		while (iter && iter->left.get() != prev)
		{
			prev = iter;
			iter = iter->parent;
		}
		return iter;
	}
	return nullptr;
} // time O(h), space O(1)
 
pair<bool,const unique_ptr< Tree_node>&> kth_helper(const unique_ptr<Tree_node>&node, const int& k, int& counter);
const unique_ptr< Tree_node>& kth(const unique_ptr<Tree_node>&node,const int& k)
{
	int counter = 0;
	return kth_helper(node, k, counter).second;
}
pair<bool, const unique_ptr< Tree_node>&> kth_helper(const unique_ptr<Tree_node>&node, const int& k, int& counter)
{
	if (!node)return{ false,nullptr };
	auto left = kth_helper(node->left, k, counter);
	if (left.first)return left;
	++counter;
	if (k == counter)return{ true,node };
	auto right = kth_helper(node->right, k, counter);
	if (right.first)return right;
	return{ false,nullptr };
}

unique_ptr<Tree_node> build_tree()
{
	unique_ptr<Tree_node>root = make_unique<Tree_node>(Tree_node{ 314,nullptr,nullptr,nullptr });
	root->left = make_unique<Tree_node>(Tree_node{ 6,nullptr,nullptr,root.get() });
	root->left->left = make_unique<Tree_node>(Tree_node{ 271,nullptr,nullptr,root->left.get() });
	root->left->left->left = make_unique<Tree_node>(Tree_node{ 28,nullptr,nullptr,root->left->left.get() });
	root->left->left->right = make_unique<Tree_node>(Tree_node{ 0,nullptr,nullptr,root->left->left.get() });
	root->left->right = make_unique<Tree_node>(Tree_node{ 561,nullptr,nullptr,root->left.get() });
	root->left->right->right = make_unique<Tree_node>(Tree_node{ 3,nullptr,nullptr,root->left->right.get() });
	root->left->right->right->left = make_unique<Tree_node>(Tree_node{ 17,nullptr,nullptr,root->left->right->right.get() });
	root->right = make_unique<Tree_node>(Tree_node{ 6,nullptr,nullptr,root.get() });
	root->right->left = make_unique<Tree_node>(Tree_node{ 2,nullptr,nullptr,root->right.get() });
	root->right->left->right = make_unique<Tree_node>(Tree_node{ 1,nullptr,nullptr,root->right->left.get() });
	root->right->left->right->left = make_unique<Tree_node>(Tree_node{ 401,nullptr,nullptr,root->right->left->right.get() });
	root->right->left->right->left->right = make_unique<Tree_node>(Tree_node{ 641,nullptr,nullptr,root->right->left->right->left.get() });
	root->right->left->right->right = make_unique<Tree_node>(Tree_node{ 257,nullptr,nullptr,root->right->left->right.get() });
	root->right->right = make_unique<Tree_node>(Tree_node{ 271,nullptr,nullptr,root->right.get() });
	root->right->right->right = make_unique<Tree_node>(Tree_node{ 28,nullptr,nullptr,root->right->right.get() });
	return root;
}

void main()
{
	auto root = build_tree();
	vector<int>check{ 28,271,0,6,561,17,3,314,2,401,641,1,257,6,271,28 };
	for (int i = 0; i < check.size(); ++i)
	{
		if (i + 1 == check.size())
		{
			assert(!successor(kth(root, i + 1)));
			continue;
		}
		assert(successor(kth(root, i + 1)) == kth(root, i + 2).get());
	}
	system("pause");
}