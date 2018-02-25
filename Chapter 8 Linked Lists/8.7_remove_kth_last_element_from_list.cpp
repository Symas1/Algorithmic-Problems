// remove the kth last element from a list
#include <memory>
#include <iostream>
#include <assert.h>
using namespace std;

struct List_node {
	int data;
	shared_ptr<List_node>next;
};

shared_ptr<List_node> delete_kth_last(const shared_ptr<List_node>&head, int k)
{
	auto dummy_head = make_shared<List_node>(List_node{ 0,head });
	auto first = dummy_head->next;
	auto second = dummy_head;
	while (k--)first = first->next;
	while (first)
	{
		first = first->next;
		second = second->next;
	}
	second->next = second->next->next;
	return dummy_head->next;
} // time O(n) space O(1)

void main()
{
	auto list = make_shared<List_node>(List_node{ 1,
		make_shared<List_node>(List_node{2,
			make_shared<List_node>(List_node{3,nullptr})}) });
	list=delete_kth_last(list, 2);
	assert(list->next->data == 3);
	list=delete_kth_last(list, 1);
	assert(list->data == 1);
	list=delete_kth_last(list, 1);
	assert(!list);
	system("pause");
}