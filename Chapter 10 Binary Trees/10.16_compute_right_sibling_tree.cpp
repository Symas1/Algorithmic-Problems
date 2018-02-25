// compute the right sibling tree
#include <memory>
#include <iostream>
#include <assert.h>
#include <queue>
#include <string>
using namespace std;

struct Tree_node {
	int data;
	unique_ptr<Tree_node>left, right;
	Tree_node* right_sibling;
};

unique_ptr<Tree_node> build_perfect(const int height)
{
	int counter = 0;
	auto root = make_unique<Tree_node>(Tree_node{ counter++,nullptr,nullptr,nullptr });
	queue<Tree_node*>current{ {root.get()} };
	for (int i = 0; i < height; ++i)
	{
		queue<Tree_node*>next{};
		while (!current.empty())
		{
			auto node = current.front();
			current.pop();
			node->left = make_unique<Tree_node>(Tree_node{ counter++,nullptr,nullptr,nullptr });
			node->right = make_unique<Tree_node>(Tree_node{ counter++,nullptr,nullptr,nullptr });
			next.emplace(node->left.get());
			next.emplace(node->right.get());
		}
		current = next;
	}
	return root;
}

void sibling_help(Tree_node* node);
void sibling(const unique_ptr<Tree_node>&root)
{
	auto iter = root.get();
	while (iter && iter->left)
	{
		sibling_help(iter);
		iter = iter->left.get();
	}
} // time O(n) n - nodes; space O(1)
void sibling_help(Tree_node* node)
{
	auto iter = node;
	while (iter)
	{
		iter->left->right_sibling = iter->right.get();
		if (iter->right_sibling)
		{
			iter->right->right_sibling = iter->right_sibling->left.get();
		}
		iter = iter->right_sibling;
	}
}

void show(const unique_ptr<Tree_node>&node)
{
	if (!node)return;
	cout << node->data << '\t';
	if (node->right_sibling) cout << node->right_sibling->data << endl;
	else cout << "nullptr" << endl;
	show(node->left);
	show(node->right);
}

void variant_sibling_helper(Tree_node* node);
void variant_sibling(const unique_ptr<Tree_node>&root)
{
	auto iter = root.get();
	while (iter)
	{
		variant_sibling_helper(iter);
		if (iter->left)iter = iter->left.get();
		else if (iter->right)iter = iter->right.get();
		else if (iter->right_sibling)
		{
			if (iter->right_sibling->left)iter = iter->right_sibling->left.get();
			else if (iter->right_sibling->right)iter = iter->right_sibling->right.get();
			else iter = nullptr;
		}
		else iter = nullptr;
	}
} // time O(n) n - nodes, space O(1)
void variant_sibling_helper(Tree_node* node)
{
	auto iter = node;
	while (iter)
	{
		if (iter->left)
		{
			Tree_node* for_left = nullptr;
			if (iter->right)for_left = iter->right.get();
			else if (iter->right_sibling)
			{
				if (iter->right_sibling->left)for_left = iter->right_sibling->left.get();
				else if (iter->right_sibling->right)for_left = iter->right_sibling->right.get();
			}
			iter->left->right_sibling = for_left;
		}
		if (iter->right)
		{
			Tree_node* for_right = nullptr;
			if (iter->right_sibling)
			{
				if (iter->right_sibling->left)for_right = iter->right_sibling->left.get();
				else if (iter->right_sibling->right)for_right = iter->right_sibling->right.get();
			}
			iter->right->right_sibling = for_right;
		}
		iter = iter->right_sibling;
	}
}

void test_sibling();
void test_variant_sibling();
void main()
{
	test_sibling();
	test_variant_sibling();
	system("pause");
}

void test_sibling()
{
	auto root = build_perfect(2);
	sibling(root);
	assert(root->right_sibling == nullptr);
	assert(root->left->right_sibling == root->right.get());
	assert(root->left->left->right_sibling == root->left->right.get());
	assert(root->left->right->right_sibling == root->right->left.get());
	assert(root->right->right_sibling == nullptr);
	assert(root->right->left->right_sibling == root->right->right.get());
	assert(root->right->right->right_sibling == nullptr);
}

void test_variant_sibling()
{
	auto root = make_unique<Tree_node>(Tree_node{ 0 });
	root->left = make_unique<Tree_node>(Tree_node{ 1 });
	root->left->left = make_unique<Tree_node>(Tree_node{ 3 });

	root->right = make_unique<Tree_node>(Tree_node{ 2 });
	root->right->left = make_unique<Tree_node>(Tree_node{ 4 });
	root->right->left->left = make_unique<Tree_node>(Tree_node{ 6 });
	root->right->right = make_unique<Tree_node>(Tree_node{ 5 });
	root->right->right->left = make_unique<Tree_node>(Tree_node{ 7 });
	root->right->right->right = make_unique<Tree_node>(Tree_node{ 8 });

	variant_sibling(root);
	assert(root->right_sibling == nullptr);
	assert(root->left->right_sibling == root->right.get());
	assert(root->left->left->right_sibling == root->right->left.get());
	assert(root->right->right_sibling == nullptr);
	assert(root->right->left->right_sibling == root->right->right.get());
	assert(root->right->left->left->right_sibling == root->right->right->left.get());
	assert(root->right->right->right_sibling == nullptr);
	assert(root->right->right->left->right_sibling == root->right->right->right.get());
	assert(root->right->right->right->right_sibling == nullptr);
}