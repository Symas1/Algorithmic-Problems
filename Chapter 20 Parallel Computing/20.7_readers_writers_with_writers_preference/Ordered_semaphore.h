// ordered semaphore - first entered process gets woken up first
#ifndef ORDERED_SEMAPHORE_H_
#define ORDERED_SEMAPHORE_H_
#include <mutex>
#include <condition_variable>
#include <queue>

class Ordered_semaphore {
public:
	Ordered_semaphore(int max_available) :max_available_{ max_available }, currently_available_{ max_available_ } {}
	void acquire() {
		std::unique_lock<std::mutex>lock{ mx_ };
		unsigned my_gen = generation_++;
		if (currently_available_ == 0 || !queue_.empty()) {
			queue_.emplace();
			queue_.back().wait(lock, [this,&my_gen]() 
			{return currently_available_ != 0 && my_gen == next_generation_; });
			queue_.pop();
		}
		--currently_available_;
	}
	void release() {
		std::lock_guard<std::mutex>lock{ mx_ };
		++currently_available_;
		++next_generation_;
		if (!queue_.empty()) {
			queue_.front().notify_one();
		}
	}
private:
	int max_available_;
	int currently_available_;

	unsigned generation_{ 0 };
	unsigned next_generation_{ 0 };

	std::queue<std::condition_variable>queue_;
	std::mutex mx_;
};

#endif // ORDERED_SEMAPHORE_H_