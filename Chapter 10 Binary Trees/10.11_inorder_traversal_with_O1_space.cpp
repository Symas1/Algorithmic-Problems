// implement an inorder traversal with O(1) space
#include <memory>
#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

struct Tree_node {
	int data;
	shared_ptr<Tree_node>left, right;
};

struct Tree_node_ext {
	int data;
	shared_ptr<Tree_node_ext>left, right;
	Tree_node_ext* parent;
};

vector<int> morris(const shared_ptr<Tree_node>&root)
{
	vector<int>res{};
	auto iter = root;
	while (iter)
	{
		if (!iter->left)
		{
			res.emplace_back(iter->data);
			iter = iter->right;
		}
		else
		{
			auto r = iter->left;
			while (r->right && r->right != iter)
			{
				r = r->right;
			}
			if (r->right == iter)
			{
				r->right = nullptr;
				res.emplace_back(iter->data);
				iter = iter->right;
			}
			else
			{
				r->right = iter;
				iter = iter->left;
			}
		}
	}
	return res;
} // time O(n) n - nodes, space O(h) h - height

vector<int> inorder(const shared_ptr<Tree_node_ext>&root)
{
	vector<int>res{};
	Tree_node_ext* prev = nullptr;
	Tree_node_ext* curr = root.get();
	while (curr)
	{
		Tree_node_ext* next = nullptr;
		if (curr->parent == prev)
		{
			if (curr->left)next = curr->left.get();
			else
			{
				res.emplace_back(curr->data);
				next = curr->right ? curr->right.get() : curr->parent;
			}
		}
		else if (curr->left.get() == prev)
		{
			res.emplace_back(curr->data);
			next = curr->right ? curr->right.get() : curr->parent;
		}
		else
		{
			next = curr->parent;
		}
		prev = curr;
		curr = next;
	}
	return res;
} // time O(n) n - nodes; space O(1)

vector<int> variant_preorder(const shared_ptr<Tree_node_ext>&root)
{
	vector<int>res{};
	Tree_node_ext* curr = root.get();
	Tree_node_ext* prev = nullptr;
	while (curr)
	{
		Tree_node_ext* next = nullptr;
		if (curr->left.get() == prev)
		{
			next = curr->right ? curr->right.get() : curr->parent;
		}
		else if (curr->parent == prev)
		{
			res.emplace_back(curr->data);
			next = curr->left ? curr->left.get() : curr->right ? curr->right.get() : curr->parent;
		}
		else
		{
			next = curr->parent;
		}
		prev = curr;
		curr = next;
	}
	return res;
} // time O(n) n - nodes; space O(1)

vector<int> variant_postorder(const shared_ptr<Tree_node_ext>&root)
{
	vector<int>res{};
	Tree_node_ext* curr = root.get();
	Tree_node_ext* prev = nullptr;
	while (curr)
	{
		Tree_node_ext* next = nullptr;
		if (curr->parent == prev)
		{
			if (curr->left)
			{
				next = curr->left.get();
			}
			else
			{
				if (curr->right)next = curr->right.get();
				else
				{
					res.emplace_back(curr->data);
					next = curr->parent;
				}
			}
		}
		else if (curr->left.get() == prev)
		{
			if (curr->right)
			{
				next = curr->right.get();
			}
			else
			{
				res.emplace_back(curr->data);
				next = curr->parent;
			}
		}
		else if (curr->right.get() == prev)
		{
			res.emplace_back(curr->data);
			next = curr->parent;
		}
		prev = curr;
		curr = next;
	}
	return res;
} // time O(n) n - nodes; space O(1)

shared_ptr<Tree_node> build_tree()
{
	shared_ptr<Tree_node>root = make_shared<Tree_node>(Tree_node{ 314,nullptr,nullptr });
	root->left = make_shared<Tree_node>(Tree_node{ 6,nullptr,nullptr });
	root->left->left = make_shared<Tree_node>(Tree_node{ 271,nullptr,nullptr });
	root->left->left->left = make_shared<Tree_node>(Tree_node{ 28,nullptr,nullptr });
	root->left->left->right = make_shared<Tree_node>(Tree_node{ 0,nullptr,nullptr });
	root->left->right = make_shared<Tree_node>(Tree_node{ 561,nullptr,nullptr });
	root->left->right->right = make_shared<Tree_node>(Tree_node{ 3,nullptr,nullptr });
	root->left->right->right->left = make_shared<Tree_node>(Tree_node{ 17,nullptr,nullptr });
	root->right = make_shared<Tree_node>(Tree_node{ 6,nullptr,nullptr });
	root->right->left = make_shared<Tree_node>(Tree_node{ 2,nullptr,nullptr });
	root->right->left->right = make_shared<Tree_node>(Tree_node{ 1,nullptr,nullptr });
	root->right->left->right->left = make_shared<Tree_node>(Tree_node{ 401,nullptr,nullptr });
	root->right->left->right->left->right = make_shared<Tree_node>(Tree_node{ 641,nullptr,nullptr });
	root->right->left->right->right = make_shared<Tree_node>(Tree_node{ 257,nullptr,nullptr });
	root->right->right = make_shared<Tree_node>(Tree_node{ 271,nullptr,nullptr });
	root->right->right->right = make_shared<Tree_node>(Tree_node{ 28,nullptr,nullptr });
	return root;
}

shared_ptr<Tree_node_ext> build_tree_ext()
{
	shared_ptr<Tree_node_ext>root = make_shared<Tree_node_ext>(Tree_node_ext{ 314,nullptr,nullptr,nullptr });
	root->left = make_shared<Tree_node_ext>(Tree_node_ext{ 6,nullptr,nullptr,root.get() });
	root->left->left = make_shared<Tree_node_ext>(Tree_node_ext{ 271,nullptr,nullptr,root->left.get() });
	root->left->left->left = make_shared<Tree_node_ext>(Tree_node_ext{ 28,nullptr,nullptr,root->left->left.get() });
	root->left->left->right = make_shared<Tree_node_ext>(Tree_node_ext{ 0,nullptr,nullptr,root->left->left.get() });
	root->left->right = make_shared<Tree_node_ext>(Tree_node_ext{ 561,nullptr,nullptr,root->left.get() });
	root->left->right->right = make_shared<Tree_node_ext>(Tree_node_ext{ 3,nullptr,nullptr,root->left->right.get() });
	root->left->right->right->left = make_shared<Tree_node_ext>(Tree_node_ext{ 17,nullptr,nullptr,root->left->right->right.get() });
	root->right = make_shared<Tree_node_ext>(Tree_node_ext{ 6,nullptr,nullptr,root.get() });
	root->right->left = make_shared<Tree_node_ext>(Tree_node_ext{ 2,nullptr,nullptr,root->right.get() });
	root->right->left->right = make_shared<Tree_node_ext>(Tree_node_ext{ 1,nullptr,nullptr,root->right->left.get() });
	root->right->left->right->left = make_shared<Tree_node_ext>(Tree_node_ext{ 401,nullptr,nullptr,root->right->left->right.get() });
	root->right->left->right->left->right = make_shared<Tree_node_ext>(Tree_node_ext{ 641,nullptr,nullptr,root->right->left->right->left.get() });
	root->right->left->right->right = make_shared<Tree_node_ext>(Tree_node_ext{ 257,nullptr,nullptr,root->right->left->right.get() });
	root->right->right = make_shared<Tree_node_ext>(Tree_node_ext{ 271,nullptr,nullptr,root->right.get() });
	root->right->right->right = make_shared<Tree_node_ext>(Tree_node_ext{ 28,nullptr,nullptr,root->right->right.get() });
	return root;
}

void main()
{
	// inorder
	{
		vector<int>check{ 28,271,0,6,561,17,3,314,2,401,641,1,257,6,271,28 };
		assert(equal(check.begin(), check.end(), morris(build_tree()).begin()));
		assert(equal(check.begin(), check.end(), morris(build_tree()).begin()));
		assert(equal(check.begin(), check.end(), inorder(build_tree_ext()).begin()));
	}

	// preorder traversal
	{
		vector<int>check{ 314,6,271,28,0,561,3,17,6,2,1,401,641,257,271,28 };
		assert(equal(check.begin(), check.end(), variant_preorder(build_tree_ext()).begin()));
	}

	// postorder traversal
	{
		vector<int>check{ 28,0,271,17,3,561,6,641,401,257,1,2,28,271,6,314 };
		assert(equal(check.begin(), check.end(), variant_postorder(build_tree_ext()).begin()));
	}
	system("pause");
}