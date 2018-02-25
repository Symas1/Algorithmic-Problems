// implement fast sorting algorithm for lists
#include <memory>
#include <iostream>
#include <assert.h>
#include <map>
#include <iterator>
#include <algorithm>
#include <random>
#include <list>
#include <thread>
#include <chrono>
using namespace std;

struct Node {
	int data;
	shared_ptr<Node>next;
};

shared_ptr<Node> list_sort(shared_ptr<Node> head)
{
	if (!head)return{};
	map<int, list<shared_ptr<Node>>>map{};
	while (head)
	{
		auto iter = map.find(head->data);
		if (iter == map.end())
		{
			map.emplace(head->data, list<shared_ptr<Node>>{ head });
		}
		else
		{
			iter->second.back()->next = head;
			iter->second.emplace_back(head);
		}
		head = head->next;
	}

	for (auto prev = map.begin(), curr = ++map.begin(); curr != map.end(); ++curr)
	{
		prev->second.back()->next = curr->second.front();
		prev = curr;
		if (curr == --map.end())curr->second.back()->next = nullptr;
	}

	return map.begin()->second.front();
} // time worst-case O(nlogn), average O(nlogm) m - distinct elements; space worst-case O(logn), average O(logm)

void append(shared_ptr<Node>&node, shared_ptr<Node>&tail)
{
	tail->next = node;
	node = node->next;
	tail = tail->next;
}

shared_ptr<Node> merge(shared_ptr<Node>first, shared_ptr<Node>second)
{
	shared_ptr<Node>fake_head = make_shared<Node>(Node{});
	auto tail = fake_head;
	while (first && second)
	{
		append(first->data <= second->data ? first : second, tail);
	}
	tail->next = first ? first : second;
	return fake_head->next;
}

shared_ptr<Node> stable_list_sort(shared_ptr<Node>head)
{
	if (head == nullptr || head->next == nullptr)
		return head;

	shared_ptr<Node> pre_slow = nullptr, slow = head, fast = head;
	while (fast && fast->next)
	{
		pre_slow = slow;
		fast = fast->next->next, slow = slow->next;
	}

	pre_slow->next = nullptr;

	return merge(stable_list_sort(head), stable_list_sort(slow));
} // time O(nlogn); space O(logn)

shared_ptr<Node> generate_list(size_t size)
{
	mt19937 mt{ random_device{}() };
	shared_ptr<Node>fake_head = make_shared<Node>(Node{});
	auto head = fake_head;
	for (int i = 0; i < size; ++i)
	{
		int num = uniform_int_distribution<>{ 0,10 }(mt);
		head->next = make_shared<Node>(Node{ num,nullptr });
		head = head->next;
	}
	return fake_head->next;
}

void print_list(shared_ptr<Node> head)
{
	while (head)
	{
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
}

bool check(shared_ptr<Node> head)
{
	if (!head && !head->next)return true;
	auto curr = head->next;
	while (curr)
	{
		if (curr->data < head->data)return false;
		head = curr;
		curr = curr->next;
	}
	return true;
}

void main()
{
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 1000; ++times)
	{
		int size = uniform_int_distribution<>{ 0,1000}(mt);
		auto head = generate_list(size);
		head = stable_list_sort(head);
		assert(check(head));
	}
	system("pause");
}