#include <memory>
#include <iostream>
#include <stack>
using namespace std;

struct List_node {
	int data;
	shared_ptr<List_node>next;
};

void print_reverse(shared_ptr<List_node>head)
{
	stack<int>nodes{};
	while (head)
	{
		nodes.emplace(head->data);
		head = head->next;
	}
	while (!nodes.empty())
	{
		cout << nodes.top() << " ";
		nodes.pop();
	}
	cout << endl;
}

void main()
{
	auto list = make_shared<List_node>(List_node{ 1,
		make_shared<List_node>(List_node{2,
			make_shared<List_node>(List_node{3,nullptr})}) });
	print_reverse(list);
	system("pause");
}