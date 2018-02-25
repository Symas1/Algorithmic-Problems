// reconstruct a binary tree from traversal data
#include <memory>
#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <numeric>
using namespace std;

struct Tree_node {
	char data;
	unique_ptr<Tree_node>left, right;
};

struct Tree {
	int data;
	unique_ptr<Tree>left, right;
};

unique_ptr<Tree_node> build_tree_help(const vector<char>&preorder,
	size_t pre_beg, size_t pre_end,
	size_t in_beg, size_t in_end,
	unordered_map<char, int>&indexes);

unique_ptr<Tree_node> build_tree(const vector<char>& inorder, const vector<char>& preorder)
{
	unordered_map<char, int>indexes;
	for (int i = 0; i < inorder.size(); ++i)
	{
		indexes.emplace(inorder[i], i);
	}
	return build_tree_help(preorder, 0, preorder.size(), 0, inorder.size(), indexes);
}

unique_ptr<Tree_node> build_tree_help(const vector<char>&preorder,
	size_t pre_beg, size_t pre_end,
	size_t in_beg, size_t in_end,
	unordered_map<char, int>&indexes)
{
	if (pre_beg >= pre_end || in_beg >= in_end)return nullptr;

	size_t root_index = indexes.at(preorder[pre_beg]);
	size_t left_size = root_index - in_beg;

	return make_unique<Tree_node>(Tree_node{preorder[pre_beg],
	build_tree_help(preorder,pre_beg+1,pre_beg+1+left_size,in_beg,root_index+1,indexes),
	build_tree_help(preorder,pre_beg+1+left_size,pre_end,root_index+1,in_end,indexes)}
	);
} // time O(n) n - nodes, space O(n+h)=O(n) 

void in_helper(const unique_ptr<Tree_node>&node, vector<char>&res);
vector<char> in(const unique_ptr<Tree_node>&root)
{
	vector<char> res{};
	in_helper(root, res);
	return res;
}
void in_helper(const unique_ptr<Tree_node>&node, vector<char>&res)
{
	if (node)
	{
		in_helper(node->left, res);
		res.emplace_back(node->data);
		in_helper(node->right, res);
	}
}

void pre_helper(const unique_ptr<Tree_node>&node, vector<char>&res);
vector<char> pre(const unique_ptr<Tree_node>&root)
{
	vector<char> res{};
	pre_helper(root, res);
	return res;
}
void pre_helper(const unique_ptr<Tree_node>&node, vector<char>&res)
{
	if (node)
	{
		res.emplace_back(node->data);
		pre_helper(node->left, res);
		pre_helper(node->right, res);
	}
}

void post_helper(const unique_ptr<Tree_node>&node, vector<char>&res);
vector<char> post(const unique_ptr<Tree_node>&root)
{
	vector<char> res{};
	post_helper(root, res);
	return res;
}
void post_helper(const unique_ptr<Tree_node>&node, vector<char>&res)
{
	if (node)
	{
		post_helper(node->left, res);
		post_helper(node->right, res);
		res.emplace_back(node->data);
	}
}

unique_ptr<Tree_node> variant1_help(const vector<char>& postorder,
	size_t post_beg, size_t post_end,
	size_t in_beg, size_t in_end,
	const unordered_map<char, int>&indexes);
unique_ptr<Tree_node> variant1(const vector<char>& inorder, const vector<char>& postorder)
{
	unordered_map<char, int>indexes{};
	for (int i = 0; i < inorder.size(); ++i)
	{
		indexes.emplace(inorder[i], i);
	}
	return variant1_help(postorder,  0, postorder.size(), 0, inorder.size(), indexes);
} // time O(n) n - nodes, space O(n+h)=O(n) 
unique_ptr<Tree_node> variant1_help(const vector<char>& postorder,
	 size_t post_beg, size_t post_end,
	size_t in_beg, size_t in_end,
	const unordered_map<char, int>&indexes)
{
	if (post_beg >= post_end || in_beg >= in_end )return nullptr;

	size_t root_ind = indexes.at(postorder[post_end-1]);
	size_t dist = in_end - root_ind;

	return make_unique<Tree_node>(
		Tree_node{
		postorder[post_end-1],
		variant1_help(postorder,post_beg,post_end-dist,in_beg,root_ind,indexes),
		variant1_help(postorder,post_end-dist,post_end-1,root_ind+1,in_end,indexes)
	}
	);
} 

unique_ptr<Tree> variant2_helper(const vector<int>&arr, size_t start, size_t end);
unique_ptr<Tree> variant2(const vector<int>&arr)
{
	return variant2_helper(arr, 0, arr.size());
} // time O(n^2) n - nodes, space O(h) h - height
unique_ptr<Tree> variant2_helper(const vector<int>&arr,size_t start,size_t end)
{
	if (start >= end)return nullptr;

	auto max = max_element(arr.begin() + start, arr.begin() + end);
	auto max_index = distance(arr.begin(), max);

	return make_unique<Tree>(Tree{
		arr[max_index],
		variant2_helper(arr,start,max_index),
		variant2_helper(arr,max_index+1,end)
	});
}
void test_build();
void test_variant1();
void main()
{
	test_build();
	test_variant1();
	vector<int> arr{ 1,5,6,4,3 };
	auto r = variant2(arr);
	system("pause");
}

void test_build()
{
	vector<char>inorder{ 'F','B','A','E','H','C','D','I','G' };
	vector<char>preorder{ 'H','B','F','E','A','C','D','G','I' };
	auto res = build_tree(inorder, preorder);
	auto check_in = in(res);
	assert(equal(check_in.begin(), check_in.end(), inorder.begin()));
	auto check_pre = pre(res);
	assert(equal(check_pre.begin(), check_pre.end(), preorder.begin()));
}

void test_variant1()
{
	vector<char>inorder{ 'F','B','A','E','H','C','D','I','G' };
	vector<char>preorder{ 'H','B','F','E','A','C','D','G','I' };
	vector<char>postorder{ 'F','A','E','B','I','G','D','C','H' };
	auto res = variant1(inorder, postorder);
	assert(equal(postorder.begin(), postorder.end(), post(res).begin()));
}