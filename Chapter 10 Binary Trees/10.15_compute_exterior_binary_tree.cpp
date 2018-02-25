// compute the exterior of a binary tree
#include <memory>
#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
using namespace std;

struct Tree_node {
	int data;
	unique_ptr<Tree_node>left, right;
};

void add_left(const unique_ptr<Tree_node>&node, vector<int>&res);
void add_bottom(const unique_ptr<Tree_node>&node, vector<int>&res);
void add_right(const unique_ptr<Tree_node>&node, vector<int>&res);
vector<int> exterior(const unique_ptr<Tree_node>&root)
{
	vector<int> res{};
	add_left(root, res);
	add_bottom(root, res);
	add_right(root, res);
	return res;
}
void add_left(const unique_ptr<Tree_node>&node, vector<int>&res)
{
	auto iter = node.get();
	while (iter)
	{
		res.emplace_back(iter->data);
		iter = iter->left ? iter->left.get() : (iter->right) ? iter->right.get() : nullptr;
	}
	res.pop_back();
}
void add_bottom(const unique_ptr<Tree_node>&node, vector<int>&res)
{
	if (!node)return;
	if (!node->left && !node->right)
	{
		res.emplace_back(node->data);
		return;
	}

	add_bottom(node->left, res);
	add_bottom(node->right, res);
}
void add_right(const unique_ptr<Tree_node>&node, vector<int>&res)
{
	auto iter = node.get();
	iter = iter->right ? iter->right.get() : (iter->left) ? iter->left.get() : nullptr;
	int counter = 0;
	while (iter)
	{
		++counter;
		res.emplace_back(iter->data);
		iter = iter->right ? iter->right.get() : (iter->left) ? iter->left.get() : nullptr;
	}
	res.pop_back();
	reverse(res.rbegin(), res.rbegin() + counter -1);
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

void left_exterior2(const unique_ptr<Tree_node>&node, vector<int>& res, bool& reached_leaf);
void right_exterior2(const unique_ptr<Tree_node>&node, vector<int>& res, bool boundary);
vector<int> exterior2(const unique_ptr<Tree_node>& root)
{
	vector<int>res{};
	res.emplace_back(root->data);
	bool reached = false;
	left_exterior2(root->left, res, reached);
	right_exterior2(root->right, res, true);
	return res;
} // time O(n) n - nodes, space O(h) h - height
void left_exterior2(const unique_ptr<Tree_node>&node, vector<int>& res, bool& reached_leaf)
{
	if (!node)return;
	if (!node->left && !node->right)reached_leaf = true;

	if (!reached_leaf)res.emplace_back(node->data);
	else if (!node->left && !node->right)res.emplace_back(node->data);

	left_exterior2(node->left, res, reached_leaf);
	left_exterior2(node->right, res, reached_leaf);
}
void right_exterior2(const unique_ptr<Tree_node>&node, vector<int>& res, bool boundary)
{
	if (!node)return;
	right_exterior2(node->left, res, boundary && node->right == nullptr);
	right_exterior2(node->right, res, boundary);
	if (boundary || (!node->left && !node->right))res.emplace_back(node->data);
}

void main()
{
	auto res = exterior2(build_tree());
	vector<int>check{ 314,6,271,28,0,17,641,257,28,271,6 };
	assert(equal(res.begin(), res.end(), check.begin(),check.end()));
	system("pause");
}