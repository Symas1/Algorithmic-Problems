// First readers-writers problem using condition variable -> writers starvation
#include <condition_variable>
#include <mutex>
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <vector>
using namespace std;

class Read_write {
public:
	void read() {
		while (keep_working) {
			{
				lock_guard<mutex>lock{ readers_mx_ };
				++readers_;
			}
			++count_reads_;
			{
				lock_guard<mutex>lock{ readers_mx_ };
				if (--readers_ == 0) {
					cv_.notify_one();
				}
			}
		}
	}
	void write() {
		while (keep_working) {
			unique_lock<mutex>r_lock{ readers_mx_ };
			if (readers_ != 0) {
				cv_.wait(r_lock, [this]() {return readers_ == 0 || keep_working==false; });
			}
			++count_writes_;
		}
	}

	atomic<unsigned> count_reads_{ 0 };
	atomic<unsigned> count_writes_{ 0 };

	atomic_bool keep_working{ true };
private:
	atomic<int>readers_;
	mutex readers_mx_;
	mutex writers_mx_;
public:
	condition_variable cv_;
};

void main() {
	Read_write rw{};
	vector<thread>threads;
	for (int i = 0; i < 5; ++i) {
		threads.emplace_back(&Read_write::read, &rw);
		threads.emplace_back(&Read_write::write, &rw);
	}

	this_thread::sleep_for(chrono::seconds(3));
	unsigned r = rw.count_reads_;
	unsigned w = rw.count_writes_;
	unsigned sum = r + w;
	cout << "Reads: " << r << " Writes: " << w << " Sum: " << sum << endl;
	cout << "Reads: " << r / (double)sum << "% Writes: " << w / (double)sum << "%" << endl;

	rw.keep_working = false;
	rw.cv_.notify_all();
	for (auto&t : threads) {
		t.join();
	}
	system("pause");
}