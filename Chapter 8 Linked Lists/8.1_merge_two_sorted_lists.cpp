// merge two sorted lists
#include <memory>
#include <iostream>
using namespace std;

struct List_node {
	int data;
	shared_ptr<List_node>next;
};

void append_node(shared_ptr<List_node>&node,shared_ptr<List_node>&tail)
{
	tail->next = node;
	tail = tail->next;
	node = node->next;
}

shared_ptr<List_node> merge_lists(shared_ptr<List_node>first,shared_ptr<List_node>second)
{
	shared_ptr<List_node>fake_head = make_shared<List_node>(List_node{});
	auto tail = fake_head;
	while (first&&second)
	{
		append_node(first->data <= second->data ? first : second, tail);
	}
	tail->next = first ? first : second;
	return fake_head->next;
} // time O(n+m) space O(1)

void print_list(shared_ptr<List_node>L)
{
	while (L)
	{
		cout << L->data << " ";
		L = L->next;
	}
	cout << endl;
}

struct Double_list_node
{
	int data;
	shared_ptr<Double_list_node>next;
	shared_ptr<Double_list_node>prev;
};
void print_double(shared_ptr<Double_list_node>L)
{
	while (L)
	{
		cout << L->data << " ";
		if(L->next)L=L->next;
		else break;
	}
	cout << endl;
	while (L)
	{
		cout << L->data << " ";
		L=L->prev;
	}
	cout << endl;
}
void insert_after_double(const shared_ptr<Double_list_node>&node, const shared_ptr<Double_list_node>&new_node)
{
	new_node->next = node->next;
	if(node->next)node->next->prev = new_node;
	node->next = new_node;
	new_node->prev = node;
}
void append_double(shared_ptr<Double_list_node>&node, shared_ptr<Double_list_node>&tail)
{
	tail->next = node;
	node->prev = tail;
	tail = tail->next;
	node = node->next;
}

shared_ptr<Double_list_node> merge_double_lists(shared_ptr<Double_list_node>l1, shared_ptr<Double_list_node>l2)
{
	shared_ptr<Double_list_node>fake_head = make_shared<Double_list_node>(Double_list_node{});
	auto tail = fake_head;
	while (l1&&l2)
	{
		append_double(l1->data <= l2->data ? l1 : l2, tail);
	}
	tail->next = l1 ? l1 : l2;
	if (l1)l1->prev = tail;
	else if (l2)l2->prev = tail;

	fake_head->next->prev = nullptr;
	return fake_head->next;
} // time O(n+m) space O(1)

void list_test();
void double_list_test();
void main()
{
	list_test();
	cout << endl;
	double_list_test();
	system("pause");
}

void list_test()
{
	shared_ptr<List_node>first = make_shared<List_node>(List_node{
		1,make_shared<List_node>(List_node{
		3,make_shared<List_node>(List_node{
		5,nullptr }) }) });
	shared_ptr<List_node>second = make_shared<List_node>(List_node{
		2,make_shared<List_node>(List_node{
		4,nullptr }) });
	print_list(first);
	print_list(second);
	auto merge = merge_lists(first, second);
	print_list(merge);
	print_list(first);
	print_list(second);
}

void double_list_test()
{
	shared_ptr<Double_list_node>first = make_shared<Double_list_node>(Double_list_node{ 1,nullptr,nullptr });
	insert_after_double(first, make_shared<Double_list_node>(Double_list_node{ 3,nullptr,nullptr }));
	insert_after_double(first->next, make_shared<Double_list_node>(Double_list_node{ 5,nullptr,nullptr }));
	print_double(first);
	shared_ptr<Double_list_node>second = make_shared<Double_list_node>(Double_list_node{ 2,nullptr,nullptr });
	insert_after_double(second, make_shared<Double_list_node>(Double_list_node{ 4,nullptr,nullptr }));
	print_double(second);

	auto m = merge_double_lists(first, second);
	print_double(m);
	print_double(first);
	print_double(second);
}