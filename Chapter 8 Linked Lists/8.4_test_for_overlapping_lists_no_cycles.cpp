// test for overlapping lists - lists are cycle-free
#include <memory>
#include <assert.h>
#include <iostream>
using namespace std;

struct List_node
{
	int data;
	shared_ptr<List_node>next;
};

int length(shared_ptr<List_node>head);
void advance_iter(shared_ptr<List_node>&iter, unsigned k);
shared_ptr<List_node> test_overlap(shared_ptr<List_node> first, shared_ptr<List_node>second)
{
	auto first_length = length(first);
	auto second_length = length(second);
	advance_iter(first_length > second_length ? first : second, abs(first_length - second_length));

	while (first&&second && first != second)
	{
		first = first->next;
		second = second->next;
	}
	return first;
} // time O(n) space O(1)

int length(shared_ptr<List_node>head)
{
	int ans = 0;
	while (head)
	{
		++ans, head = head->next;
	}
	return ans;
}

void advance_iter(shared_ptr<List_node>&iter, unsigned k)
{
	while (k--)
	{
		iter = iter->next;
	}
}

shared_ptr<List_node> create_list(unsigned length)
{
	shared_ptr<List_node>fake_head = make_shared<List_node>(List_node{});
	auto tail = fake_head;
	for (int i = 1; i <= length; ++i)
	{
		tail->next= make_shared<List_node>(List_node{i,nullptr});
		tail = tail->next;
	}
	return fake_head->next;
}
void unite_lists(shared_ptr<List_node>first, shared_ptr<List_node> second,unsigned connect_to)
{
	while (first->next)first = first->next;
	while (--connect_to)second = second->next;
	first->next = second;
}

void test();

void main()
{
	test();
	system("pause");
}

void test()
{
	for (int i = 1; i < 10; ++i)
	{
		for (int j = 1; j < 10; ++j)
		{
			auto first_n = create_list(i);
			auto second_n = create_list(j);
			assert(test_overlap(first_n, second_n) == nullptr);
			assert(test_overlap(second_n, first_n) == nullptr);
			for (int k = 1; k <= j; ++k)
			{
				auto first = create_list(i);
				auto second = create_list(j);
				unite_lists(first, second, k);
				shared_ptr<List_node>overlap = make_shared<List_node>(List_node{0,second});
				for (int q = 1; q <= k; ++q)
				{
					overlap = overlap->next;
				}
				assert(test_overlap(first, second) == overlap);
				assert(test_overlap(second, first) == overlap);
			}
		}
	}
}