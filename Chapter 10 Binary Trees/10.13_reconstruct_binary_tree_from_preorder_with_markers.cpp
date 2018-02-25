// reconstruct a binary tree from a preorder traversal with markers
#include <memory>
#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

struct Tree_node {
    char data;
	unique_ptr<Tree_node>left, right;
};

unique_ptr<Tree_node> build_helper(const vector<char>&arr, int& index);
unique_ptr<Tree_node> build(const vector<char>& arr)
{
	int index = 0;
	return build_helper(arr, index);
}
unique_ptr<Tree_node> build_helper(const vector<char>&arr, int& index)
{
	if (index >= arr.size())return nullptr;
	if (arr[index] == '\n')return nullptr;

	return make_unique<Tree_node>(Tree_node{
		arr[index],
		build_helper(arr,++index),
		build_helper(arr,++index)
	});
} // time O(n) n - nodes, space O(h) h - height

void pre_helper(const unique_ptr<Tree_node>&node, vector<char>&res);
vector<char> pre(const unique_ptr<Tree_node>&root)
{
	vector<char>res{};
	pre_helper(root,res);
	return res;
} 

void pre_helper(const unique_ptr<Tree_node>&node, vector<char>&res)
{
	if (!node)
	{
		res.emplace_back('\n');
		return;
	}
	else
	{
		res.emplace_back(node->data);
		pre_helper(node->left, res);
		pre_helper(node->right, res);
	}
	
}

void post_helper(const unique_ptr<Tree_node>&node, vector<char>&res);
vector<char> post(const unique_ptr<Tree_node>&root)
{
	vector<char>res{};
	post_helper(root, res);
	return res;
}

void post_helper(const unique_ptr<Tree_node>&node, vector<char>&res)
{
	if (!node)
	{
		res.emplace_back('.');
		return;
	}
	else
	{
		post_helper(node->left, res);
		post_helper(node->right, res);
		res.emplace_back(node->data);
	}

}

unique_ptr<Tree_node> postorder_build_help(const vector<char>&arr, int& index);
unique_ptr<Tree_node> postorder_build(const vector<char>& arr)
{
	int index = arr.size() - 1;
	return postorder_build_help(arr, index);
} // time O(n) n - node, space O(h) h - height
unique_ptr<Tree_node> postorder_build_help(const vector<char>&arr, int& index)
{
	if (index < 0)return nullptr;
	if (arr[index] == '.')return nullptr;

	char data = arr[index];
	auto right = postorder_build_help(arr, --index);
	auto left = postorder_build_help(arr, --index);

	return make_unique<Tree_node>(Tree_node{
		data,
		move(left),
		move(right)
	});
}

void test_build();
void test_post_build();

void main()
{
	test_build();
	test_post_build();

	system("pause");
}

void test_build()
{
	vector<char>arr{ 'H','B','F','\n','\n','E','A','\n','\n','\n','C','\n','D' ,'\n','G','I','\n','\n','\n' };
	auto res = build(arr);
	assert(equal(arr.begin(), arr.end(), pre(res).begin()));
}

void test_post_build()
{
	vector<char>arr{ 'H','B','F','\n','\n','E','A','\n','\n','\n','C','\n','D' ,'\n','G','I','\n','\n','\n' };
	auto root = build(arr);
	auto post_arr = post(root);
	auto root_from_post = postorder_build(post_arr);
	assert(equal(post_arr.begin(), post_arr.end(), post(root_from_post).begin()));
}