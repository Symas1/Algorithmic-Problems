// implement even-odd merge
#include <memory>
#include <iostream>
#include <assert.h>
#include <random>
#include <array>
using namespace std;

struct List_node {
	int data;
	shared_ptr<List_node>next;
};

void merge(const shared_ptr<List_node>&head)
{
	if (head == nullptr)return;
	auto even_fake_head = make_shared<List_node>(List_node{});
	auto odd_fake_head = make_shared<List_node>(List_node{});
	array<shared_ptr<List_node>, 2>tails{ even_fake_head,odd_fake_head };
	int turn = 0;
	for (auto iter = head; iter; iter = iter->next)
	{
		tails[turn]->next = iter;
		tails[turn] = tails[turn]->next;
		turn ^= 1;
	}
	tails[1]->next = nullptr;
	tails[0]->next = odd_fake_head->next;
} // time O(n) space O(1)

shared_ptr<List_node> create_list(int k)
{
	shared_ptr<List_node>fake_head = make_shared<List_node>(List_node{});
	auto tail = fake_head;
	for (int i = 0; i < k; ++i)
	{
		tail->next= make_shared<List_node>(List_node{i,nullptr});
		tail = tail->next;
	}
	return fake_head->next;
}

void check(shared_ptr<List_node>head)
{
	bool found_odd = false;
	while (head)
	{
		if (head->data % 2 == 0)assert(found_odd == false);
		else
		{
			found_odd = true;
		}
		head = head->next;
	}
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
void main()
{
	mt19937 mt{ random_device{}() };
	uniform_int_distribution<int>size{ 1,100 };
	for (int i = 0; i < 1000; ++i)
	{
		auto s = size(mt);
		auto list = create_list(s);
		merge(list);
		check(list);
	}
	system("pause");
}