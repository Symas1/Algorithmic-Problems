//// First readers-writers problem using shared_mutex -> writers starvation
//#include <thread>
//#include <string>
//#include <iostream>
//#include <atomic>
//#include <mutex>
//#include<chrono>
//#include <shared_mutex>
//#include <vector>
//using namespace std;
//
//class Read_write {
//public:
//	void read() {
//		while (keep_working) {
//			shared_lock<shared_mutex>lock{ mx_ };
//			++count_reads_;
//		}
//	}
//	void write() {
//		while (keep_working) {
//			lock_guard<shared_mutex>lock{ mx_ };
//			++count_writes_;
//		}
//	}
//
//	atomic<unsigned> count_reads_{ 0 };
//	atomic<unsigned> count_writes_{ 0 };
//
//	atomic_bool keep_working{ true };
//private:
//	shared_mutex mx_;
//};
//
//void main() {
//	Read_write rw;
//	vector<thread>threads;
//	for (int i = 0; i < 5; ++i) {
//		threads.emplace_back(&Read_write::read, &rw);
//		threads.emplace_back(&Read_write::write, &rw);
//	}
//
//	this_thread::sleep_for(chrono::seconds(3));
//	unsigned r = rw.count_reads_;
//	unsigned w = rw.count_writes_;
//	unsigned sum = r + w;
//	cout << "Reads: " << r << " Writes: " << w << " Sum: " << sum << endl;
//	cout << "Reads: " << r / (double)sum << "% Writes: " << w / (double)sum << "%" << endl;
//
//	rw.keep_working = false;
//	for (auto&t : threads) {
//		t.join();
//	}
//	system("pause");
//}