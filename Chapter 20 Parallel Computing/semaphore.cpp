#include <mutex>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <string>
#include <assert.h>
#include <vector>
using namespace std;

class Semaphore {
public:
	Semaphore(int max_available) :max_available_{ max_available }, taken_{ 0 } {};
	void acquire() {
		unique_lock<mutex>lock{ mx_ };
		while (taken_ == max_available_) {
			cond_.wait(lock);
		}
		++taken_;
	}
	void release() {
		lock_guard<mutex>lock{ mx_ };
		--taken_;
		cond_.notify_all();
	}
	int get_taken_()const { return taken_; }
private:
	int max_available_;
	int taken_;
	mutex mx_;
	condition_variable cond_;
};

void test_function(Semaphore& semaphore, const string& thread_name,int max_taken_) {
	semaphore.acquire();
	cout << "Semaphore acquired by " << thread_name << "\nCurrently taken " << semaphore.get_taken_() << endl;
	assert(semaphore.get_taken_() >= 0 && semaphore.get_taken_()<=max_taken_);
	cout << "Semaphore released by " << thread_name << endl;
	semaphore.release();
	assert(semaphore.get_taken_() >= 0 && semaphore.get_taken_() <= max_taken_);
}

void main() {
	int max_taken = 1;
	Semaphore semaphore{ max_taken };
	int size = 10;
	vector<thread>threads(size);
	for (int i = 0; i < size; ++i) {
		threads[i] = thread{ test_function, ref(semaphore), string{"thread " + to_string(i) },max_taken };
	}

	for (int i = 0; i < size; ++i) {
		threads[i].join();
	}
	system("pause");
}