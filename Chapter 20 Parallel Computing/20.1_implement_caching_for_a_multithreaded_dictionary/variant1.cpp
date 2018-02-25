// variant 1
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>
#include <chrono>
#include <random>
#include <condition_variable>
#include <string>
#include <iostream>
using namespace std;

class Barrier {
public:
	Barrier(int num_threads) :number_of_threads_{ num_threads }, waiting_threads_{ 0 }, generation_{0} {}
	void wait() {
		unique_lock<mutex>lock{ mx_ };
		int my_generation = generation_;
		if (++waiting_threads_ == number_of_threads_) {
			++generation_;
			waiting_threads_ = 0;
			cv_.notify_all();
		}
		else {
			cv_.wait(lock, [this,&my_generation]() {return my_generation!=generation_; });
		}
	}
private:
	int number_of_threads_;
	int waiting_threads_;
	int generation_;
	mutex mx_;
	condition_variable cv_;
};

class Thread_sync {
public:
	Thread_sync(int num_threads, int k) :barrier_{ num_threads }, k_{ k } {
		for (int i = 0; i < num_threads; ++i) {
			threads_.emplace_back(thread{ &Thread_sync::start,this,"Thread " + to_string(i + 1) });
		}
	}
	void start(const string& thread_name) {
		rendezvous();
		barrier_.wait();
		for (int i = 0; i < k_; ++i) {
			{
				lock_guard<mutex>lock{ mx_ };
				cout << thread_name << " starts critical()\n";
				auto start_time = chrono::system_clock::now();
				critical();
				chrono::duration<float>passed_time = chrono::system_clock::now() - start_time;
				cout << thread_name << " ended critical in " << passed_time.count() << "sec\n";
			}
			barrier_.wait();
		}
	}
	void rendezvous() {
		mt19937 mt{ random_device{}() };
		this_thread::sleep_for(chrono::milliseconds{ uniform_int_distribution<>{100,250}(mt) });
	}
	void critical() {
		mt19937 mt{ random_device{}() };
		this_thread::sleep_for(chrono::milliseconds{ uniform_int_distribution<>{10,25}(mt) });
	}
	~Thread_sync() {
		for (auto& t : threads_) {
			if (t.joinable()) {
				t.join();
			}
		}
	}
private:
	int k_;
	vector<thread>threads_;
	mutex mx_;
	Barrier barrier_;
};

void main() {
	Thread_sync{ 10,3 };
	system("pause");
}