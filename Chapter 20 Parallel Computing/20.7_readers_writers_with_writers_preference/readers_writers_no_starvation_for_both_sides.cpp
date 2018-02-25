// Third readers-writers problem (no starvation for both sides)
#include <thread>
#include <vector>
#include <mutex>
#include <iostream>
#include <atomic>
using namespace std;

class Readers_writers {
public:
	void read() {
		while (true) {
			{
				unique_lock<mutex>enter_mutex{ enter_mx_ };
				lock_guard<mutex>pass{ pass_mx_ };
				if (++readers_ == 1) {
					resource_mx_.lock();
				}
			}
			++count_reads_;
			{
				lock_guard<mutex>enter_mutex{ enter_mx_ };
				if (--readers_ == 0) {
					resource_mx_.unlock();
				}
			}
		}
	}
	void write() {
		while (true) {
				pass_mx_.lock();
				lock_guard<mutex>resource_mutex{ resource_mx_ };
				pass_mx_.unlock();
				++count_writes_;
		}
	}

	atomic<unsigned>count_reads_{ 0 };
	atomic<unsigned>count_writes_{ 0 };
private:
	unsigned readers_{ 0 };

	mutex enter_mx_;
	mutex pass_mx_;
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
	cout << "Reads: " << r / (double)sum << "% Writes: " << w / (double)sum << "%" << endl;
	system("pause");
}