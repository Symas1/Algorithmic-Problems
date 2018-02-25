// the readers-writers problem - this implementation has bug
#include <thread>
#include <string>
#include <iostream>
#include <atomic>
#include <mutex>
#include<chrono>
using namespace std;

class Read_write {
public:
	void read() {
		while (writers_ > 0) {
			this_thread::yield;
		}
		++readers_;
		--readers_;
	}
	void write(const string& new_data) {
		++writers_;
		lock_guard<mutex>lock{ mx_ };
		while (readers_ > 0) {
			this_thread::yield;
		}
		data_ = new_data;
		--writers_;
	}
private:
	atomic<int>readers_{ 0 };
	atomic<int>writers_{ 0 };
	mutex mx_;
	string data_{ "Message" };
};

void main() {
	Read_write obj{};
	thread reader1{ &Read_write::read,&obj };
	this_thread::sleep_for(chrono::milliseconds{ 10 });
	thread reader2{ &Read_write::read,&obj };
	this_thread::sleep_for(chrono::milliseconds{ 10 });
	thread writer1{ &Read_write::write,&obj,"New message" };
	this_thread::sleep_for(chrono::milliseconds{ 10 });
	thread reader3{ &Read_write::read,&obj };
	this_thread::sleep_for(chrono::milliseconds{ 10 });
	thread reader4{ &Read_write::read,&obj };

	reader1.join();
	reader2.join();
	reader3.join();
	reader4.join();
	writer1.join();
	system("pause");
}