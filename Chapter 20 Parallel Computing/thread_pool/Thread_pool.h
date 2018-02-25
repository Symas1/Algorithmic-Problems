#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_
#include <thread>
#include <vector>
#include <atomic>

#include "Threadsafe_queue.h"
#include "Join_threads.h"

class Thread_pool {
public:
	Thread_pool() :done_{ false }, joiner_{ threads_ } {
		const auto number_of_threads = std::thread::hardware_concurrency();
		try {
			for (unsigned i = 0; i < number_of_threads; ++i) {
				threads_.emplace_back(&Thread_pool::worker_thread, this );
			}
		}
		catch (...) {
			done_ = true;
			throw;
		}
	}

	~Thread_pool() {
		done_ = true;
	}

	template<typename Function_type>
	void submit(Function_type function) {
		queue_.push(std::function<void()>{function});
	}
private:
	void worker_thread() {
		while (!done_) {
			function<void()>task;
			if (queue_.try_pop(task)) {
				task();
			}
			else {
				std::this_thread::yield(); // let other threads work
			}
		}
	}

	std::atomic_bool done_;
	Threadsafe_queue<std::function<void()>>queue_;
	std::vector<std::thread>threads_;
	Join_threads joiner_;
};

#endif // THREAD_POOL_H_