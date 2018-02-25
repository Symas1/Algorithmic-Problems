// Implement queue using stacks
#include <stack>
#include <iostream>
#include <stdexcept>
#include <assert.h>
using namespace std;

class Queue {
public:
	void enqueue(int data);
	int dequeue();
private:
	stack<int>enq_;
	stack<int>deq_;
}; // time O(m) for m operations (each element is pushed and popped no more than twice)

void Queue::enqueue(int data)
{
	enq_.emplace(data);
}

int Queue::dequeue()
{
	if (deq_.empty())
	{
		if (enq_.empty())throw length_error("dequeue(): empty queue");
		while (!enq_.empty())
		{
			deq_.emplace(enq_.top());
			enq_.pop();
		}
	}
	int res = deq_.top();
	deq_.pop();
	return res;
}

void main()
{
	Queue q{};
	// both stacks are empty
	try { q.dequeue(); assert(false); }
	catch (const exception& e) { cout << e.what() << endl; }

	// dequeue stack is empty and enqueue stack has one element
	q.enqueue(1);

	assert(q.dequeue() == 1);

	// both stacks should be empty again
	try { q.dequeue(); assert(false); }
	catch (const exception& e) { cout << e.what() << endl; }

	// dequeue stack is empty and enqueue stack has two elements
	q.enqueue(1);
	q.enqueue(2);

	// enqueue stack is empty and dequeue has two elements
	assert(q.dequeue()==1);

	q.enqueue(3);
	q.enqueue(4);
	// dequeue: 2, enqueue: 3,4

	assert(q.dequeue() == 2);
	assert(q.dequeue() == 3);
	assert(q.dequeue() == 4);

	// both stacks should be empty again
	try { q.dequeue(); assert(false); }
	catch (const exception& e) { cout << e.what() << endl; }
	system("pause");
}
