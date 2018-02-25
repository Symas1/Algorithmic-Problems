// remove duplicates from a sorted list
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

struct List_node {
	int data;
	shared_ptr<List_node>next;
};

void delete_duplicates(shared_ptr<List_node>head)
{
	auto last_valid = head;
	head = head->next;
	while (head)
	{
		while (head && head->data == last_valid->data)
			head = head->next;
		last_valid->next = head;
		last_valid = head;
	}
} // time O(n) space O(1)

void delete_variant1(const shared_ptr<List_node>&head, int k)
{
	auto last_valid = head;
	auto iter = head->next;
	while (iter)
	{
		for (int c = 0; iter&&iter->data == last_valid->data; ++c)
		{
			if (c < k-1 && last_valid->next)last_valid = last_valid->next;
			iter = iter->next;
		}
		last_valid->next = iter;
		last_valid = iter;
	}
} // time O(n) space O(1)

void test_vairant();
shared_ptr<List_node> create_list(const vector<int>&arr)
{
	auto head = make_shared<List_node>(List_node{});
	auto tail = head;
	for (int i = 0; i < arr.size(); ++i)
	{
		tail->next = make_shared<List_node>(List_node{ arr[i],nullptr });
		tail = tail->next;
	}
	return head->next;
}
void main()
{
	test_vairant();
	auto head = create_list({ 1,1,1,1,2,3,4,4,5,5,6,7,7,7,8,8 });
	delete_duplicates(head);
	auto iter = head;
	vector<int>ans{};
	while (iter)
	{
		ans.emplace_back(iter->data);
		iter = iter->next;
	}
	assert(distance(ans.begin(), ans.end()) == distance(ans.begin(), unique(ans.begin(), ans.end())));
	system("pause");
}

void test_vairant()
{
	auto head = create_list({ 1,1,1,2,2,2,3,3,3,4,4,5,5,6,7,8,9 });
	delete_variant1(head,2);
	while (head)
	{
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
}