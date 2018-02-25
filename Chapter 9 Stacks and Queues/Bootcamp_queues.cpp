// Queue with max() O(n)
#include <list>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <assert.h>
using namespace std;

class Queue {
public:
	void enqueue(int data)
	{
		queue_.emplace_back(data);
	}
	int dequeue()
	{
		if (!queue_.empty())
		{
			int res = queue_.front();
			queue_.pop_front();
			return res;
		}
		else throw length_error("dequeue(): empty queue");
	}
	int q_max()
	{
		if (!queue_.empty())
		{
			return *(max_element(queue_.begin(), queue_.end()));
		}
		else throw length_error("max(): empty queue");
	}
private:
	list<int>queue_;
}; // enqueue O(1) dequeue O(1) max O(n)

void test()
{
	Queue q{};
	q.enqueue(1);
	q.enqueue(2);
	assert(q.q_max() == 2);
	assert(q.dequeue() == 1);
	assert(q.q_max() == 2);
	assert(q.dequeue() == 2);
	
	// dequeue() on empty queue
	try {
		q.dequeue();
		assert(false);
	}
	catch (const exception& error)
	{
		cout << error.what() << endl;
	}

	// q_max() om empty queue
	try {
		q.q_max();
		assert(false);
	}
	catch (const exception& error)
	{
		cout << error.what() << endl;
	}
}

void main()
{
	test();
	system("pause");
}