// test whether a singly linked list is palindromic
#include <memory>
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

struct List_node {
	int data;
	shared_ptr<List_node>next;
};

struct Double_node {
	int data;
	shared_ptr<Double_node>next;
	shared_ptr<Double_node>prev;
};
void print(shared_ptr<List_node>head);

void reverse_list(shared_ptr<List_node>pre_head)
{
	auto reverse_list_iter = pre_head->next;
	while (reverse_list_iter->next)
	{
		auto temp = reverse_list_iter->next;
		reverse_list_iter->next = temp->next;
		temp->next = pre_head->next;
		pre_head->next = temp;
	}
}

bool is_palindromic(const shared_ptr<List_node>&head)
{
	if (!head->next)return true; // one element
	auto first_half = head;
	auto second_half_pre_head = head;
	auto fast = head;
	while (fast && fast->next)
	{
		fast = fast->next->next;
		if (fast)second_half_pre_head = second_half_pre_head->next;
	}
	reverse_list(second_half_pre_head);

	auto second_half = second_half_pre_head->next;
	while (second_half)
	{
		if (second_half->data != first_half->data)
		{
			reverse_list(second_half_pre_head);
			return false;
		}
		second_half = second_half->next;
		first_half = first_half->next;
	}
	reverse_list(second_half_pre_head);
	return true;
} // time O(n) space O(1)

bool is_palindromic_double(shared_ptr<Double_node>head,shared_ptr<Double_node>tail)
{
	while (head != tail)
	{
		if (head->data != tail->data)return false;
		if (head->next == tail)break;
		head = head->next;
		tail = tail->prev;
	}
	return true;
} // time O(n) space O(1)

void print(shared_ptr<List_node>head)
{
	while (head)
	{
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
}

shared_ptr<List_node> create_list(const vector<int>&arr)
{
	shared_ptr<List_node>fake_head = make_shared<List_node>(List_node{});
	auto tail = fake_head;
	for (int i = 0; i < arr.size(); ++i)
	{
		tail->next= make_shared<List_node>(List_node{arr[i],nullptr});
		tail = tail->next;
	}
	return fake_head->next;
}

shared_ptr<Double_node> create_double_list(const vector<int>&arr)
{
	shared_ptr<Double_node>fake_head = make_shared<Double_node>(Double_node{});
	auto tail = fake_head;
	for (int i = 0; i < arr.size(); ++i)
	{
		tail->next= make_shared<Double_node>(Double_node{arr[i]});
		tail->next->prev = tail == fake_head ? nullptr : tail;
		tail = tail->next;
	}
	return fake_head->next;
}

shared_ptr<Double_node> find_tail(shared_ptr<Double_node>head)
{
	while (head->next)head = head->next;
	return head;
}

void main()
{
	// singly linked list
	{
		shared_ptr<List_node>list{};
		{
			list = create_list({ 1 });
			assert(is_palindromic(list));
		}
		{
			list = create_list({ 2,2 });
			assert(is_palindromic(list));
		}
		{
			list = create_list({ 1,2,2,1 });
			assert(is_palindromic(list));
		}
		{
			list = create_list({ 3,1,2,2,1,3 });
			assert(is_palindromic(list));
		}
		{
			list = create_list({ 1,2,5,2,1 });
			assert(is_palindromic(list));
		}
		{
			list = create_list({ 2,1 });
			assert(!is_palindromic(list));
		}
		{
			list = create_list({ 1,2,2,2 });
			assert(!is_palindromic(list));
		}
		{
			list = create_list({ 3,1,2,2,1,2 });
			assert(!is_palindromic(list));
		}
		{
			list = create_list({ 1,2,5,2,3 });
			assert(!is_palindromic(list));
		}
	}

	// doubly linked list
	{
		shared_ptr<Double_node>double_list{};
		{
			double_list = create_double_list({ 1,2,3,4,4,3,2,1 });
			assert(is_palindromic_double(double_list, find_tail(double_list)));
		}
		{
			double_list = create_double_list({ 1,2,3,4,4,3,2 });
			assert(!is_palindromic_double(double_list, find_tail(double_list)));
		}
	}
	system("pause");
}