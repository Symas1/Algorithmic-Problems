// implement inorder traversal without recursion
#include <memory>
#include <stack>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <assert.h>
using namespace std;

struct Tree_node {
	int data;
	unique_ptr<Tree_node>left, right;
};

vector<int> inorder(const unique_ptr<Tree_node>&root)
{
	vector<int>res{};
	stack<Tree_node*>stack{};
	auto iter = root.get();
	while (!stack.empty() || iter)
	{
		if (iter)
		{
			stack.emplace(iter);
			iter = iter->left.get();
		}
		else
		{
			iter = stack.top();
			stack.pop();
			res.emplace_back(iter->data);
			iter = iter->right.get();
		}
	}
	return res;
} // time O(n) n - nodes, space O(h) h - height

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

void main()
{
	vector<int>check{ 28,271,0,6,561,17,3,314,2,401,641,1,257,6,271,28 };
	assert(equal(check.begin(), check.end(), inorder(build_tree()).begin()));
	system("pause");
}