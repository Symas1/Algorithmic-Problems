// implement cyclic right shift for singly linked list
#include <memory>
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

struct List_node {
	int data;
	shared_ptr<List_node>next;
};

shared_ptr<List_node> cyclic(const shared_ptr<List_node>&head, int k)
{
	auto fake_head= make_shared<List_node>(List_node{ 0,head });
	shared_ptr<List_node>second = fake_head;
	shared_ptr<List_node>first = fake_head->next;
	shared_ptr<List_node>tail;
	while (k--)first = first->next;
	while (first)
	{
		if (first->next == nullptr)tail = first;
		second = second->next, first = first->next;
	}
	tail->next = fake_head->next;
	fake_head->next = second->next;
	second->next = nullptr;
	return fake_head->next;
} // time O(n) space O(1)

shared_ptr<List_node> create_list(const vector<int>&arr)
{
	shared_ptr<List_node>fake_head = make_shared <List_node>(List_node{});
	auto tail = fake_head;
	for (int i = 0; i < arr.size(); ++i)
	{
		tail->next= make_shared <List_node>(List_node{arr[i],nullptr});
		tail = tail->next;
	}
	return fake_head->next;
}

void equal(shared_ptr<List_node>head,const vector<int>&arr)
{
	for (int i = 0; i < arr.size(); ++i)
	{
		assert(head->data == arr[i]);
		head = head->next;
	}
	assert(!head);
}

void main()
{
	{
		auto list = create_list({ 2,3,5,3,2 });
		list = cyclic(list, 3);
		equal(list, { 5,3,2,2,3 });
	}
	{
		auto list = create_list({ 2,3,5,3,2 });
		list = cyclic(list, 1);
		equal(list, { 2,2,3,5,3 });
	}
	{
		auto list = create_list({ 2,3,5,3,2 });
		list = cyclic(list, 2);
		equal(list, { 3,2,2,3,5 });
	}
	system("pause");
}