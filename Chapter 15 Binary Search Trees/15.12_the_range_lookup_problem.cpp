// the range lookup problem
#include <memory>
#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <utility>
using namespace std;

struct Tree_node {
	Tree_node(int data_, unique_ptr<Tree_node>left_, unique_ptr<Tree_node>right_)
	{
		data = { data_ };
		left = move(left_);
		right = move(right);
	}
	int data;
	unique_ptr<Tree_node>left, right;
};

void range_lookup_helper(vector<int>&res, const unique_ptr<Tree_node>&node, const pair<int, int>&range);
vector<int> range_lookup(const unique_ptr<Tree_node>&root,const  pair<int, int>range)
{
	vector<int> res{};
	range_lookup_helper(res,root, range);
	return res;
} // time O(m+h) h - paths to range limits and m - elements between paths; space O(n) as tree not balanced
void range_lookup_helper(vector<int>&res, const unique_ptr<Tree_node>&node, const pair<int, int>&range)
{
	if (!node)return;
	if (node->data <= range.second && node->data >= range.first)
	{
		range_lookup_helper(res, node->left, range);
		res.emplace_back(node->data);
		range_lookup_helper(res, node->right, range);
	}
	else if (node->data < range.first)
	{
		range_lookup_helper(res, node->right, range);
	}
	else if (node->data > range.second)
	{
		range_lookup_helper(res, node->left, range);
	}
}

void inorder_range_helper(vector<int>&res, const unique_ptr<Tree_node>&node, const pair<int, int>&range);
vector<int> inorder_range(const unique_ptr<Tree_node>&root, const pair<int, int>range)
{
	vector<int>res{};
	inorder_range_helper(res, root, range);
	return res;
} // time O(n); space O(n)
void inorder_range_helper(vector<int>&res, const unique_ptr<Tree_node>&node, const pair<int, int>&range)
{
	if (!node)return;

	inorder_range_helper(res,node->left,range);
	if (node->data <= range.second && node->data >= range.first)
		res.emplace_back(node->data);
	inorder_range_helper(res, node->right, range);
}

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
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			auto res = range_lookup(root, { i,j });
			auto check = inorder_range(root, { i,j });
			assert(equal(res.begin(), res.end(), check.begin(), check.end()));
		}
	}
	system("pause");
}