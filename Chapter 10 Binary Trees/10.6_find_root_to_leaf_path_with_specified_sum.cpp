// find a root to leaf path with specified sum
#include <memory>
#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>
using namespace std;

struct Tree_node {
	int data;
	unique_ptr<Tree_node>left, right;
};

bool path_helper(const unique_ptr<Tree_node>& node, const int& weight, int current_sum = 0);
bool path(const unique_ptr<Tree_node>& root, const int& weight)
{
	return path_helper(root, weight);
} // time O(n) n - nodes, space O(h) h - height

bool path_helper(const unique_ptr<Tree_node>& node, const int& weight, int current_sum)
{
	if (!node)return false;
	current_sum += node->data;
	if (current_sum == weight && !node->left && !node->right)return true;

	return path_helper(node->left, weight, current_sum) || path_helper(node->right, weight, current_sum);
}

void variant1_helper(const unique_ptr<Tree_node>& node, const int& weight, vector<int>curr_vec,vector<vector<int>>&res);
vector<vector<int>> variant1(const unique_ptr<Tree_node>& root, const int& weight)
{
	vector<vector<int>>res{};
	variant1_helper(root, weight, {},res);
	return res;
} // time O(n) n - nodes, space O(h) h - height

void variant1_helper(const unique_ptr<Tree_node>& node, const int& weight, vector<int>curr_vec, vector<vector<int>>&res)
{
	if (!node)return;
	if (!node->left && !node->right)
	{
		if (weight == node->data)
		{
			curr_vec.emplace_back(node->data);
			res.emplace_back(curr_vec);
		}
		return;
	}
	curr_vec.emplace_back(node->data);
	variant1_helper(node->left, weight - node->data, curr_vec, res);
	variant1_helper(node->right, weight - node->data, curr_vec, res);
}

void test_path();
void test_variant();
void main()
{
	test_path();
	test_variant();
	system("pause");
}

void test_path()
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
	assert(path(root, 591));
	assert(path(root, 619));
	assert(path(root, 901));
	assert(path(root, 1365));
	assert(path(root, 580));
	assert(path(root, 619));
	assert(!path(root, 1));
}

void test_variant()
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

	auto res = variant1(root, 619);
	vector<int>check1 = { 314,6,271,28 };
	vector<int>check2 = { 314,6,271,28 };
	assert(equal(res[0].begin(), res[0].end(),check1.begin())&&equal(res[1].begin(), res[1].end(), check2.begin())&&res.size()==2);
}