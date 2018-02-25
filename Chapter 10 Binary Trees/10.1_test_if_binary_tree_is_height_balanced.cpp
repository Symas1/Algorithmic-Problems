// test if a binary tree is height balanced
#include <memory>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <functional>
#include <tuple>
#include <stdexcept>
using namespace std;

struct Tree_node {
	int data;
	unique_ptr<Tree_node>left, right;
};

pair<bool, int> balanced_helper(const unique_ptr<Tree_node>&node);
bool balanced(const unique_ptr<Tree_node>&root)
{
	return balanced_helper(root).first;
} // time O(n) n - nodes; space O(h) h - height
pair<bool, int> balanced_helper(const unique_ptr<Tree_node>&node)
{
	if (!node)return make_pair(true, -1);

	auto left_tree = balanced_helper(node->left);
	if (!left_tree.first)return make_pair(false, 0);

	auto right_tree = balanced_helper(node->right);
	if (!right_tree.first)return make_pair(false, 0);

	bool balanced = abs(left_tree.second - right_tree.second) <= 1;
	int height = max(left_tree.second, right_tree.second) + 1;
	return make_pair(balanced, height);
}

struct var
{
	int height;
	int width;
};
var variant1_helper(const unique_ptr<Tree_node>& root, int& height);
int variant1(const unique_ptr<Tree_node>& root)
{
	int height = 0;
	variant1_helper(root, height);
	return height;
}
var variant1_helper(const unique_ptr<Tree_node>& root, int&height)
{
	if (!root)return{};
	var current;
	auto left = variant1_helper(root->left, height);
	auto right = variant1_helper(root->right, height);

	if (!root->left && !root->right)current = { 0,1 };
	else if (!root->right)current = { 1,1 };
	else if (!root->left)current = { 0,1 };
	else
	{
		if (left.height - 1 == right.height && right.width == (int)pow(2,right.height) )
		{
			current = { left.height + 1,left.width };
		}
		else if (left.height > right.height)
		{
			current = { right.height + 1,2 * right.width };
		}
		else if (left.height == right.height && left.width == (int)pow(2, left.height))
		{
			current = { left.height + 1,left.width + right.width };
		}
		else if (left.height == right.height && left.width < (int)pow(2, left.height))
		{
			current = { left.height,left.width };
		}
		else if (left.height < right.height && left.width == (int)pow(2, left.height))
		{
			current = { left.height + 1,2 * left.width };
		}
		else if (left.height < right.height && left.width < (int)pow(2, left.height))
		{
			current = { left.height + 1,left.width };
		}
	}
	height = max(height, current.height);
	return current;
}

void test_balance();
void test_variant1();

void main()
{
	//test_balance();
	test_variant1();
	system("pause");
}

void test_balance()
{
	unique_ptr<Tree_node>root = make_unique<Tree_node>(Tree_node{});
	root->left = make_unique<Tree_node>(Tree_node{});
	root->left->left = make_unique<Tree_node>(Tree_node{});

	root->right = make_unique<Tree_node>(Tree_node{});
	root->right->left = make_unique<Tree_node>(Tree_node{});
	root->right->right = make_unique<Tree_node>(Tree_node{});

	assert(balanced(root));

	root->left->left->left = make_unique<Tree_node>(Tree_node{});

	assert(!balanced(root));
}

void test_variant1()
{
	{
		unique_ptr<Tree_node>root = make_unique<Tree_node>(Tree_node{ 0 });
		root->left = make_unique<Tree_node>(Tree_node{ 1 });
		assert(1 == variant1(root));
	}
	{
		unique_ptr<Tree_node>root = make_unique<Tree_node>(Tree_node{ 0 });
		root->left = make_unique<Tree_node>(Tree_node{ 1 });
		root->left->left = make_unique<Tree_node>(Tree_node{ 2 });
		root->right = make_unique<Tree_node>(Tree_node{ 3 });
		root->right->left = make_unique<Tree_node>(Tree_node{ 4 });
		cout << variant1(root) << endl;
		assert(1 == variant1(root));
	}
	{
		unique_ptr<Tree_node>root = make_unique<Tree_node>(Tree_node{ 0 });
		root->left = make_unique<Tree_node>(Tree_node{ 1 });
		root->left->right = make_unique<Tree_node>(Tree_node{ 1 });
		root->left->left = make_unique<Tree_node>(Tree_node{ 2 });
		root->right = make_unique<Tree_node>(Tree_node{ 3 });
		root->right->left = make_unique<Tree_node>(Tree_node{ 4 });
		cout << variant1(root) << endl;
		assert(2 == variant1(root));
	}
	{
		unique_ptr<Tree_node>root = make_unique<Tree_node>(Tree_node{ 0 });
		root->left = make_unique<Tree_node>(Tree_node{ 1 });
		root->left->right = make_unique<Tree_node>(Tree_node{ 1 });
		root->left->left = make_unique<Tree_node>(Tree_node{ 2 });
		root->left->left->left = make_unique<Tree_node>(Tree_node{ 2 });
		root->right = make_unique<Tree_node>(Tree_node{ 3 });
		root->right->left = make_unique<Tree_node>(Tree_node{ 4 });
		cout << variant1(root) << endl;
		assert(2 == variant1(root));
	}
	{
		unique_ptr<Tree_node>root = make_unique<Tree_node>(Tree_node{ 1 });
		root->left = make_unique<Tree_node>(Tree_node{ 2 });
		root->left->right = make_unique<Tree_node>(Tree_node{5 });
		root->left->left = make_unique<Tree_node>(Tree_node{ 4 });
		root->left->left->left = make_unique<Tree_node>(Tree_node{8 });
		root->right = make_unique<Tree_node>(Tree_node{ 3 });
		root->right->left = make_unique<Tree_node>(Tree_node{ 6 });
		root->right->right= make_unique<Tree_node>(Tree_node{ 7 });
		cout << variant1(root) << endl;
		assert(3 == variant1(root));
	}
}