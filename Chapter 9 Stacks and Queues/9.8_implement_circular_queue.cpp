// implement a curcular queue
#include <vector>
#include <iostream>
#include <stdexcept>
#include <assert.h>
#include <algorithm>
using namespace std;

class Queue {
public:
	Queue(unsigned size) :queue_(size) {};
	unsigned size()const { return elements_; };
	void enqueue(int data);
	int dequeue();
//private:
	int head_{0};
	int tail_{0};
	int elements_{ 0 };
	vector<int>queue_;
}; // amortized enqueue() O(1), dequeue O(1)

void Queue::enqueue(int data)
{
	if (elements_ == queue_.size())
	{
		rotate(queue_.begin(), queue_.begin() + head_, queue_.end());
		head_ = 0;
		tail_ = elements_;
		queue_.resize(queue_.size() * 2);
	}
	queue_[tail_] = data;
	tail_ = (tail_ + 1) % queue_.size();
	++elements_;
}

int Queue::dequeue()
{
	if (!size())throw length_error("dequeue(): empty queue");
	
	int res = queue_[head_];
	--elements_;
	head_ = (head_ + 1) % queue_.size();
	return res;
}

void small_test();

void main()
{
	small_test();
	Queue q{ 1 };
	try { q.dequeue(); assert(false); }
	catch (const exception& e) { cout << e.what() << endl; }

	q.enqueue(1);
	q.enqueue(2);
	assert(q.queue_.size() == 2);
	assert(q.dequeue() == 1);
	assert(q.dequeue() == 2);
	q.enqueue(1);
	assert(q.queue_.size() == 2);
	assert(q.dequeue() == 1);


	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	assert(q.queue_.size() == 4);
	assert(q.dequeue() == 1);
	assert(q.dequeue() == 2);
	assert(q.dequeue() == 3);
	try { q.dequeue(); assert(false); }
	catch (const exception& e) { cout << e.what() << endl; }


	system("pause");
}

void small_test()
{
	Queue q(8);
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);
	q.enqueue(6);
	q.enqueue(7);
	q.enqueue(8);
	// Now head = 0 and tail = 0

	assert(1 == q.dequeue());
	assert(2 == q.dequeue());
	assert(3 == q.dequeue());
	// Now head = 3 and tail = 0

	q.enqueue(11);
	q.enqueue(12);
	q.enqueue(13);
	// Ok till here. Now head = 3 and tail = 3

	q.enqueue(14);  // now the vector (data) is resized; but the head and tail.
					// (or elements) does not change accordingly.
	q.enqueue(15);
	q.enqueue(16);
	q.enqueue(17);
	q.enqueue(18);
	// The elements starting from head=3 are over-written!

	assert(4 == q.dequeue());
	assert(5 == q.dequeue());
	assert(6 == q.dequeue());
	assert(7 == q.dequeue());
	assert(8 == q.dequeue());
	assert(11 == q.dequeue());
	assert(12 == q.dequeue());
}
