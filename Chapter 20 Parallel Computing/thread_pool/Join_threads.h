#ifndef JOIN_THREADS_H_
#define JOIN_THREADS_H_
#include <vector>
#include <thread>

class Join_threads {
public:
	explicit Join_threads(std::vector<std::thread>&threads) :threads_{ threads } {}
	~Join_threads() {
		for (size_t i = 0; i < threads_.size(); ++i) {
			if (threads_[i].joinable()) {
				threads_[i].join();
			}
		}
	}
private:
	std::vector<std::thread>&threads_;
};

#endif // JOIN_THREADS_H_
