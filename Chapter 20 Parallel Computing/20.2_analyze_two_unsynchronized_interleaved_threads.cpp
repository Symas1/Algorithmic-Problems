// analyze two unsynchronized interleaved threads
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
using namespace std;

class Task {
public:
	Task(int threads, int n) :threads_{ threads }, result_{ 0 }, n_{ n } {
		for (int i = 0; i < threads_; ++i) {
			vector_threads_.emplace_back(thread{ &Task::start_increment,this });
		}
	}
	void start_increment() {
		for (int i = 0; i < n_; ++i) {
			++result_;
		}
	}
	~Task() {
		for (auto& t : vector_threads_) {
			if (t.joinable()) {
				t.join();
			}
		}
		cout << result_ << endl;
	}
private:
	atomic<int> result_;
	int n_;
	int threads_;
	vector<thread>vector_threads_;
}; // without atomic minimun result for n>1 == 2

void main() {
	Task{ 10 ,1000000};
	system("pause");
}