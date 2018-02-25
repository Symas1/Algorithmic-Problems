// find the k largest elements in a BST
#include <vector>
#include <iostream>
#include <memory>
#include <list>
#include <queue>
#include <stack>
#include <assert.h>
#include <functional>
using namespace std;

struct Tree_node {
	Tree_node(int data_, unique_ptr<Tree_node>left_, unique_ptr<Tree_node> right_)
	{
		data = { data_ };
		left = move(left_);
		right = move(right_);
	}
	int data;
	unique_ptr<Tree_node>left, right;
};

vector<Tree_node*> find_k(const unique_ptr<Tree_node>&root, int k)
{
	stack<Tree_node*> q{};
	q.emplace(root.get());
	vector<Tree_node*>res(k,nullptr);
	size_t ind = 0;
	Tree_node* iter = root->right.get();
	while (ind != k&&(!q.empty() || iter))
	{
		if (iter)
		{
			q.emplace(iter);
			iter = iter->right.get();
		}
		else if (!iter)
		{
			iter = q.top();
			q.pop();
			res[ind++] = iter;
			iter = iter->left.get();
		}
	}
	return{ res.begin(),res.begin() + ind };
} // time O(h+k); space O(h) h - height

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
	for (int i = 1; i < 20; ++i)
	{
		auto res = find_k(root, i);
		assert(is_sorted(res.begin(), res.end(), [](const Tree_node* first, const Tree_node*second) {return first->data >= second->data; }));
	}
	system("pause");
}