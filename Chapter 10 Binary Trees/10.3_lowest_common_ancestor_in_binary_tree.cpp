// compute the lowest common ancestor in a binary tree
#include <memory>
#include <assert.h>
#include <iostream>
#include <deque>
#include <functional>
#include <stdexcept>
#include <algorithm>
using namespace std;

struct Tree_node {
	int data;
	unique_ptr<Tree_node>left, right;
};

bool path_helper(const unique_ptr<Tree_node>&current, const unique_ptr<Tree_node>&node, deque<Tree_node*>&que)
{
	if (!current)return false;
	else
	{
		que.emplace_back(current.get());
		if (current == node)return true;
		if (path_helper(current->left, node, que) || path_helper(current->right, node, que))
			return true;
		else que.pop_back();
	}
	return false;
}
deque<Tree_node*> path(const unique_ptr<Tree_node>&root, const unique_ptr<Tree_node>&node)
{
	deque<Tree_node*>path{};
	path_helper(root, node, path);
	return path;
}

int lowest(const unique_ptr<Tree_node>& root,const unique_ptr<Tree_node>& first, const unique_ptr<Tree_node>&second)
{
	if (first == root || second == root)throw invalid_argument("Root can't have an ancestor");
	int ret = root->data;
	auto path_first = path(root, first);
	auto path_second = path(root, second);
	path_first.pop_back();
	path_second.pop_back();

	while (!path_first.empty() && !path_second.empty() && path_first.front() == path_second.front())
	{
		ret = min(ret, path_first.front()->data);
		path_first.pop_front();
		path_second.pop_front();
	}
	return ret;
} // time O(n) n - number of nodes; space O(h) h - height of the tree


pair<int, Tree_node*> lca_helper(const unique_ptr<Tree_node>& root, const unique_ptr<Tree_node>& first, const unique_ptr<Tree_node>&second)
{
	if (root == nullptr)return{ 0,nullptr };

	auto left = lca_helper(root->left, first, second);
	if (left.first == 2)return left;

	auto right = lca_helper(root->right, first, second);
	if (right.first == 2)return right;

	int res = left.first + right.first + (root == first) + (root == second);
	return{ res,res==2?root.get():nullptr };
}
Tree_node* lca(const unique_ptr<Tree_node>& root, const unique_ptr<Tree_node>& first, const unique_ptr<Tree_node>&second)
{
	return lca_helper(root, first, second).second;
} // time O(n) n - nodes; space O(h) h - height of the tree



void test();

void main()
{
	void test();

	system("pause");
}

void test()
{
	{
		auto root = make_unique<Tree_node>(Tree_node{ 1 });
		root->left = make_unique<Tree_node>(Tree_node{ 0 });
		root->left->left = make_unique<Tree_node>(Tree_node{ 2 });
		root->left->right = make_unique<Tree_node>(Tree_node{ 3 });

		assert(lowest(root, root->left->left, root->left->right) == 0);
		assert(lca(root, root->left->left, root->left->right)->data == 0);
	}

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

		const unique_ptr<Tree_node>& m = root->right->left->right->left->right;
		const unique_ptr<Tree_node>& n = root->right->left->right->right;

		assert(lowest(root, m, n) == 1);
		assert(lca(root, m, n)->data == 1);
	}
}