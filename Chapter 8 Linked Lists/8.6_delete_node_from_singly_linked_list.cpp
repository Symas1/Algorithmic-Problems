// delete a node from a singly linked list
// the input node is guaranteed not to be the tail node
#include <memory>
#include <iostream>
#include <assert.h>
using namespace std;

struct List_node {
	int data;
	shared_ptr<List_node>next;
};

void delete_node(shared_ptr<List_node>node)
{
	node->data = node->next->data;
	node->next = node->next->next;
} // time O(1) space O(1)

void main()
{
	shared_ptr<List_node>list = make_shared<List_node>(List_node{ 1,
	make_shared<List_node>(List_node{2,
	make_shared<List_node>(List_node{3,nullptr})}) });

	delete_node(list->next);
	assert(list->next->data == 3);
	delete_node(list);
	assert(list->data == 3);
	system("pause");
}