// reconstruct a BST from traversal data
#include <memory>
#include <iostream>
#include <vector>
#include <assert.h>
#include <numeric>
#include <utility>
#include <algorithm>
using namespace std;

struct Tree_node {
	int data;
	unique_ptr<Tree_node>left, right;
};


unique_ptr<Tree_node> reconstruct_preorder_helper(const vector<int>&preorder, size_t& start, size_t end, pair<int, int>limits);
unique_ptr<Tree_node> reconstruct_preorder(const vector<int>& preorder)
{
	size_t start = 0;
	return reconstruct_preorder_helper(preorder, start, preorder.size(), { numeric_limits<int>::min(),numeric_limits<int>::max() });
} // time O(n) n - nodes; space O(1)
unique_ptr<Tree_node> reconstruct_preorder_helper(const vector<int>&preorder, size_t& start, size_t end, pair<int, int>limits)
{
	if (start >= end)return{};
	if (preorder[start]<limits.first || preorder[start]>limits.second)
	{
		--start;
		return{};
	}
	int curr =preorder[start];
	return make_unique<Tree_node>(
		Tree_node{
		curr,
	reconstruct_preorder_helper(preorder,++start,end,{limits.first,curr}),
	reconstruct_preorder_helper(preorder,++start,end,{ curr,limits.second }),
	}
	);
}

void preorder_helper(const unique_ptr<Tree_node>&node,vector<int>&res);
vector<int> preorder(const unique_ptr<Tree_node>&root)
{
	vector<int>res{};
	preorder_helper(root, res);
	return res;
}
void preorder_helper(const unique_ptr<Tree_node>&node, vector<int>&res)
{
	if (!node)return;
	
	res.emplace_back(node->data);
	preorder_helper(node->left, res);
	preorder_helper(node->right, res);
}

unique_ptr<Tree_node> reconstruct_postorder_helper(const vector<int>&postorder,int& start, pair<int, int>limits);
unique_ptr<Tree_node> reconstruct_postorder(const vector<int>& postorder)
{
	int start = postorder.size()-1;
	return reconstruct_postorder_helper(postorder, start, { numeric_limits<int>::min(),numeric_limits<int>::max() });
} // time O(n) n - nodes; space O(1)
unique_ptr<Tree_node> reconstruct_postorder_helper(const vector<int>&postorder, int& start, pair<int, int>limits)
{
	if (start < 0)return{};
	if (postorder[start]<limits.first || postorder[start]>limits.second)
	{
		++start;
		return{};
	}
	int curr = postorder[start];

	auto right = reconstruct_postorder_helper(postorder, --start, { curr,limits.second });
	auto left = reconstruct_postorder_helper(postorder, --start, { limits.first,curr });
	return make_unique<Tree_node>(
		Tree_node{
		curr,
		move(left),
		move(right)
	}
	);
}

void postorder_helper(const unique_ptr<Tree_node>&node, vector<int>&res);
vector<int> postorder(const unique_ptr<Tree_node>&root)
{
	vector<int>res{};
	postorder_helper(root, res);
	return res;
}
void postorder_helper(const unique_ptr<Tree_node>&node, vector<int>&res)
{
	if (!node)return;

	postorder_helper(node->left, res);
	postorder_helper(node->right, res);
	res.emplace_back(node->data);
}

void check_preorder();
void check_postorder();

void main()
{
	check_preorder();
	check_postorder();
	system("pause");
}

void check_preorder()
{
	vector<int>pre{ 110,100,90,105,120,115,130 };
	auto root = reconstruct_preorder(pre);
	auto check = preorder(root);
	assert(equal(pre.begin(), pre.end(), check.begin(), check.end()));
}

void check_postorder()
{
	vector<int>post{ 90,105,100,115,130,120,110 };
	auto root = reconstruct_postorder(post);
	auto check = postorder(root);
	assert(equal(post.begin(), post.end(), check.begin(), check.end()));
}