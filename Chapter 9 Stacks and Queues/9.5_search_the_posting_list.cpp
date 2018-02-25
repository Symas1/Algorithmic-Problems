// search the posting list
#include <memory>
#include <iostream>
#include <vector>
#include <assert.h>
#include <stack>
using namespace std;

struct Posting_list {
	int order{ -1 };
	shared_ptr<Posting_list>jump;
	shared_ptr<Posting_list>next;
};
void r_order_helper(const shared_ptr<Posting_list>&list, shared_ptr<int>& order);
void r_order(const shared_ptr<Posting_list>&list)
{
	r_order_helper(list, make_shared<int>(0));
} // time O(n) space O(n) - stack

void r_order_helper(const shared_ptr<Posting_list>&list,shared_ptr<int>& order)
{
	if (list && list->order == -1)
	{
		list->order = (*order)++;
		r_order_helper(list->jump, order);
		r_order_helper(list->next, order);
	}
}

void i_order(const shared_ptr<Posting_list>&list)
{
	auto head = list;
	auto iter = list;
	int ord = 0;
	while (head)
	{
		while (true)
		{
			if (iter&&iter->order == -1)
			{
				iter->order = ord++;
				iter = iter->jump;
			}
			else break;
		}
		head = head->next;
		iter = head;
	}
} // time O(n) space O(1)

void i_order_stack(const shared_ptr<Posting_list>&list)
{
	stack<shared_ptr<Posting_list>>s{ {list} };
	int order = 0;
	while (!s.empty())
	{
		auto curr = s.top();
		s.pop();
		if (curr && curr->order == -1)
		{
			curr->order = order++;
			s.emplace(curr->next);
			s.emplace(curr->jump);
		}
	}
} // time O(n) space O(n)

shared_ptr<Posting_list> test_head()
{
	auto node0 = make_shared<Posting_list>(Posting_list{});
	auto node1 = make_shared<Posting_list>(Posting_list{});
	auto node2 = make_shared<Posting_list>(Posting_list{});
	auto node3 = make_shared<Posting_list>(Posting_list{});
	node0->next = node1;
	node1->next = node2;
	node2->next = node3;

	node0->jump = node2;
	node1->jump = node3;
	node2->jump = node1;
	node3->jump = node3;

	return node0;
}

bool check_eq(shared_ptr<Posting_list>list,const vector<int>& arr)
{
	for (int i = 0; i < arr.size(); ++i)
	{
		if (list->order != arr[i])return false;
		list = list->next;
	}
	return true;
}

void main()
{
	{
		auto node0 = test_head();
		r_order(node0);
		assert(check_eq(node0, { 0,2,1,3 }));
	}
	{
		auto node0 = test_head();
		i_order_stack(node0);
		assert(check_eq(node0, { 0,2,1,3 }));
	}
	{
		auto node0 = test_head();
		i_order(node0);
		assert(check_eq(node0, { 0,2,1,3 }));
	}
	system("pause");
}