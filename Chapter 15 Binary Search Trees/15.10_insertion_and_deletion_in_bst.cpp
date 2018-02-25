// insertion and deletion in a bst
#include <vector>
#include <memory>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <utility>
#include <numeric>
#include <random>
#include <unordered_set>
using namespace std;

struct Tree_node {
	int data;
	unique_ptr<Tree_node>left, right;
};

bool is_bst_helper(const unique_ptr<Tree_node>&node, const pair<int, int> bounds);
bool is_bst(const unique_ptr<Tree_node>&root)
{
	return is_bst_helper(root, { numeric_limits<int>::min(),numeric_limits<int>::max() });
}
bool is_bst_helper(const unique_ptr<Tree_node>&node, const pair<int, int> bounds)
{
	if (!node)return true;
	if (node->data <= bounds.first || node->data >= bounds.second)return false;

	return is_bst_helper(node->left, { bounds.first,node->data }) && is_bst_helper(node->right, { node->data,bounds.second });
}

void insert(unique_ptr<Tree_node>&root, int data)
{
	if (!root)
	{
		root = make_unique<Tree_node>(Tree_node{ data,nullptr,nullptr });
		return;
	}
	Tree_node* prev = nullptr;
	auto iter = root.get();
	while (iter)
	{
		prev = iter;
		if (iter->data == data)return;
		if (iter->data > data)iter = iter->left.get();
		else if (iter->data < data)iter = iter->right.get();
	}
	if (prev->data > data)prev->left = make_unique<Tree_node>(Tree_node{ data,nullptr,nullptr });
	else prev->right = make_unique<Tree_node>(Tree_node{ data,nullptr,nullptr });
} // time worst-case O(n), average-case O(h) h - height; space worst-case O(n), average-case O(h) h - height;

void del(unique_ptr<Tree_node>&root, int data)
{
	if (!root)return;
	Tree_node* parent = nullptr;
	auto node_to_delete = root.get();
	while (node_to_delete && node_to_delete->data != data)
	{
		parent = node_to_delete;
		if (node_to_delete->data > data)node_to_delete = node_to_delete->left.get();
		else if (node_to_delete->data < data)node_to_delete = node_to_delete->right.get();
	}
	if (!node_to_delete)return;

	if (!node_to_delete->left && !node_to_delete->right)
	{
		if (!parent)root.reset();
		else if (parent->left.get() == node_to_delete)parent->left.reset();
		else parent->right.reset();
	}
	else if (node_to_delete->left && !node_to_delete->right)
	{
		if (!parent)root.reset(node_to_delete->left.release());
		else if (parent->left.get() == node_to_delete)parent->left = move(node_to_delete->left);
		else parent->right = move(node_to_delete->left);
	}
	else
	{
		Tree_node* subtree_parent = node_to_delete;
		auto subtree_iter = node_to_delete->right.get();
		while (subtree_iter->left)
		{
			subtree_parent = subtree_iter;
			subtree_iter = subtree_iter->left.get();
		}
		if (subtree_iter->right)
		{
			unique_ptr<Tree_node> subtree_iter_save{};
			if (subtree_parent->right.get() == subtree_iter)
			{
				subtree_iter_save = move(subtree_parent->right);
				subtree_iter_save->left = move(node_to_delete->left);
				if (!parent)
				{
					root.reset(subtree_iter_save.release());
				}
				else if (parent->left.get() == node_to_delete)
				{
					parent->left = move(subtree_iter_save);
				}
				else
				{
					parent->right = move(subtree_iter_save);
				}
			}
			else
			{
				subtree_iter_save = move(subtree_parent->left);
				subtree_parent->left = move(subtree_iter_save->right);
				subtree_iter_save->left = move(node_to_delete->left);
				subtree_iter_save->right = move(node_to_delete->right);
				if (!parent)
				{
					root.reset(subtree_iter_save.release());
				}
				else if (parent->left.get() == node_to_delete)
				{
					parent->left = move(subtree_iter_save);
				}
				else
				{
					parent->right = move(subtree_iter_save);
				}
			}
		}
		else
		{
			unique_ptr<Tree_node> subtree_iter_save{};
			if (node_to_delete->right.get() == subtree_iter)
			{
				subtree_iter->left = move(node_to_delete->left);
				if (!parent)
				{
					root.reset(node_to_delete->right.release());
				}
				else if (parent->left.get() == node_to_delete)
				{
					parent->left = move(node_to_delete->right);
				}
				else parent->right = move(node_to_delete->right);
			}
			else
			{
				subtree_iter->right = move(node_to_delete->right);
				subtree_iter->left = move(node_to_delete->left);
				if (!parent)
				{
					root.reset(subtree_parent->left.release());
				}
				else if (parent->left.get() == node_to_delete)
				{
					parent->left = move(subtree_parent->left);
				}
				else
				{
					parent->right = move(subtree_parent->left);
				}
			}
		}
	}
} // time worst-case O(n), average-case O(h) h - height; space worst-case O(n), average-case O(h) h - height;


void test_insert()
{
	mt19937 mt{ random_device{}() };
	unique_ptr<Tree_node>root{};
	for (int i = 0; i < 1000; ++i)
	{
		insert(root, uniform_int_distribution<int>{numeric_limits<int>::min(), numeric_limits<int>::max()}(mt));
		assert(is_bst(root));
	}
}

void test_delete()
{
	mt19937 mt{ random_device{}() };
	unique_ptr<Tree_node>root{};
	unordered_set<int>numbers{};
	for (int i = 0; i < 100; ++i)
	{
		auto number = uniform_int_distribution<int>{ numeric_limits<int>::min(), numeric_limits<int>::max() }(mt);
		numbers.emplace(number);
		insert(root, number);
	}
	while (!numbers.empty())
	{
		auto num = numbers.begin();
		del(root, *num);
		numbers.erase(num);
		assert(is_bst(root));
	}
}



void main()
{
	test_insert();
	test_delete();
	system("pause");
}