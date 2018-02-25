// implement a timer class
#include <thread>
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <chrono>
#include <atomic>
#include <assert.h>
#include <mutex>
#include <condition_variable>
using namespace std;
using time_point = chrono::time_point<chrono::system_clock>;

struct Task {
	Task(function<void()>task, string&& name) {
		this->task = move(task);
		this->name = move(name);
	}
	function<void()>task;
	string name;
};

class Timer {
public:
	Timer() {
		service_thread_ = thread{ &Timer::alarm_service,this };
	}
	~Timer() {
		keep_work_ = false;
		cond_.notify_one();
		service_thread_.join();
	}
	void add_task(const Task& new_task) {
		tasks_.emplace(new_task.name, pair<Task, __int64>{new_task, 0});
	}
	void start_task_at(const string& name, chrono::time_point<chrono::system_clock> time) {
		auto iter = tasks_.find(name);
		if (iter != tasks_.end()) {
			auto schedule_time = to_seconds(time);
			iter->second.second = schedule_time;
			lock_guard<mutex>lock{ mx_ };
			cout << "Task " << name << " scheduled for " << schedule_time << endl;
			bool top = schedule_time < ((deffered_starts_.empty()) ?
				numeric_limits<long long>::max() : deffered_starts_.begin()->first);
			deffered_starts_.emplace(move(schedule_time), iter);
			if(top){
				cond_.notify_one();
			}
		}
	}
	void cancel_sheduled_start(const string&name) {
		auto iter = tasks_.find(name);
		if (iter != tasks_.end()) {
			lock_guard<mutex>lock{ mx_ };
			auto map_iter = deffered_starts_.find(iter->second.second);
			if (map_iter != deffered_starts_.end()) {
				cout << "Sheduled task " << name << " was canceled by user" << endl;
				bool top = deffered_starts_.begin() == map_iter;
				deffered_starts_.erase(map_iter);
				if (top)
				{
					cond_.notify_one();
				}
			}
		}
	}
private:
	void alarm_service() {
		while (keep_work_) {
			auto current_time = to_seconds(chrono::system_clock::now());
			unique_lock<mutex>lock{ mx_ };
			if (!deffered_starts_.empty()) {
				if (current_time == deffered_starts_.begin()->first) {
					auto task = deffered_starts_.begin()->second->second.first;
					thread{ task.task }.detach();
					deffered_starts_.erase(deffered_starts_.begin());
				}

				if (!deffered_starts_.empty()) {
					auto time_till_next = deffered_starts_.begin()->first - current_time;
					cout << "I will wake up in " << time_till_next << "s" << endl;
					cond_.wait_for(lock, chrono::seconds{ time_till_next });
				}
			}
			else {
				cond_.wait(lock);
			}
		}
	}

	__int64 to_seconds(const chrono::system_clock::time_point& time) {
		return chrono::duration_cast<chrono::seconds>(time.time_since_epoch()).count();
	}

	atomic_bool keep_work_{ true };
	thread service_thread_;
	unordered_map<string, pair<Task, __int64>>tasks_;
	map< __int64, unordered_map<string, pair<Task, __int64>>::iterator>deffered_starts_;

	mutex mx_;
	condition_variable cond_;
};

void print_hello() {
	cout << "Hello, current time: " <<
		chrono::duration_cast<chrono::seconds>(chrono::system_clock::now().time_since_epoch()).count() << endl;
}

void print_how() {
	cout << "How are you? Current time: " <<
		chrono::duration_cast<chrono::seconds>(chrono::system_clock::now().time_since_epoch()).count() << endl;
}

void main() {
	Task a{ print_hello,"print_hello" };
	Task a2{ print_how,"print_how" };
	Timer b;
	b.add_task(a);
	b.start_task_at("print_hello", chrono::system_clock::now() + chrono::seconds{ 3 });
	b.add_task(a2);
	b.start_task_at("print_how", chrono::system_clock::now() + chrono::seconds{ 2 }); // if 4 -> doesn't wake up
	this_thread::sleep_for(chrono::milliseconds{ 200 });
	b.cancel_sheduled_start("print_how");
	this_thread::sleep_for(chrono::seconds{ 4 });
	system("pause");
}