// implement a preorder traversal without recursion
#include <memory>
#include <stack>
#include <vector>
#include <iostream>
#include <assert.h>
using namespace std;

struct Tree_node {
	int data;
	unique_ptr<Tree_node>left, right;
};

vector<int> preorder(const unique_ptr<Tree_node>&root)
{
	vector<int>res{};
	stack<Tree_node*>stack{};
	auto iter = root.get();
	while (!stack.empty() || iter)
	{
		if (iter)
		{
			res.emplace_back(iter->data);
			if(iter->right)stack.emplace(iter->right.get());
			iter = iter->left.get();
		}
		else
		{
			iter = stack.top();
			stack.pop();
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
	// preorder traversal
	{
		vector<int>check{ 314,6,271,28,0,561,3,17,6,2,1,401,641,257,271,28 };
		assert(equal(check.begin(), check.end(), preorder(build_tree()).begin()));
	}
	system("pause");
}