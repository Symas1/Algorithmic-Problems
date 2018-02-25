// generate binary trees
#include <memory>
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

struct Tree_node {
	int data;
	unique_ptr<Tree_node>left, right;
};

unique_ptr<Tree_node> copy_tree(const unique_ptr<Tree_node>& root);
vector<unique_ptr<Tree_node>> gen_trees(const int nodes)
{
	vector<unique_ptr<Tree_node>>res{};
	if (!nodes)
	{
		res.emplace_back(nullptr);
		return res;
	}

	
	for (int num_left = 0; num_left < nodes; ++num_left)
	{
		int num_right = nodes - num_left - 1;
		auto left_subtrees = gen_trees(num_left);
		auto right_subtrees = gen_trees(num_right);

		for (const auto& left : left_subtrees)
		{
			for (const auto& right : right_subtrees)
			{
				res.emplace_back(make_unique<Tree_node>(Tree_node{ 0,copy_tree(left),copy_tree(right) }));
			}
		}
	}

	return res;
} // time O((2n)!/(n!(n+1)!)); space O(h) h - max height; Catalan numbers
unique_ptr<Tree_node> copy_tree(const unique_ptr<Tree_node>& root)
{
	return root ? make_unique<Tree_node>(Tree_node{ root->data, copy_tree(root->left), copy_tree(root->right) })
		: nullptr;
}


void small_test()
{
	auto trees = gen_trees(2);
	assert(trees.size() == 2);
	assert(trees[1] && trees[1]->left);
	assert(trees[0] && trees[0]->right);

	trees = gen_trees(3);
	assert(trees[4] && trees[4]->left && trees[4]->left->left);
	assert(trees[3] && trees[3]->left && trees[3]->left->right);
	assert(trees[2] && trees[2]->left && trees[2]->right);
	assert(trees[1] && trees[1]->right && trees[1]->right->left);
	assert(trees[0] && trees[0]->right && trees[0]->right->right);

	assert(gen_trees(1).size() == 1);
	assert(gen_trees(2).size() == 2);
	assert(gen_trees(3).size() == 5);
	assert(gen_trees(4).size() == 14);
	assert(gen_trees(5).size() == 42);
	assert(gen_trees(10).size() == 16796);
}

void main()
{
	small_test();
	system("pause");
}