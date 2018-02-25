// compute binary tree nodes in order of increasing order
#include <memory>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <assert.h>
#include <iterator>
using namespace std;

struct Node {
	int data;
	shared_ptr<Node>left;
	shared_ptr<Node>right;
};

shared_ptr<Node> build_tree(int depth)
{
	queue<shared_ptr<Node>>next_node{};
	shared_ptr<Node>root = make_shared<Node>(Node{ 0 });
	next_node.emplace(root);
	int counter = 1;
	for (int elements = 1, current_d = 0; current_d < depth; ++elements)
	{
		if (elements == pow(2, current_d))
		{
			++current_d;
			elements = 0;
		}
		shared_ptr<Node> current_node = next_node.front();
		next_node.pop();

		current_node->left = make_shared<Node>(Node{ counter++ });
		current_node->right = make_shared<Node>(Node{ counter++ });

		next_node.emplace(current_node->left);
		next_node.emplace(current_node->right);
	}
	return root;
}

vector<vector<int>> print(const shared_ptr<Node>&root)
{
	if (!root)return{}; // root nullptr

	vector<vector<int>>res{ {root->data} }; // root element is first
	queue<shared_ptr<Node>>next_node{{root}};

	int elements = 1; // elements on current depth
	while (!next_node.empty())
	{
		res.emplace_back(vector<int>{});
		int next = 0;
		for (int i = 0; i < elements; ++i)
		{
			auto current = next_node.front();
			next_node.pop();
			if (current->left)
			{
				next_node.emplace(current->left);
				++next;
				res.back().emplace_back(current->left->data);
			}
			if (current->right)
			{
				next_node.emplace(current->right);
				++next;
				res.back().emplace_back(current->right->data);
			}
		}
		elements = next;
	}
	return res;
} // time	O(-(1-2^(depth+1))) space O(-(1-2^(depth+1))) 
  // time O(n) n - numbers of nodes; space O(m + n)~O(n) m - max number of nodes at any depth

void pri(const vector<vector<int>>& arr)
{
	for (auto iter = arr.begin(); iter < arr.end(); ++iter)
	{
		copy(iter->begin(), iter->end(), ostream_iterator<int>{cout, " "});
		cout << '\n';
	}
	cout << endl;
}

vector<vector<int>> variant1(const shared_ptr<Node>&root)
{
	if (!root)return{};
	vector<vector<int>>res{ };
	deque<shared_ptr<Node>>current_level{ {root} };
	bool turn = false;
	while (!current_level.empty())
	{
		vector<int>current_l{};
		deque<shared_ptr<Node>>next_level{};
		while (!current_level.empty())
		{
				auto curr = current_level.front();
				current_level.pop_front();
				if (curr)
				{
					current_l.emplace_back(curr->data);
					next_level.emplace_back(curr->left);
					next_level.emplace_back(curr->right);
				}
		}
		current_level = next_level;
		if (turn)reverse(current_l.begin(), current_l.end());
		if (!current_l.empty())res.emplace_back(current_l);
		turn = turn ? false : true;
	}
	return res;
} // time O(n) n - numbers of nodes; space O(m + n)~O(n) m - max number of nodes at any depth

vector<vector<int>> variant2(const shared_ptr<Node>&root)
{
	if (!root)return{};
	vector<vector<int>>res{};
	queue<shared_ptr<Node>>current_nodes{ {root} };
	while (!current_nodes.empty())
	{
		queue<shared_ptr<Node>>next_nodes{};
		vector<int>new_row{};
		while (!current_nodes.empty())
		{
			auto current = current_nodes.front();
			current_nodes.pop();
			if (current)
			{
				new_row.emplace_back(current->data);

				next_nodes.emplace(current->left);
				next_nodes.emplace(current->right);
			}
		}
		current_nodes = next_nodes;
		if (!new_row.empty())res.emplace_back(new_row);
	}
	reverse(res.begin(), res.end());
	return res;
} // time O(n) n - numbers of nodes; space O(m + n)~O(n) m - max number of nodes at any depth

vector<double> variant3(const shared_ptr<Node>&root)
{
	if (!root)return{};
	vector<double>res{};
	queue<shared_ptr<Node>>current_nodes{ {root} };
	while (!current_nodes.empty())
	{
		queue<shared_ptr<Node>>next_nodes{};
		double average = 0;
		int elements_on_level = 0;
		while (!current_nodes.empty())
		{
			auto current = current_nodes.front();
			current_nodes.pop();
			if (current)
			{
				average += current->data;
				++elements_on_level;

				next_nodes.emplace(current->left);
				next_nodes.emplace(current->right);
			}
		}
		current_nodes = next_nodes;
		if (elements_on_level)
		{
			average /= elements_on_level;
			res.emplace_back(average);
		}
	}
	return res;
} // time O(n) n - numbers of nodes; space O(m) m - max number of nodes at any depth

void test_main();
void test_variant1();
void test_variant2();
void test_variant3();

void main()
{
	test_main();
	test_variant1();
	test_variant2();
	test_variant3();
	system("pause");
}

void test_main()
{
	auto root = build_tree(4);
	auto arr = print(root);
	pri(arr);
}

void test_variant1()
{
	auto root = build_tree(3);
	auto arr = variant1(root);
	pri(arr);
}

void test_variant2()
{
	auto root = build_tree(2);
	auto arr = variant2(root);
	pri(arr);
}

void test_variant3()
{
	auto root = build_tree(2);
	auto arr = variant3(root);
	assert(arr[0] == 0 && arr[1] == 1.5 && arr[2] == 4.5);
}