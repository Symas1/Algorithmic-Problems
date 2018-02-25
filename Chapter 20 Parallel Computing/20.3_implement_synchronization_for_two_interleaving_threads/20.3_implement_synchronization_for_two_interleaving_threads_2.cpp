// implement synchronization for two interleaving threads
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <atomic>
using namespace std;

class Sync {
public:
	Sync() :turn_{ turns_::odd_turn } {}

	void wait(bool my_turn) {
		unique_lock<mutex>lock{ mx_ };
		cv_.wait(lock, [this,my_turn]() {return turn_ == my_turn; });
	}

	void toggle_turn() {
		lock_guard<mutex>lock{ mx_ };
		turn_ = !turn_;
		cv_.notify_one();
	}

	enum turns_: bool {odd_turn=true,even_turn=false};
private:
	mutex mx_;
	condition_variable cv_;
	bool turn_;
};

void print_odd(Sync& sync) {
	for (int i = 1; i < 100000; i += 2) {
		sync.wait(Sync::turns_::odd_turn);
		cout << i << " ";
		sync.toggle_turn();
	}
}

void print_even(Sync& sync) {
	for (int i = 2; i <= 100000; i += 2) {
		sync.wait(Sync::turns_::even_turn);
		cout << i << " ";
		sync.toggle_turn();
	}
}

void main() {
	Sync a{};
	thread first = thread{ print_odd,ref(a) };
	thread second = thread{ print_even,ref(a) };
	first.join();
	second.join();
	system("pause");
}
