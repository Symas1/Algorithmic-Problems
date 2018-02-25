// implement list pivoting
#include <memory>
#include <iostream>
#include <array>
#include <vector>
using namespace std;

struct List_node {
	int data;
	shared_ptr<List_node>next;
};

shared_ptr<List_node> pivoting(const shared_ptr<List_node>& head, int k)
{
	shared_ptr<List_node>less_head = make_shared<List_node>(List_node{});
	shared_ptr<List_node>equal_head = make_shared<List_node>(List_node{});
	shared_ptr<List_node>bigger_head = make_shared<List_node>(List_node{});
	array<shared_ptr<List_node>, 3>tails{ less_head,equal_head,bigger_head };

	for (auto iter = head; iter; iter = iter->next)
	{
		if (iter->data < k)
		{
			tails[0]->next = iter;
			tails[0] = tails[0]->next;
		}
		else if (iter->data == k)
		{
			tails[1]->next = iter;
			tails[1] = tails[1]->next;
		}
		else if (iter->data > k)
		{
			tails[2]->next = iter;
			tails[2] = tails[2]->next;
		}
	}
	tails[0]->next = equal_head->next;
	tails[1]->next = bigger_head->next;
	tails[2]->next = nullptr;
	return less_head->next;
} // time O(n) space O(1)

shared_ptr<List_node> create_list(const vector<int>&arr)
{
	shared_ptr<List_node>head{};
	for (int i = arr.size() - 1; i >= 0; --i)
	{
		auto node = make_shared<List_node>(List_node{ arr[i],nullptr });
		node->next = head;
		head = node;
	}
	return head;
}

void print(shared_ptr<List_node>head)
{
	while (head)
	{
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
}

void main()
{
	auto list = create_list({ 3,2,2,11,7,7,5,11 });
	print(list);
	list = pivoting(list,7);
	print(list);
	system("pause");
}