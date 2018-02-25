// find the first key greater than a given value in a BST
#include <memory>
#include <iostream>
#include <assert.h>
#include <algorithm>
using namespace std;

struct Tree_node {
	Tree_node(int data_,unique_ptr<Tree_node>left_, unique_ptr<Tree_node> right_)
	{
		data = { data_ };
		left =move(left_ );
		right = move(right_);
	}
	int data;
	unique_ptr<Tree_node>left, right;
};

Tree_node* gre(const unique_ptr<Tree_node>& root,const int& data)
{
	if (!root)return nullptr;
	Tree_node* iter = root.get();
	Tree_node* res = nullptr;
	while (iter)
	{
		if (iter->data > data)
		{
			res = iter;
			iter = iter->left.get();
		}
		else
		{
			iter = iter->right.get();
		}
	}
	return res;
} // time O(h); space O(1)

Tree_node* variant1(const unique_ptr<Tree_node>&root, const int&data)
{
	if (!root)return nullptr;
	Tree_node* iter = root.get();
	Tree_node* best = nullptr;
	while (iter)
	{
		if (iter->data > data)iter = iter->left.get();
		else if (iter->data < data)iter = iter->right.get();
		else if (iter->data == data)
		{
			best = iter;
			iter = iter->left.get();
		}
	}
	return best;
} // time O(h); space O(1)

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

void small_test();
void test_variant1();

void main()
{
	small_test();
	test_variant1();
	system("pause");
}

void small_test()
{
	auto root = gen_tree();
	assert(gre(root, 23)->data == 29);
	assert(gre(root, 53) == nullptr);
	assert(gre(root, 19)->data == 23);
	assert(gre(root, 41)->data == 43);
}

void test_variant1()
{
	auto head = make_unique<Tree_node>(108, nullptr, nullptr);
	head->left = make_unique<Tree_node>(108, nullptr, nullptr);
	head->left->left = make_unique<Tree_node>(-10, nullptr, nullptr);
	head->left->left->left = make_unique<Tree_node>(-14, nullptr, nullptr);
	head->left->left->right = make_unique<Tree_node>(2, nullptr, nullptr);
	head->left->right = make_unique<Tree_node>(108, nullptr, nullptr);

	head->right = make_unique<Tree_node>(285, nullptr, nullptr);
	head->right->left = make_unique<Tree_node>(243, nullptr, nullptr);
	head->right->right = make_unique<Tree_node>(285, nullptr, nullptr);
	head->right->right->right = make_unique<Tree_node>(401, nullptr, nullptr);

	assert(variant1(head, 108) == head->left.get());
	assert(variant1(head, -10) == head->left->left.get());
	assert(variant1(head, 285) == head->right.get());
	assert(variant1(head, 1000) == nullptr);

	head->left->left->data = 108;
	head->left->left->right->data = 108;
	head->left->left->left->data = 108;
	assert(variant1(head, 108) == head->left->left->left.get());
}