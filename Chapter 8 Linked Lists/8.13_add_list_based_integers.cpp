// add list-based integers
#include <memory>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

struct List_node {
	int data;
	shared_ptr<List_node>next;
};

shared_ptr<List_node> add2(shared_ptr<List_node>first, shared_ptr<List_node>second)
{
	auto fake_head = make_shared<List_node>(List_node{});
	auto tail = fake_head;
	int carry = 0;
	while (first || second || carry)
	{
		int num = carry + (first ? first->data : 0) + (second ? second->data : 0);
		tail->next= make_shared<List_node>(List_node{num%10,nullptr});
		first = first ? first->next : nullptr, second = second ? second->next : nullptr;
		tail = tail->next, carry = num / 10;
	}
	return fake_head->next;
} // time O(n+m) space O(max(n,m))
shared_ptr<List_node> reverse_list(shared_ptr<List_node>first);
shared_ptr<List_node> add_variant1(shared_ptr<List_node>first, shared_ptr<List_node>second)
{
	first = reverse_list(first);
	second = reverse_list(second);

	auto res = add2(first, second);

	first = reverse_list(first);
	second = reverse_list(second);
	res = reverse_list(res);
	return res;
} // time O(n+m) space O(max(n,m))

shared_ptr<List_node> reverse_list(shared_ptr<List_node>first)
{
	auto head = first;
	while (first->next)
	{
		auto temp = first->next;
		first->next = temp ? temp->next : nullptr;
		temp->next = head;
		head = temp;
	}
	return head;
}

shared_ptr<List_node> create_list(const vector<int>&arr)
{
	shared_ptr<List_node>res = make_shared<List_node>(List_node{});
	auto res_tail = res;
	for (int i = 0; i < arr.size(); ++i)
	{
		res_tail->next = make_shared<List_node>(List_node{ arr[i] ,nullptr });
		res_tail = res_tail->next;
	}
	return res->next;
}

void print(shared_ptr<List_node>head)
{
	while (head)
	{
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
}

void print_reverse(shared_ptr<List_node>head)
{
	vector<int>res{};
	while (head)
	{
		res.push_back(head->data);
		head = head->next;
	}
	copy(res.rbegin(), res.rend(), ostream_iterator<int>{ cout," " });
	cout << endl;
}

void main()
{
	{
		auto first = create_list({ 3,1,4 });
		auto second = create_list({ 7,0,9 });
		print_reverse(first);
		print_reverse(second);
		auto res = add2(first, second);
		print_reverse(res);
	}
	{
		auto first = create_list({ 9,9,9,9,9,9,9,9 });
		auto second = create_list({ 5,5,5 });
		print_reverse(first);
		print_reverse(second);
		auto res = add2(first, second);
		print_reverse(res);
	}
	{
		auto first = create_list({ 4,1,3 });
		auto second = create_list({ 9,0,7});
		print(first);
		print(second);
		auto res = add_variant1(first, second);
		print(res);
	}
	{
		auto first = create_list({ 9,9,9,9,9,9,9,9 });
		auto second = create_list({ 5,5,5 });
		print(first);
		print(second);
		auto res = add_variant1(first, second);
		print(res);
	}
	system("pause");
}