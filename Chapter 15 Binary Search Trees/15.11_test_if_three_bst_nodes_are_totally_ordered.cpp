// test if three bst nodes are totally ordered
#include <memory>
#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>
using namespace std;

struct Tree_node {
	Tree_node(int data_, unique_ptr<Tree_node>left_, unique_ptr<Tree_node>right_)
	{
		data = { data_ };
		left = move(left_);
		right = move(right);
	}
	int data;
	unique_ptr<Tree_node>left, right;
};

bool search_target(const unique_ptr<Tree_node>&start, const unique_ptr<Tree_node>&end);
bool ordered(const unique_ptr<Tree_node>&first, const unique_ptr<Tree_node>&second, const unique_ptr<Tree_node>&middle)
{
	auto first_iter = first.get();
	auto second_iter = second.get();
	while ((first_iter || second_iter) && first_iter != middle.get() && second_iter != middle.get() &&
		first_iter != second.get() && second_iter != first.get())
	{
		if (first_iter)
		{
			first_iter = first_iter->data > middle->data ? first_iter->left.get() : first_iter->right.get();
		}
		if (second_iter)
		{
			second_iter = second_iter->data > middle->data ? second_iter->left.get() : second_iter->right.get();
		}
	}
	if ((first_iter != middle.get() && second_iter != middle.get()) || (first_iter == second.get() || second_iter == first.get()))
		return false;

	return search_target(middle, first_iter == middle.get() ? second : first);
}
bool search_target(const unique_ptr<Tree_node>&start, const unique_ptr<Tree_node>&end)
{
	auto iter = start.get();
	while (iter && iter != end.get())
	{
		iter = iter->data > end->data ? iter->left.get() : iter->right.get();
	}
	return iter == end.get();
} // time when false O(h), when true O(d) d - distance between anc and des; space O(1)

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

void main()
{
	
	auto root = gen_tree();
	assert(ordered(root, root->right->left, root->right) == true);
	assert(ordered(root->left, root->right, root) == false);
	assert(ordered(root->right, root->right->right->right, root->right->right) == true);
	assert(ordered(root->right, root->right->left->right->left->right, root->right->left->right) == true);
	system("pause");
}