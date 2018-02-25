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

void inorder_helper(const unique_ptr<Tree_node>&node,vector<int>&res);
vector<int> inorder(const unique_ptr<Tree_node>&root)
{
	vector<int>res{};
	inorder_helper(root, res);
	return res;
} // time O(n), n - nodes, space O(h) h - max height (min lg(n),max n)

void inorder_helper(const unique_ptr<Tree_node>&node, vector<int>&res)
{
	if (node)
	{
		inorder_helper(node->left, res);
		res.emplace_back(node->data);
		inorder_helper(node->right, res);
	}
}

void preorder_helper(const unique_ptr<Tree_node>&node, vector<int>&res);
vector<int> preorder(const unique_ptr<Tree_node>&root)
{
	vector<int>res{};
	preorder_helper(root, res);
	return res;
} // time O(n), n - nodes, space O(h) h - max height (min lg(n),max n)

void preorder_helper(const unique_ptr<Tree_node>&node, vector<int>&res)
{
	if (node)
	{
		res.emplace_back(node->data);
		preorder_helper(node->left, res);
		preorder_helper(node->right, res);
	}
}

void postorder_helper(const unique_ptr<Tree_node>&node, vector<int>&res);
vector<int> postorder(const unique_ptr<Tree_node>&root)
{
	vector<int>res{};
	postorder_helper(root, res);
	return res;
} // time O(n), n - nodes, space O(h) h - max height (min lg(n),max n)

void postorder_helper(const unique_ptr<Tree_node>&node, vector<int>&res)
{
	if (node)
	{
		postorder_helper(node->left, res);
		postorder_helper(node->right, res);
		res.emplace_back(node->data);
	}
}

unique_ptr<Tree_node> build_tree()
{
	unique_ptr<Tree_node>root = make_unique<Tree_node>(Tree_node{ 314,nullptr,nullptr });
	root->left= make_unique<Tree_node>(Tree_node{ 6,nullptr,nullptr });
	root->left->left = make_unique<Tree_node>(Tree_node{ 271,nullptr,nullptr });
	root->left->left->left = make_unique<Tree_node>(Tree_node{ 28,nullptr,nullptr });
	root->left->left->right = make_unique<Tree_node>(Tree_node{ 0,nullptr,nullptr });
	root->left->right = make_unique<Tree_node>(Tree_node{ 561,nullptr,nullptr });
	root->left->right->right = make_unique<Tree_node>(Tree_node{3,nullptr,nullptr });
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

void main()
{
	// inorder traversal
	{
		vector<int>check{ 28,271,0,6,561,17,3,314,2,401,641,1,257,6,271,28 };
		assert(equal(check.begin(), check.end(), inorder(build_tree()).begin()));
	}

	// preorder traversal
	{
		vector<int>check{ 314,6,271,28,0,561,3,17,6,2,1,401,641,257,271,28 };
		auto r = preorder(build_tree());
		assert(equal(check.begin(), check.end(), preorder(build_tree()).begin()));
	}

	// postorder traversal
	{
		vector<int>check{ 28,0,271,17,3,561,6,641,401,257,1,2,28,271,6,314 };
		auto r = preorder(build_tree());
		assert(equal(check.begin(), check.end(), postorder(build_tree()).begin()));
	}
	system("pause");
}