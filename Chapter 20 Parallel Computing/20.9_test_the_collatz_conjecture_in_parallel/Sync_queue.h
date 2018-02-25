#ifndef SYNC_QUEUE_H_
#define SYNC_QUEUE_H_

// sychronized queue
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class Sync_queue {
public:
	void push(T data) {
		std::lock_guard<std::mutex>lock{ mx_ };
		queue_.emplace(move(data));
		cv_.notify_one();
	}
	void wait_and_pop() {
		std::unique_lock<std::mutex>lock{ mx_ };
		if (queue_.empty()) {
			cv_.wait(lock, [this]() {return !queue_.empty(); });
		}
		T result = queue_.front();
		queue_.pop();
		return result;
	}
	bool try_pop(T& data) {
		std::lock_guard<std::mutex>lock{ mx_ };
		if (queue_.empty()) {
			return false;
		}
		data = queue_.front();
		queue_.pop();
		return true;
	}
private:
	std::queue<T>queue_;

	std::mutex mx_;
	std::condition_variable cv_;
};

#endif // SYNC_QUEUE_H_