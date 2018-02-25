// implement synchronization for two interleaving threads
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <atomic>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

class Sync {
public:
	Sync() :odd_turn_{ true } {
		first_ = thread{ &Sync::print_odd,this };
		second_ = thread{ &Sync::print_even,this };
	}
	void print_odd() {
		int num = 1;
		while (num <= max_value_-1) {
			{
				while (!odd_turn_) {
					this_thread::yield;
				}
				res_.emplace_back(num);
				odd_turn_ = !odd_turn_;
			}
			num += 2;
		}
	}
	void print_even() {
		int num = 2;
		while (num <= max_value_) {
			{
				while (odd_turn_) {
					this_thread::yield;
				}
				res_.emplace_back(num);
				odd_turn_ = !odd_turn_;
			}
			num += 2;
		}
	}
	~Sync() {
		if (first_.joinable()) {
			first_.join();
		}
		if (second_.joinable()) {
			second_.join();
		}
		assert(is_sorted(res_.begin(), res_.end()));
	}
private:
	static int max_value_;
	thread first_;
	thread second_;
	atomic_bool odd_turn_;
	vector<int>res_;
};
int Sync::max_value_ = 100000;

//void main() {
//	Sync{};
//	system("pause");
//}
