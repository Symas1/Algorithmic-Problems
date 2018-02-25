// reverse single sublist
#include <memory>
#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;

struct List_node {
	int data;
	shared_ptr<List_node>next;
};

void insert_after(const shared_ptr<List_node>&node, const shared_ptr<List_node>&new_node)
{
	new_node->next = node->next;
	node->next = new_node;
}
void print(shared_ptr<List_node>L)
{
	while (L)
	{
		cout << L->data << " ";
		L = L->next;
	}
	cout << endl;
}

shared_ptr<List_node> reverse_list2(shared_ptr<List_node>L, int start, int end)
{
	auto dummy_head = make_shared<List_node>(List_node{ 0,L });
	shared_ptr<List_node>substr_head = dummy_head;
	for (int i = 1; i < start; ++i)
	{
		substr_head = substr_head->next;
	}

	auto substr_iter = substr_head->next;
	while (start++ < end)
	{
		auto temp = substr_iter->next;
		substr_iter->next = temp->next;
		temp->next = substr_head->next;
		substr_head->next = temp;
	}
	return dummy_head->next;
} // time O(end) space O(1)

shared_ptr<List_node> reverse_full_list(shared_ptr<List_node>L)
{
	if (L == nullptr || L->next == nullptr)return L ? L : nullptr;

	auto swap_iter = L;
	while (swap_iter->next)
	{
		auto temp = swap_iter->next;
		swap_iter->next = temp->next;
		temp->next = L;
		L = temp;
	}
	return L;
} // time O(n) space O(1)

shared_ptr<List_node> reverse_k(shared_ptr<List_node>head, unsigned k)
{
	auto check = head;
	auto sublist_head = head;
	shared_ptr<List_node> prev_sublist{};
	bool first_time = true;
	while (true)
	{
		for (size_t i = 0; i < k; ++i)
		{
			if (!check)return head;
			check = check->next;
		}

		auto sublist_iter = sublist_head;
		for (size_t i = 0; i < k-1; ++i)
		{
			auto temp = sublist_iter->next;
			sublist_iter->next = temp->next;
			temp->next = sublist_head;
			sublist_head = temp;
			if (prev_sublist)prev_sublist->next = sublist_head;
		}
		if (first_time)
		{
			head = sublist_head;
			first_time = false;
		}
		prev_sublist = sublist_iter;
		sublist_head = sublist_iter->next;
	}
} // time O(n) space O(1)

void test_reverse();
void test_full_reverse();
void test_reverse_k();

void main()
{
	test_reverse();
	test_full_reverse();
	test_reverse_k();
	system("pause");
}

void test_reverse()
{
	shared_ptr<List_node>list;
	{
		list = make_shared<List_node>(List_node{ 1,nullptr });
		insert_after(list, make_shared<List_node>(List_node{ 2,nullptr }));
		insert_after(list->next, make_shared<List_node>(List_node{ 3,nullptr }));
		auto s = reverse_list2(list, 1, 3);
		assert(s->data == 3 && s->next->data == 2 && s->next->next->data == 1 && s->next->next->next == nullptr);
		list.reset();
	}
	{
		list = make_shared<List_node>(List_node{ 1,nullptr });
		insert_after(list, make_shared<List_node>(List_node{ 2,nullptr }));
		insert_after(list->next, make_shared<List_node>(List_node{ 3,nullptr }));
		auto c = reverse_list2(list, 2, 3);
		assert(c->data == 1 && c->next->data == 3 && c->next->next->data == 2 && c->next->next->next == nullptr);
		list.reset();
	}
	{
		auto u = reverse_list2(list, 0, 0);
		assert(u == nullptr);
	}
}

void test_full_reverse()
{
	// three elements
	shared_ptr<List_node>list = make_shared<List_node>(List_node{
		1,make_shared<List_node>(List_node{
		2,make_shared<List_node>(List_node{
		3,nullptr }) }) });
	list = reverse_full_list(list);
	assert(list->data == 3 && list->next->data == 2 && list->next->next->data == 1 && list->next->next->next == nullptr);
	list.reset();

	// zero elements
	list = nullptr;
	list = reverse_full_list(list);
	assert(list == nullptr);
	list.reset();

	// one element
	list = make_shared<List_node>(List_node{ 1,nullptr });
	list = reverse_full_list(list);
	assert(list->data == 1 && list->next == nullptr);
	list.reset();

	//two elements
	list = make_shared<List_node>(List_node{
		1,make_shared<List_node>(List_node{
		2,nullptr}) });
	list = reverse_full_list(list);
	assert(list->data == 2 && list->next->data == 1 && list->next->next == nullptr);
}

void test_reverse_k()
{
	shared_ptr<List_node>list;
	
	// k=2
	list = make_shared<List_node>(List_node{ 1,nullptr });
	insert_after(list, make_shared<List_node>(List_node{ 2,nullptr }));
	insert_after(list->next, make_shared<List_node>(List_node{ 3,nullptr }));
	insert_after(list->next->next, make_shared<List_node>(List_node{ 4,nullptr }));
	insert_after(list->next->next->next, make_shared<List_node>(List_node{ 5,nullptr }));
	insert_after(list->next->next->next->next, make_shared<List_node>(List_node{ 6,nullptr }));
	list =reverse_k(list,2);
	assert(list->data == 2 && list->next->data == 1 && list->next->next->data == 4 && list->next->next->next->data == 3 && list->next->next->next->next->data == 6 && list->next->next->next->next->next->data == 5);

	// k=1
	list = reverse_k(list, 1);
	assert(list->data == 2 && list->next->data == 1 && list->next->next->data == 4 && list->next->next->next->data == 3 && list->next->next->next->next->data == 6 && list->next->next->next->next->next->data == 5);

	// k=3
	list.reset();
	list = make_shared<List_node>(List_node{ 1,nullptr });
	insert_after(list, make_shared<List_node>(List_node{ 2,nullptr }));
	insert_after(list->next, make_shared<List_node>(List_node{ 3,nullptr }));
	insert_after(list->next->next, make_shared<List_node>(List_node{ 4,nullptr }));
	insert_after(list->next->next->next, make_shared<List_node>(List_node{ 5,nullptr }));
	insert_after(list->next->next->next->next, make_shared<List_node>(List_node{ 6,nullptr }));
	list = reverse_k(list, 3);
	assert(list->data == 3 && list->next->data == 2 && list->next->next->data == 1 && list->next->next->next->data == 6 && list->next->next->next->next->data == 5 && list->next->next->next->next->next->data == 4);

	// list length mod k != 0
	list.reset();
	list = make_shared<List_node>(List_node{ 1,nullptr });
	insert_after(list, make_shared<List_node>(List_node{ 2,nullptr }));
	insert_after(list->next, make_shared<List_node>(List_node{ 3,nullptr }));
	insert_after(list->next->next, make_shared<List_node>(List_node{ 4,nullptr }));
	insert_after(list->next->next->next, make_shared<List_node>(List_node{ 5,nullptr }));
	insert_after(list->next->next->next->next, make_shared<List_node>(List_node{ 6,nullptr }));
	list = reverse_k(list, 4);
	assert(list->data == 4 && list->next->data == 3 && list->next->next->data == 2 && list->next->next->next->data == 1 && list->next->next->next->next->data == 5 && list->next->next->next->next->next->data == 6);
}