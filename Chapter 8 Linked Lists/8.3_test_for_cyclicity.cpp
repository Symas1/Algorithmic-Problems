// test singly linked list for cyclicity
#include <memory>
#include <iostream>
#include <assert.h>
using namespace std;

struct List_node {
	int data;
	shared_ptr<List_node>next;
};

shared_ptr<List_node> cyclicity_floyd(const shared_ptr<List_node>&head) // hare and tortoise
{
	auto slow = head;
	auto fast = head;

	while (fast && fast->next && fast->next->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (fast == slow)
		{
			slow = head;
			while (slow != fast)slow = slow->next, fast = fast->next;
			return slow; // start of the cycle
		}
	}
	return nullptr;
} // time O(n) - (O(F) to reach cycle + O(C) cycle length) space O(1)

shared_ptr<List_node> cyclicity_brent(const shared_ptr<List_node>&head)
{
	shared_ptr<List_node> slow{};
	auto fast = head;

	int steps = 1;
	int teleport = 1;
	while (fast&&fast->next)
	{
		if (steps == teleport)
		{
			teleport *= 2;
			slow = fast;
			steps = 0;
		}

		fast = fast->next;
		++steps;
		if (fast == slow)
		{
			slow = head;
			fast = head;
			while (steps--)fast = fast->next;
			while (fast != slow)fast = fast->next, slow = slow->next;
			return slow;
		}
	}
	return nullptr;
} // time O(n) space O(1) 24-36% faster on average than Floyd's algorithm
 
shared_ptr<List_node> create_cyclic_list(unsigned length, unsigned cycle_to)
{
	if (length == 0)return nullptr;
	shared_ptr<List_node>fake_head = make_shared<List_node>(List_node{});
	auto tail = fake_head;
	shared_ptr<List_node>cycle_node{};
	for (int i = 1; i <= length; ++i)
	{
		tail->next = make_shared<List_node>(List_node{ i,nullptr });
		if (i == cycle_to)cycle_node = tail->next;
		tail = tail->next;
	}
	tail->next = cycle_node;
	return fake_head->next;
}

shared_ptr<List_node> create_list(unsigned length)
{
	if (length == 0)return nullptr;
	shared_ptr<List_node>fake_head = make_shared<List_node>(List_node{});
	auto tail = fake_head;
	for (int i = 1; i <= length; ++i)
	{
		tail->next = make_shared<List_node>(List_node{ i,nullptr });
		tail = tail->next;
	}
	return fake_head->next;
}

void test_cyclicity();

void main()
{
	test_cyclicity();
	system("pause");
}

void test_cyclicity()
{
	// tests for lists with cycles
	for (int i = 1; i <= 10; ++i)
	{
		for (int j = 1; j <= i; ++j)
		{
			auto list = create_cyclic_list(i, j);
			shared_ptr<List_node>cycle_start = make_shared<List_node>(List_node{0,list});
			for (int k = 1; k <= j; ++k)
			{
				cycle_start = cycle_start->next;
			}

			auto floyd = cyclicity_floyd(list);
			auto brent = cyclicity_brent(list);

			assert(floyd == cycle_start && brent == cycle_start);
		}
	}

	// tests for lists without cycles
	for (int i = 0; i <= 10; ++i)
	{
		auto list = create_list(i);

		auto floyd = cyclicity_floyd(list);
		auto brent = cyclicity_brent(list);

		assert(floyd == nullptr && brent == nullptr);
	}
}