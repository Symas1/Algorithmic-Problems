// Second readers-writers problem -> readers starvation
//#include <thread>
//#include <mutex>
//#include <iostream>
//#include <vector>
//#include <atomic>
//#include <chrono>
//using namespace std;
//
//class Readers_writers {
//public:
//	void read() {
//		while (keep_working) {
//			{
//				lock_guard<mutex>lock{ mx_in_ };
//				++readers_in_;
//			}
//			++count_reads_;
//			{
//				lock_guard<mutex>lock{ mx_out_ };
//				--readers_in_;
//				if (writer_waits_ && readers_in_ == 0) {
//					cv_.notify_one();
//				}
//			}
//		}
//	}
//	void write() {
//		while (keep_working) {
//			lock_guard<mutex>lock{ mx_in_ };
//			{
//				unique_lock<mutex>lock_uniq{ mx_out_ };
//				if (readers_in_ != 0) {
//					writer_waits_ = true;
//					cv_.wait(lock_uniq, [this]() {return readers_in_ == 0 || keep_working==false; });
//					writer_waits_ = false;
//				}
//			}
//			++count_writes_;
//		}
//	}
//
//	atomic<unsigned> count_reads_{ 0 };
//	atomic<unsigned> count_writes_{ 0 };
//
//	atomic_bool keep_working{ true };
//private:
//	unsigned readers_in_{ 0 };
//	bool writer_waits_{ false };
//
//	mutex mx_in_;
//	mutex mx_out_;
//public:
//	condition_variable cv_;
//};
//
//void main() {
//	Readers_writers rw{};
//	vector<thread>threads;
//	for (int i = 0; i < 5; ++i) {
//		threads.emplace_back(&Readers_writers::read, &rw);
//		threads.emplace_back(&Readers_writers::write, &rw);
//	}
//	this_thread::sleep_for(chrono::seconds{ 2 });
//	rw.keep_working = false;
//	rw.cv_.notify_all();
//	for (auto&t : threads) {
//		t.join();
//	}
//	cout << "Reads: " << rw.count_reads_ << " Writes: " << rw.count_writes_ << " Sum: " << rw.count_reads_ + rw.count_writes_ << endl;
//	system("pause");
//}