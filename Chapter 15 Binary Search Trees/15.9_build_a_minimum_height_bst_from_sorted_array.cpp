// build a minimum height BST from a sorted array
#include <vector>
#include <iostream>
#include <assert.h>
#include <memory>
#include <algorithm>
#include <random>
#include<numeric>
using namespace std;

struct Tree_node {
	int data;
	unique_ptr<Tree_node>left, right;
};

unique_ptr<Tree_node> minimum_bst_helper(const vector<int>&arr, int start, int end);
unique_ptr<Tree_node> minimum_bst(const vector<int>&arr)
{
	return minimum_bst_helper(arr, 0, arr.size());
}
unique_ptr<Tree_node> minimum_bst_helper(const vector<int>&arr, int start, int end)
{
	if (start >= end)return nullptr;
	int middle = start+((end - start) / 2);
	return make_unique<Tree_node>(Tree_node{ arr[middle],
		minimum_bst_helper(arr, start, middle),
		minimum_bst_helper(arr, middle + 1, end) });
} // time O(n) n - number of elements; space O(h) h - max height;

int height_h(const unique_ptr<Tree_node>&node,int height);
int height(const unique_ptr<Tree_node>&root)
{
	return height_h(root, 0);
}
int height_h(const unique_ptr<Tree_node>&node,int height)
{
	if (!node)return height-1;

	return max(height_h(node->left, height + 1), height_h(node->right, height + 1));
}

void traversal_check(const unique_ptr<Tree_node>&node, int& target)
{
	if (!node)return;
	traversal_check(node->left, target);
	assert(node->data == target);
	++target;
	traversal_check(node->right, target);
}

void main()
{
	vector<int>arr{ 1,2,3,4,5,6 };
	auto root = minimum_bst(arr);
	assert(height(root) == 2);
	arr = { 1,2,3,4,5 };
	root = minimum_bst(arr);
	assert(height(root) == 2);

	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times)
	{
		vector<int>arr(uniform_int_distribution<>{1, 1000}(mt));
		iota(arr.begin(), arr.end(), 0);
		int target = 0;
		auto root = minimum_bst(arr);
		traversal_check(root, target);
	}
	system("pause");
}