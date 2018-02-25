#ifndef THREADSAFE_QUEUE_H_
#define THREADSAFE_QUEUE_H_
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class Threadsafe_queue {
public:
	void push(T data) {
		std::lock_guard<std::mutex>lock{ mx_ };
		queue_.emplace(std::move(data));
		cd_.notify_one();
	}
	T wait_and_pop() {
		std::unique_lock<std::mutex>lock{ mx_ };
		cd_.wait(lock, [this]() {return !queue_.empty(); });
		T return_object = std::move(queue_.top());
		queue_.pop();
		return return_object;
	}
	bool try_pop(T& result) {
		std::lock_guard<std::mutex>lock{ mx_ };
		if (queue_.empty()) {
			return false;
		}

		result = std::move(queue_.front());
		queue_.pop();
		return true;
	}
	bool empty()const {
		std::lock_guard<std::mutex>lock{ mx_ };
		return queue_.empty();
	}
private:
	std::queue<T>queue_;
	mutable std::mutex mx_;
	std::condition_variable cd_;
};

#endif // THREADSAFE_QUEUE_H_
