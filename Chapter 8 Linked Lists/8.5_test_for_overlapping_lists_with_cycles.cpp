// test for overlapping lists - lists may have cycles
#include <memory>
#include <iostream>
#include <assert.h>
using namespace std;

struct List_node
{
	int data;
	shared_ptr<List_node>next;
};

shared_ptr<List_node> has_cycle(const shared_ptr<List_node>& list)
{
	auto fast = list;
	auto slow = list;
	while (fast && fast->next && fast->next->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
		{
			slow = list;
			while (slow != fast) { slow = slow->next, fast = fast->next; }
			return slow;
		}
	}
	return nullptr;
}

int length(shared_ptr<List_node> list)
{
	int ans = 0;
	while (list)++ans, list = list->next;
	return ans;
}

void advance_iter(shared_ptr<List_node>&iter, int k)
{
	while (k--) { iter = iter->next; }
}

int distance_my(shared_ptr<List_node>first, shared_ptr<List_node>second)
{
	int res = 0;
	while (first != second)first = first->next, ++res;
	return res;
}

shared_ptr<List_node> is_overlap(const shared_ptr<List_node>&first, const shared_ptr<List_node>& second)
{
	auto first_cycle = has_cycle(first);
	auto second_cycle = has_cycle(second);

	auto second_head = second;
	auto first_head = first;
	if (!first_cycle && !second_cycle) // first case - both lists dont have cycles
	{
		auto first_l = length(first);
		auto second_l = length(second);

		advance_iter(first_l > second_l ? first_head : second_head, abs(first_l - second_l));
		while (first_head&&second_head && (second_head != first_head))
		{
			first_head = first_head->next;
			second_head = second_head->next;
		}
		return first_head;
	}
	else if ((!first_cycle&&second_cycle) || (first_cycle && !second_cycle))// second case - one list has cycle and other doesnt	
	{
		return nullptr;
	}
	else // third case - both lists have cycles
	{
		auto temp = first_cycle;
		do {
			temp = temp->next;
		} while (temp != first_cycle && temp != second_cycle);
		if (temp != second_cycle)return nullptr; // cycles are disjoint

		int first_dist = distance_my(first, first_cycle), second_dist = distance_my(second, second_cycle);
		advance_iter(first_dist > second_dist ? first_head : second_head, abs(first_dist - second_dist));
		while (second_head != first_head&&first_head != first_cycle&&second_head != second_cycle)
		{
			first_head = first_head->next;
			second_head = second_head->next;
		}
		return second_head == first_head ? second_head : first_cycle;
	}
} // time O(n+m) space O(1)

void test_cyclicity();

shared_ptr<List_node>create_list(int length)
{
	shared_ptr<List_node>fake_head = make_shared<List_node>(List_node{});
	auto tail = fake_head;
	for (int i = 1; i <= length; ++i)
	{
		tail->next = make_shared<List_node>(List_node{ i,nullptr });
		tail = tail->next;
	}
	return fake_head->next;
}

void connect_list(shared_ptr<List_node>first, shared_ptr<List_node>second, int connect_to)
{
	while (first->next)first = first->next;
	shared_ptr<List_node>fake_head = make_shared<List_node>(List_node{ 0,second });
	while (connect_to--)fake_head = fake_head->next;
	first->next = fake_head;
}

void make_cycle(shared_ptr<List_node>list, int cycle_to)
{
	shared_ptr<List_node>fake_head = make_shared<List_node>(List_node{ 0,list });
	while (cycle_to--)fake_head = fake_head->next;
	while (list->next)list = list->next;
	list->next = fake_head;
}
shared_ptr<List_node> find_k(shared_ptr<List_node>list, int k)
{
	if (k == 0)return nullptr;
	shared_ptr<List_node>fake_head = make_shared<List_node>(List_node{ 0,list });
	while (k--)fake_head = fake_head->next;
	return fake_head;
}
void main()
{
	test_cyclicity();
	system("pause");
}

void test_cyclicity()
{
	// lists dont have cycles
	for (int i = 1; i <= 10; ++i)
	{
		for (int j = 1; j <= 10; ++j)
		{
			// lists not connected
			auto list1 = create_list(i);
			auto list2 = create_list(j);
			assert(is_overlap(list1, list2) == nullptr);
			assert(is_overlap(list2, list1) == nullptr);
			for (int k = 1; k <= j; ++k)
			{
				// lists are connected
				auto list1 = create_list(i);
				auto list2 = create_list(j);
				connect_list(list1, list2, k);
				auto test = find_k(list2, k);
				assert(is_overlap(list1, list2) == test);
				assert(is_overlap(list2, list1) == test);
			}
		}
	}

	// lists have cycles
	{
		auto list1 = create_list(6);
		auto list2 = create_list(2);
		make_cycle(list1, 5);
		connect_list(list2, list1, 4);
		assert(is_overlap(list2, list1) == find_k(list1, 4));
	}
	{
		auto list1 = create_list(6);
		auto list2 = create_list(2);
		make_cycle(list1, 5);
		connect_list(list2, list1, 3);
		assert(is_overlap(list2, list1) == find_k(list1, 3));
	}
}