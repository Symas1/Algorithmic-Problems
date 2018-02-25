// compute the kth node in an inorder traversal
#include <memory>
#include <iostream>
#include <functional>
#include <vector>
#include <assert.h>
using namespace std;

struct Tree_node {
	int data;
	unique_ptr<Tree_node>left, right;
};

struct Tree_node_ext {
	int data;
	int size;
	unique_ptr<Tree_node_ext>left, right;
};

pair<bool, Tree_node*>brute_help(const unique_ptr<Tree_node>&node, const int&k, int& counter);
Tree_node* kth_brute(const unique_ptr<Tree_node>&root, const int&k)
{
	int counter = 0;
	return brute_help(root, k, counter).second;
} // time O(n) n - nodes, space O(h) h - height
pair<bool, Tree_node*>brute_help(const unique_ptr<Tree_node>&node, const int&k, int& counter)
{
	if (!node)return{ false,nullptr };
	auto left = brute_help(node->left, k, counter);
	if (left.first)return left;
	++counter;
	if (counter == k)return{ true,node.get() };
	auto right = brute_help(node->right, k, counter);
	if (right.first)return right;
	return{ false,nullptr };
}

Tree_node_ext* kth(const unique_ptr<Tree_node_ext>&root, int k)
{
	auto iter = root.get();
	while (iter)
	{
		int left_size = iter->left ? iter->left->size : 0;
		if (left_size + 1 < k)
		{
			k = k - (left_size + 1);
			iter = iter->right.get();
		}
		else if (left_size  == k-1)return iter;
		else
		{
			iter = iter->left.get();
		}
	}
	return nullptr;
} // time O(h) h - height, space O(1)

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
void test_brute();
void test_kth();

void main()
{
	test_brute();
	test_kth();
	system("pause");
}

void test_brute()
{
	auto root = build_tree();
	vector<int>check{ 28,271,0,6,561,17,3,314,2,401,641,1,257,6,271,28 };
	for (int i = 0; i < check.size(); ++i)
	{
		assert(kth_brute(root, i + 1)->data == check[i]);
	}
}

void test_kth()
{
	unique_ptr<Tree_node_ext>root = make_unique<Tree_node_ext>(Tree_node_ext{ 2,3,nullptr,nullptr });
	root->left = make_unique<Tree_node_ext>(Tree_node_ext{ 1,1,nullptr,nullptr });
	root->right = make_unique<Tree_node_ext>(Tree_node_ext{ 3,1,nullptr,nullptr });

	assert(kth(root, 1)->data == 1);
	assert(kth(root, 2)->data == 2);
	assert(kth(root, 3)->data == 3);
	assert(kth(root, 0)==nullptr);
	assert(kth(root, 4) == nullptr);
}