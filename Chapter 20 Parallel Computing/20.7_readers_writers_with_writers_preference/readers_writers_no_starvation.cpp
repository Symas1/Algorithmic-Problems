//Third readers-writers problem (no starvation for both sides)
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>

#include "Ordered_semaphore.h"

using namespace std;

class Readers_writers {
public:
	void read(){
		while (true) {
			{
				semaphore_.acquire();
				lock_guard<mutex>readers_lock{ readers_mx_ };
				if (++current_readers_ == 1) {
					resource_mx_.lock();
				}
				semaphore_.release();
			}
			++count_reads_;
			{
				lock_guard<mutex>readers_lock{ readers_mx_ };
				if (--current_readers_ == 0) {
					resource_mx_.unlock();
				}
			}
		}
	}
	void write() {
		while (true) {
			semaphore_.acquire();
			lock_guard<mutex>lock{ resource_mx_ };
			semaphore_.release();
			++count_writes_;
		}
	}

	atomic<unsigned>count_reads_{ 0 };
	atomic<unsigned>count_writes_{ 0 };
private:
	unsigned current_readers_{ 0 };

	Ordered_semaphore semaphore_{ 1 };
	mutex readers_mx_;
	mutex resource_mx_;
};

void main() {
	Readers_writers rw;
	vector<thread>threads;
	for (int i = 0; i < 5; ++i) {
		threads.emplace_back(&Readers_writers::read, &rw);
		threads.emplace_back(&Readers_writers::write, &rw);
	}

	this_thread::sleep_for(chrono::seconds(3));
	unsigned r = rw.count_reads_;
	unsigned w = rw.count_writes_;
	unsigned sum = r + w;
	cout << "Reads: " << r << " Writes: " << w << " Sum: " << sum << endl;
	cout << "Reads: "<<r / (double)sum << "% Writes: " << w / (double)sum <<"%"<< endl;
	system("pause");
}
