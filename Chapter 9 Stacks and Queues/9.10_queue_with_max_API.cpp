// implements queue with max API
#include <queue>
#include <deque>
#include <iostream>
#include <assert.h>
#include <functional>
using namespace std;

class Queue{
public:
	void enqueue(int data);
	int dequeue();
	int q_max()const;
//private:
	queue<int>queue_;
	deque<pair<int, int>>max_q_;
}; // time: dequeue() - O(1), q_max() O(1); space for max: best-case O(1), worst-case O(n)
// amortized time for n enqueues and dequeues is O(n), since an element can be added and removed from deque no more than once

void Queue::enqueue(int data)
{
	if (queue_.empty())
	{
		queue_.emplace(data);
		max_q_.emplace_back(data, 1);
	}
	else
	{
		queue_.emplace(data);
		while (!max_q_.empty() && max_q_.back().first < data)
		{
			max_q_.pop_back();
		}
		if (!max_q_.empty() && max_q_.back().first == data)
		{
			++max_q_.back().second;
		}
		else
		{
			max_q_.emplace_back(data, 1);
		}
	}
}

int Queue::dequeue()
{
	if (queue_.empty())throw length_error("dequeue(): empty queue");

	auto ret = queue_.front();
	queue_.pop();
	if (ret == q_max())
	{
		--max_q_.front().second;
		if (max_q_.front().second == 0)max_q_.pop_front();
	}
	return ret;
}

int Queue::q_max()const
{
	if(max_q_.empty())throw length_error("q_max(): empty queue");
	return max_q_.front().first;
}

void main()
{
	Queue q{};
	q.enqueue(3);
	q.enqueue(3);
	
	// Queue: 3,3; Max: 3
	assert(q.q_max() == 3);

	q.enqueue(4);
	q.enqueue(3);
	// Queue: 3,3,4; Max: 4,3
	assert(q.q_max() == 4);
	assert(q.dequeue() == 3);
	assert(q.q_max() == 4);
	assert(q.dequeue() == 3);
	assert(q.q_max() == 4);
	assert(q.dequeue() == 4);
	assert(q.q_max() == 3);
	assert(q.dequeue() == 3);

	try { q.q_max(); assert(false); }
	catch (const exception& e) { cout << e.what() << endl; }

	try { q.dequeue(); assert(false); }
	catch (const exception& e) { cout << e.what() << endl; }
	system("pause");
}
