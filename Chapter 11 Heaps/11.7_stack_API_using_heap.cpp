#include <queue>
#include<assert.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <functional>
#include <vector>
#include <stdexcept>
using namespace std;

class Stack
{
public:
	void push(int data);
	int top()const;
	void pop();
	unsigned size()const;
private:
	struct Entry {
		Entry(int data_, unsigned priority_) :data{ data_ }, priority{ priority_ } {};
		int data;
		unsigned priority;
	};
	unsigned size_ = 0;
	unsigned priority_ = 0;
	priority_queue<Entry, vector<Entry>, function<bool(const Entry&, const Entry&)>>q_{ [](const Entry& fir, const Entry& sec)
	{return fir.priority < sec.priority; } };
};

void Stack::push(int data)
{
	++size_;
	q_.emplace(data, priority_++);
} // time O(logn); space O(1)

int Stack::top() const
{
	if (!size_)throw length_error("top(): empty stack");

	return q_.top().data;
} // time O(1); space O(1)

void Stack::pop()
{
	if (!size_)throw length_error("pop(): empty stack");

	q_.pop();
	--size_;
	--priority_;
} // time O(logn); space O(1)

unsigned Stack::size() const
{
	return size_;
} // time O(1); space O(1)


class Queue
{
public:
	void push(int data)
	{
		q_.emplace(data, priority_++);
		++size_;
	}
	int top()const {
		if (!size_)throw length_error("top(): empty queue");
		return	q_.top().data;
	};
	void pop() {
		if (!size_)throw length_error("pop(): empty queue");

		q_.pop();
		--size_;
		--priority_;
	};
	unsigned size()const { return size_; };
private:
	struct Entry {
		Entry(int data_, unsigned priority_) :data{ data_ }, priority{ priority_ } {};
		int data;
		unsigned priority;
	};
	unsigned size_ = 0;
	unsigned priority_ = 0;
	priority_queue<Entry, vector<Entry>, function<bool(const Entry&, const Entry&)>>q_{ [](const Entry& fir, const Entry& sec)
	{return fir.priority > sec.priority; } };
};


void test_stack();
void test_queue();

void main()
{
	test_stack();
	test_queue();
	system("pause");
}

void test_stack()
{
	Stack s;

	assert(s.size() == 0);
	try {
		s.top();
		assert(false);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	try {
		s.pop();
		assert(false);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	s.push(1);
	assert(s.size() == 1);
	assert(s.top() == 1);
	s.pop();

	assert(s.size() == 0);

	s.push(1);
	s.push(2);
	s.push(3);
	assert(s.size() == 3);
	assert(s.top() == 3);
	s.pop();
	assert(s.size() == 2);
	assert(s.top() == 2);
	s.pop();
	assert(s.size() == 1);
	assert(s.top() == 1);
	s.pop();
	try {
		s.top();
		assert(false);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	try {
		s.pop();
		assert(false);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
}

void test_queue()
{
	Queue q{};

	assert(q.size() == 0);
	try {
		q.top();
		assert(false);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	try {
		q.pop();
		assert(false);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	q.push(1);
	assert(q.size() == 1);
	assert(q.top() == 1);
	q.pop();

	q.push(1);
	q.push(2);
	q.push(3);
	assert(q.size() == 3);
	assert(q.top() == 1);
	q.pop();
	assert(q.size() == 2);
	assert(q.top() == 2);
	q.pop();
	assert(q.size() == 1);
	assert(q.top() == 3);
	q.pop();

	try {
		q.top();
		assert(false);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	try {
		q.pop();
		assert(false);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
}